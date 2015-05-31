#include <Dunjun/Window.hpp>

#include <Dunjun/Common.hpp>

namespace Dunjun
{
namespace Window
{
GLFWwindow* g_ptr{nullptr};
bool g_isFullscreen{false};

namespace
{
GLOBAL const Dimensions g_windowSize{1280, 720};

GLOBAL Dimensions g_size{g_windowSize.width, g_windowSize.height};
} // namespace (anonymous)F

// GLFW Specific Callback Prototypes
INTERNAL void resizeCallback(GLFWwindow* window, int width, int height);
INTERNAL void framebufferSizeCallback(GLFWwindow* window, int w, int h);
INTERNAL void errorCallback(int error, const char* description);
INTERNAL void windowRefreshCallback(GLFWwindow* window);

GLFWwindow* getHandle()
{
	return g_ptr;
}

void setHandle(GLFWwindow* w)
{
	g_ptr = w;
}

bool init()
{
	if (!glfwInit())
		return false;

	setHandle(createWindow({g_windowSize.width, g_windowSize.height}));
	if (!getHandle())
	{
		glfwTerminate();
		return false;
	}

	makeContextCurrent();

	glfwSetErrorCallback(errorCallback);

	return true;
}

void cleanup()
{
	glfwDestroyWindow(getHandle());
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
		const GLFWvidmode* mode{glfwGetVideoMode(monitor)};

		glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
		glfwWindowHint(GLFW_RED_BITS, mode->redBits);
		glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
		glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);

		glfwWindowHint(GLFW_RESIZABLE, false);

		g_size.width = mode->width;
		g_size.height = mode->height;
	}
	else
	{
		glfwWindowHint(GLFW_RESIZABLE, true);

		// TODO(bill): Set to previous window size
		// Initial Window Size
		g_size.width = g_windowSize.width;
		g_size.height = g_windowSize.height;
	}

	GLFWwindow* w{glfwCreateWindow(
	    g_size.width, g_size.height, "Dunjun", monitor, getHandle())};

	// Set GLFW specific callbacks
	glfwSetFramebufferSizeCallback(w, framebufferSizeCallback);
	glfwSetWindowSizeCallback(w, resizeCallback);
	glfwSetWindowRefreshCallback(w, windowRefreshCallback);

	glfwGetWindowSize(w, &g_size.width, &g_size.height);

	return w;
}

GLFWwindow* createWindow(Dimensions size, GLFWmonitor* monitor)
{
	glfwDefaultWindowHints();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_FOCUSED, true);

	if (monitor) // Fullscreen
	{
		const GLFWvidmode* mode{glfwGetVideoMode(monitor)};

		glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
		glfwWindowHint(GLFW_RED_BITS, mode->redBits);
		glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
		glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);

		glfwWindowHint(GLFW_RESIZABLE, false);

		g_size.width = mode->width;
		g_size.height = mode->height;
	}
	else
	{
		glfwWindowHint(GLFW_RESIZABLE, true);

		// TODO(bill): Set to previous window size
		// Initial Window Size
		g_size = size;
	}

	GLFWwindow* w{glfwCreateWindow(
	    g_size.width, g_size.height, "Dunjun", monitor, getHandle())};

	// Set GLFW specific callbacks
	glfwSetFramebufferSizeCallback(w, framebufferSizeCallback);
	glfwSetWindowSizeCallback(w, resizeCallback);
	glfwSetWindowRefreshCallback(w, windowRefreshCallback);

	glfwGetWindowSize(w, &g_size.width, &g_size.height);

	return w;
}

void destroyWindow() { glfwDestroyWindow(getHandle()); }

void makeContextCurrent() { glfwMakeContextCurrent(getHandle()); }

void swapInterval(int i) { glfwSwapInterval(i); }

bool shouldClose() { return glfwWindowShouldClose(getHandle()) == 1; }

void swapBuffers() { glfwSwapBuffers(getHandle()); }

void pollEvents() { glfwPollEvents(); }

void setTitle(const std::string& title)
{
	glfwSetWindowTitle(getHandle(), title.c_str());
}

bool isFullscreen()
{
	return g_isFullscreen;
}

void setFullscreen(bool fullscreen)
{
	g_isFullscreen = fullscreen;
}

Dimensions getWindowSize()
{
	return g_size;
}

Dimensions getFramebufferSize()
{
	int x;
	int y;

	glfwGetFramebufferSize(getHandle(), &x, &y);

	return Dimensions{x, y};
}

bool isInFocus()
{
	return glfwGetWindowAttrib(getHandle(), GLFW_FOCUSED) == 1;
}

bool isIconified()
{
	return glfwGetWindowAttrib(getHandle(), GLFW_ICONIFIED) == 1;
}

// GLFW Specific Callbacks
INTERNAL void resizeCallback(GLFWwindow* window, int width, int height)
{
	g_size.width = width;
	g_size.height = height;
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
	glfwMakeContextCurrent(window);
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);

	glfwSwapBuffers(window);
}
} // namespace Window
} // namespace Dunjun
