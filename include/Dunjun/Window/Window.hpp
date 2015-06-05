#ifndef DUNJUN_WINDOW_WINDOW_HPP
#define DUNJUN_WINDOW_WINDOW_HPP

#include <Dunjun/Math.hpp>
#include <Dunjun/System/OpenGL.hpp>
#include <Dunjun/System/Clock.hpp>
#include <Dunjun/Window/VideoMode.hpp>
#include <Dunjun/Window/ContextSettings.hpp>

#include <SDL/SDL.h>

#include <string>

namespace Dunjun
{
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

struct Event;

class Window
{
public:
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

	Window();

	explicit Window(VideoMode mode,
					const std::string& title,
					u32 style = Style::Default,
					const ContextSettings& settings = ContextSettings{});

	virtual ~Window();

	void create(VideoMode mode,
				const std::string& title,
				u32 style = Style::Default,
				const ContextSettings& settings = ContextSettings{});

	void close();
	bool isOpen() const;

	Vector2 getPosition() const;
	Window& setPosition(const Vector2& position);

	Dimensions getSize() const;
	Window& setSize(const Dimensions& size);

	Window& setTitle(const std::string& title);
	Window& setVisible(bool visible);
	Window& setVerticalSyncEnabled(bool enabled);
	Window& setFramerateLimit(u32 limit);

	Window& setFullscreen(bool fullscreen);
	bool isFullscreen() const;


	bool pollEvent(Event& event);
	bool waitEvent(Event& event);

	void display();

	SDL_Window* getNativeHandle() const { return m_impl; }

private:
	void init();

	SDL_Window* m_impl;
	SDL_GLContext m_context;
	Clock m_clock;
	Time m_frameTimeLimit;
	// Dimensions m_size;
};
} // namespace Dunjun
#endif
