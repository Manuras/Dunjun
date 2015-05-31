#include <Dunjun/Window.hpp>

namespace Dunjun
{
namespace
{
GLOBAL const Window* fullscreenWindow{nullptr};

INTERNAL u32 generateFlags(u32 style)
{
	u32 flags;
	flags |= SDL_WINDOW_OPENGL;

	if (style & Style::Borderless)
		flags |= SDL_WINDOW_BORDERLESS;
	if (style & Style::Fullscreen && !(style & Style::Windowed))
		flags |= SDL_WINDOW_FULLSCREEN;
	if (style & Style::Visible)
		flags |= SDL_WINDOW_SHOWN;
	if (style & Style::Hidden)
		flags |= SDL_WINDOW_HIDDEN;
	if (style & Style::Minimized)
		flags |= SDL_WINDOW_MINIMIZED;
	if (style & Style::Maximized)
		flags |= SDL_WINDOW_MAXIMIZED;

	return flags;
}
}

Window::Window()
: m_impl{nullptr}
, m_context{}
, m_frameTimeLimit{Time::Zero}
, m_size{0, 0}
{

}

Window::Window(const Dimensions& dimensions,
			   const std::string& title,
			   u32 style)
: m_impl{nullptr}
, m_context{}
, m_frameTimeLimit{Time::Zero}
, m_size{0, 0}
{
	create(dimensions, title, style);
}

Window::~Window()
{
	close();
}



void Window::create(const Dimensions& dimensions,
					const std::string& title,
					u32 style)
{
	// Destroy the original window
	close();

	if (style & Style::Fullscreen)
	{
		if (fullscreenWindow)
		{
			std::cerr << "Creating two fullscreen windows is not allowed.\n";
			style &= ~Style::Fullscreen;
		}
		else
		{
			// TODO(bill): Check if fullscreen dimensions is valid

			fullscreenWindow = this;
		}
	}

	u32 windowFlags{generateFlags(style)};
	m_impl = SDL_CreateWindow(title.c_str(),
							  SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
							  dimensions.width, dimensions.height,
							  windowFlags);

	m_context = SDL_GL_CreateContext(m_impl);

	m_size = dimensions;

	init();
}

void Window::init()
{

}

void Window::close()
{
	SDL_DestroyWindow(m_impl);
	m_impl = nullptr;

	if (this == fullscreenWindow)
		fullscreenWindow = nullptr;
}

bool Window::isOpen() const
{
	return m_impl != nullptr;
}

Vector2 Window::getPosition() const
{
	if (m_impl)
	{

	}

	return {0, 0};
}

Window& Window::setPosition(const Vector2& position)
{
	return *this;
}

Dimensions Window::getSize() const
{
	return {0, 0};
}

Window& Window::setSize()
{
	return *this;
}

Window& Window::setTitle(const std::string& title)
{
	return *this;
}

Window& Window::setVisible(bool visible)
{
	return *this;
}

Window& Window::setVerticalSyncEnabled(bool enabled)
{
	return *this;
}

Window& Window::setFramerateLimit(u32 limit)
{
	return *this;
}

void Window::display()
{

}
} // namespace Dunjun


