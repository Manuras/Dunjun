#ifndef DUNJUN_WINDOW_HPP
#define DUNJUN_WINDOW_HPP

#include <Dunjun/Math.hpp>

#include <Dunjun/OpenGL.hpp>

#include <Dunjun/Clock.hpp>

#include <SDL/SDL.h>

#include <string>

namespace Dunjun
{
struct Dimensions
{
	Dimensions() = default;
	Dimensions(int width, int height)
	: width{width}
	, height{height}
	{
	}

	inline f32 aspectRatio() const
	{
		if (width == height)
			return 1.0f;

		return static_cast<f32>(width) / static_cast<f32>(height);
	}

	int width;
	int height;
};

namespace Style
{
	enum : u32
	{
		Borderless = 1,
		Windowed   = 2,
		Fullscreen = 4,
		Visible    = 8,
		Hidden     = 16,
		Minimized  = 32,
		Maximized  = 64,
		Resizable  = 128,

		Default = Windowed | Visible | Resizable,
	};
} // namespace Style


class Window
{
public:
	Window();

	explicit Window(const Dimensions& dimensions,
					const std::string& title,
					u32 style);

	virtual ~Window();

	void create(const Dimensions& dimensions,
				const std::string& title,
				u32 style);

	void close();
	bool isOpen() const;

	Vector2 getPosition() const;
	Window& setPosition(const Vector2& position);

	Dimensions getSize() const;
	Window& setSize();

	Window& setTitle(const std::string& title);
	Window& setVisible(bool visible);
	Window& setVerticalSyncEnabled(bool enabled);
	Window& setFramerateLimit(u32 limit);

	void display();

private:
	void init();

	SDL_Window* m_impl;
	SDL_GLContext m_context;
	Clock m_clock;
	Time m_frameTimeLimit;
	Dimensions m_size;
};
} // namespace Dunjun

//namespace Dunjun
//{
//namespace Window
//{
//struct Dimensions
//{
//	int width;
//	int height;
//
//	inline f32 aspectRatio() const
//	{
//		if (width == height)
//			return 1.0f;
//
//		return static_cast<f32>(width) / static_cast<f32>(height);
//	}
//};
//
//GLFWwindow* getHandle();
//void setHandle(GLFWwindow* w);
//
//bool init();
//void cleanup();
//
//GLFWwindow* createWindow(GLFWmonitor* monitor = nullptr);
//GLFWwindow* createWindow(Dimensions size, GLFWmonitor* monitor = nullptr);
//void destroyWindow();
//void destroyWindow(GLFWwindow* w);
//
//void makeContextCurrent();
//void swapInterval(int i);
//bool shouldClose(); // Or should it be isOpen() ?
//
//void swapBuffers(); // or should it be display() ?
//void pollEvents();
//
//void setTitle(const std::string& title);
//
//bool isFullscreen();
//void setFullscreen(bool fullscreen);
//
//Dimensions getWindowSize();
//Dimensions getFramebufferSize();
//
//bool isInFocus();
//bool isIconified();

// void setIcon(const Image& image);
// void setFramerateLimit(u32 limit);
// void setVerticalSyncEnabled(bool enabled);
// bool hasFocus();

// TODO(bill): Event System
// // Pop the event on top of the event queue, if any, and return it
// bool pollEvent(Event& event);
// // Wait for an event and return it
// bool waitEvent(Event& event);
//
//} // namespace Window
//} // namespace Dunjun

#endif
