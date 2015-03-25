#include <Dunjun/Window.hpp>

#include <Dunjun/Common.hpp>

namespace Dunjun
{
namespace Window
{
GLFWwindow* g_ptr = nullptr;
bool g_isFullscreen = false;

namespace
{
GLOBAL const int g_windowWidth = 1280;
GLOBAL const int g_windowHeight = 720;

GLOBAL int g_width = g_windowWidth;
GLOBAL int g_height = g_windowHeight;
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

	Window::g_ptr = createWindow(nullptr, g_windowWidth, g_windowHeight);
	if (!Window::g_ptr)
	{
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(Window::g_ptr);
	glfwSwapInterval(1);

	glfwSetErrorCallback(errorCallback);

	return true;
}

void cleanup()
{
	glfwDestroyWindow(Window::g_ptr);
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
		Window::g_width = g_windowWidth;
		Window::g_height = g_windowHeight;
	}

	GLFWwindow* w = glfwCreateWindow(
		Window::g_width, Window::g_height, "Dunjun", monitor, Window::g_ptr);

	// Set GLFW specific callbacks
	glfwSetFramebufferSizeCallback(w, framebufferSizeCallback);
	glfwSetWindowSizeCallback(w, resizeCallback);
	glfwSetWindowRefreshCallback(w, windowRefreshCallback);

	glfwGetWindowSize(w, &Window::g_width, &Window::g_height);

	return w;
}

GLFWwindow* createWindow(GLFWmonitor* monitor, u32 width, u32 height)
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
		Window::g_width = width;
		Window::g_height = height;
	}

	GLFWwindow* w = glfwCreateWindow(
		Window::g_width, Window::g_height, "Dunjun", monitor, Window::g_ptr);

	// Set GLFW specific callbacks
	glfwSetFramebufferSizeCallback(w, framebufferSizeCallback);
	glfwSetWindowSizeCallback(w, resizeCallback);
	glfwSetWindowRefreshCallback(w, windowRefreshCallback);

	glfwGetWindowSize(w, &Window::g_width, &Window::g_height);

	return w;
}

void destroyWindow()
{
	glfwDestroyWindow(Window::g_ptr);
}

void destroyWindow(GLFWwindow* windowPtr) { glfwDestroyWindow(windowPtr); }

void makeContextCurrent()
{
	glfwMakeContextCurrent(Window::g_ptr);
}

void swapInterval(int i) { glfwSwapInterval(i); }

bool shouldClose()
{
	return glfwWindowShouldClose(Window::g_ptr) == 1;
}

void swapBuffers()
{
	glfwSwapBuffers(Window::g_ptr);
}

void pollEvents() { glfwPollEvents(); }

void setTitle(const char* title)
{
	glfwSetWindowTitle(Window::g_ptr, title);
}

Vector2 getWindowSize() { return Vector2(static_cast<f32>(Window::g_width),
										 static_cast<f32>(Window::g_height)); }

Vector2 getFramebufferSize()
{
	int width;
	int height;

	glfwGetFramebufferSize(Window::g_ptr, &width, &height);

	return Vector2(width, height);
}

bool isInFocus()
{
	return glfwGetWindowAttrib(Window::g_ptr, GLFW_FOCUSED) == 1;
}

bool isIconified()
{
	return glfwGetWindowAttrib(Window::g_ptr, GLFW_ICONIFIED) == 1;
}

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
	glViewport(0, 0, (GLsizei)fbSize.x, (GLsizei)fbSize.y);

	glfwMakeContextCurrent(window);
	// glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glfwSwapBuffers(window);
}
} // namespace Window
} // namespace Dunjun