//#include <Dunjun/Window.hpp>
//
//#include <Dunjun/Common.hpp>
//
//namespace Dunjun
//{
//namespace Window
//{
//GLFWwindow* g_ptr{nullptr};
//bool g_isFullscreen{false};
//
//namespace
//{
//GLOBAL const Dimensions g_windowSize{1280, 720};
//
//GLOBAL Dimensions g_size{g_windowSize.width, g_windowSize.height};
//} // namespace (anonymous)
//
//// GLFW Specific Callback Prototypes
//INTERNAL void resizeCallback(GLFWwindow* window, int width, int height);
//INTERNAL void framebufferSizeCallback(GLFWwindow* window, int w, int h);
//INTERNAL void errorCallback(int error, const char* description);
//INTERNAL void windowRefreshCallback(GLFWwindow* window);
//
//GLFWwindow* getHandle()
//{
//	return g_ptr;
//}
//
//void setHandle(GLFWwindow* w)
//{
//	g_ptr = w;
//}
//
//bool init()
//{
//	if (!glfwInit())
//		return false;
//
//	setHandle(createWindow({g_windowSize.width, g_windowSize.height}));
//	if (!getHandle())
//	{
//		glfwTerminate();
//		return false;
//	}
//
//	makeContextCurrent();
//
//	glfwSetErrorCallback(errorCallback);
//
//	return true;
//}
//
//void cleanup()
//{
//	glfwDestroyWindow(getHandle());
//	glfwTerminate();
//}
//
//GLFWwindow* createWindow(GLFWmonitor* monitor)
//{
//	glfwDefaultWindowHints();
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
//	glfwWindowHint(GLFW_FOCUSED, true);
//
//	if (monitor) // Fullscreen
//	{
//		const GLFWvidmode* mode{glfwGetVideoMode(monitor)};
//
//		glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
//		glfwWindowHint(GLFW_RED_BITS, mode->redBits);
//		glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
//		glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
//
//		glfwWindowHint(GLFW_RESIZABLE, false);
//
//		g_size.width = mode->width;
//		g_size.height = mode->height;
//	}
//	else
//	{
//		glfwWindowHint(GLFW_RESIZABLE, true);
//
//		// TODO(bill): Set to previous window size
//		// Initial Window Size
//		g_size.width = g_windowSize.width;
//		g_size.height = g_windowSize.height;
//	}
//
//	GLFWwindow* w{glfwCreateWindow(
//	    g_size.width, g_size.height, "Dunjun", monitor, getHandle())};
//
//	// Set GLFW specific callbacks
//	glfwSetFramebufferSizeCallback(w, framebufferSizeCallback);
//	glfwSetWindowSizeCallback(w, resizeCallback);
//	glfwSetWindowRefreshCallback(w, windowRefreshCallback);
//
//	glfwGetWindowSize(w, &g_size.width, &g_size.height);
//
//	return w;
//}
//
//GLFWwindow* createWindow(Dimensions size, GLFWmonitor* monitor)
//{
//	glfwDefaultWindowHints();
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
//	glfwWindowHint(GLFW_FOCUSED, true);
//
//	if (monitor) // Fullscreen
//	{
//		const GLFWvidmode* mode{glfwGetVideoMode(monitor)};
//
//		glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
//		glfwWindowHint(GLFW_RED_BITS, mode->redBits);
//		glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
//		glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
//
//		glfwWindowHint(GLFW_RESIZABLE, false);
//
//		g_size.width = mode->width;
//		g_size.height = mode->height;
//	}
//	else
//	{
//		glfwWindowHint(GLFW_RESIZABLE, true);
//
//		// TODO(bill): Set to previous window size
//		// Initial Window Size
//		g_size = size;
//	}
//
//	GLFWwindow* w{glfwCreateWindow(
//	    g_size.width, g_size.height, "Dunjun", monitor, getHandle())};
//
//	// Set GLFW specific callbacks
//	glfwSetFramebufferSizeCallback(w, framebufferSizeCallback);
//	glfwSetWindowSizeCallback(w, resizeCallback);
//	glfwSetWindowRefreshCallback(w, windowRefreshCallback);
//
//	glfwGetWindowSize(w, &g_size.width, &g_size.height);
//
//	return w;
//}
//
//void destroyWindow() { glfwDestroyWindow(getHandle()); }
//
//void makeContextCurrent() { glfwMakeContextCurrent(getHandle()); }
//
//void swapInterval(int i) { glfwSwapInterval(i); }
//
//bool shouldClose() { return glfwWindowShouldClose(getHandle()) == 1; }
//
//void swapBuffers() { glfwSwapBuffers(getHandle()); }
//
//void pollEvents() { glfwPollEvents(); }
//
//void setTitle(const std::string& title)
//{
//	glfwSetWindowTitle(getHandle(), title.c_str());
//}
//
//bool isFullscreen()
//{
//	return g_isFullscreen;
//}
//
//void setFullscreen(bool fullscreen)
//{
//	g_isFullscreen = fullscreen;
//}
//
//Dimensions getWindowSize()
//{
//	return g_size;
//}
//
//Dimensions getFramebufferSize()
//{
//	int x;
//	int y;
//
//	glfwGetFramebufferSize(getHandle(), &x, &y);
//
//	return Dimensions{x, y};
//}
//
//bool isInFocus()
//{
//	return glfwGetWindowAttrib(getHandle(), GLFW_FOCUSED) == 1;
//}
//
//bool isIconified()
//{
//	return glfwGetWindowAttrib(getHandle(), GLFW_ICONIFIED) == 1;
//}
//
//// GLFW Specific Callbacks
//INTERNAL void resizeCallback(GLFWwindow* window, int width, int height)
//{
//	g_size.width = width;
//	g_size.height = height;
//}
//
//INTERNAL void framebufferSizeCallback(GLFWwindow* window, int width, int height)
//{
//	glViewport(0, 0, width, height);
//}
//
//INTERNAL void errorCallback(int error, const char* description)
//{
//	std::cerr << "[ERROR]";
//	std::cerr << "GLFW: " << description;
//	std::cerr << std::endl;
//}
//
//INTERNAL void windowRefreshCallback(GLFWwindow* window)
//{
//	glfwMakeContextCurrent(window);
//	glClearColor(0, 0, 0, 0);
//	glClear(GL_COLOR_BUFFER_BIT);
//
//	glfwSwapBuffers(window);
//}
//} // namespace Window
//} // namespace Dunjun
