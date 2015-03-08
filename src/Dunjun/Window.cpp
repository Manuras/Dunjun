#include <Dunjun/Window.hpp>

#include <Dunjun/Common.hpp>

namespace Dunjun
{
namespace Window
{
GLFWwindow* ptr = nullptr;
bool isFullscreen = false;

namespace
{
GLOBAL int g_width = 854;
GLOBAL int g_height = 480;
} // namespace (anonymous)

// GLFW Specific Callback Prototypes
INTERNAL void resizeCallback(GLFWwindow* window, int width, int height);
INTERNAL void framebufferSizeCallback(GLFWwindow* window, int width, int height);
INTERNAL void errorCallback(int error, const char* description);
INTERNAL void windowRefreshCallback(GLFWwindow* window);

bool init()
{
	if (!glfwInit())
		return false;

	Window::ptr = createWindow(nullptr);
	if (!Window::ptr)
	{
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(Window::ptr);
	glfwSwapInterval(1);

	glfwSetErrorCallback(errorCallback);

	return true;
}

void cleanup()
{
	glfwDestroyWindow(Window::ptr);
	glfwTerminate();
}

GLFWwindow* createWindow(GLFWmonitor* monitor)
{
	glfwDefaultWindowHints();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_FOCUSED, true);

	if (monitor) // Fullscreen
	{
		const GLFWvidmode* mode = glfwGetVideoMode(monitor);

		glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
		glfwWindowHint(GLFW_RED_BITS, mode->redBits);
		glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
		glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);

		glfwWindowHint(GLFW_RESIZABLE, false);

		Window::g_width = mode->width;
		Window::g_height = mode->height;
	}
	else
	{
		glfwWindowHint(GLFW_RESIZABLE, true);

		// TODO(bill): Set to previous window size
		// Initial Window Size
		Window::g_width = 854;
		Window::g_height = 480;
	}

	GLFWwindow* w = glfwCreateWindow(
	    Window::g_width, Window::g_height, "Dunjun", monitor, Window::ptr);

	// Set GLFW specific callbacks
	glfwSetFramebufferSizeCallback(w, framebufferSizeCallback);
	glfwSetWindowSizeCallback(w, resizeCallback);
	glfwSetWindowRefreshCallback(w, windowRefreshCallback);

	glfwGetWindowSize(w, &Window::g_width, &Window::g_height);

	return w;
}

void destroyWindow() { glfwDestroyWindow(Window::ptr); }

void destroyWindow(GLFWwindow* windowPtr) { glfwDestroyWindow(windowPtr); }

void makeContextCurrent() { glfwMakeContextCurrent(Window::ptr); }

void swapInterval(int i) { glfwSwapInterval(i); }

bool shouldClose() { return glfwWindowShouldClose(Window::ptr); }

void swapBuffers() { glfwSwapBuffers(Window::ptr); }

void pollEvents() { glfwPollEvents(); }

void setTitle(const char* title) { glfwSetWindowTitle(Window::ptr, title); }

Vector2 getWindowSize() { return Vector2(Window::g_width, Window::g_height); }

Vector2 getFramebufferSize()
{
	int width;
	int height;

	glfwGetFramebufferSize(Window::ptr, &width, &height);

	return Vector2(width, height);
}

bool isInFocus() { return glfwGetWindowAttrib(Window::ptr, GLFW_FOCUSED); }

bool isIconified() { return glfwGetWindowAttrib(Window::ptr, GLFW_ICONIFIED); }

// GLFW Specific Callbacks
INTERNAL void resizeCallback(GLFWwindow* window, int width, int height)
{
	Window::g_width = width;
	Window::g_height = height;
}

INTERNAL void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

INTERNAL void errorCallback(int error, const char* description)
{
	std::cerr << "[ERROR]";
	std::cerr << "GLFW: " << description;
	std::cerr << std::endl;
}

INTERNAL void windowRefreshCallback(GLFWwindow* window)
{
	Vector2 fbSize = getFramebufferSize();
	glViewport(0, 0, fbSize.x, fbSize.y);

	glfwMakeContextCurrent(window);
	// glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glfwSwapBuffers(window);
}
} // namespace Window
} // namespace Dunjun
