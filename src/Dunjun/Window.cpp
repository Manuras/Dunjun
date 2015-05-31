#include <Dunjun/Window.hpp>

#include <Dunjun/Event.hpp>

namespace Dunjun
{
namespace
{
GLOBAL const Window* fullscreenWindow{nullptr};

INTERNAL u32 generateFlags(u32 style)
{
	u32 flags = SDL_WINDOW_OPENGL;

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
	if (style & Style::Resizable)
		flags |= SDL_WINDOW_RESIZABLE;

	return flags;
}
}

Window::Window()
: m_impl{nullptr}
, m_context{}
, m_frameTimeLimit{Time::Zero}
{

}

Window::Window(const Dimensions& size,
			   const std::string& title,
			   u32 style)
: m_impl{nullptr}
, m_context{}
, m_frameTimeLimit{Time::Zero}
{
	create(size, title, style);
}

Window::~Window()
{
	close();
}



void Window::create(const Dimensions& size,
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
							  size.width, size.height,
							  windowFlags);

	m_context = SDL_GL_CreateContext(m_impl);

	init();
}

void Window::init()
{
	setVisible(true);
	setFramerateLimit(0);
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
		int x, y;
		SDL_GetWindowPosition(m_impl, &x, &y);

		return Vector2{(f32)x, (f32)y};
	}

	return {0, 0};
}

Window& Window::setPosition(const Vector2& position)
{
	SDL_SetWindowPosition(m_impl, position.x, position.y);

	return *this;
}

Window::Dimensions Window::getSize() const
{
	// TODO(bill): update when changed
	s32 width, height;
	SDL_GetWindowSize(m_impl, &width, &height);

	return {width, height};
}

Window& Window::setSize(const Dimensions& size)
{
	SDL_SetWindowSize(m_impl, size.width, size.height);

	return *this;
}

Window& Window::setTitle(const std::string& title)
{
	SDL_SetWindowTitle(m_impl, title.c_str());

	return *this;
}

Window& Window::setVisible(bool visible)
{
	if (visible)
		SDL_ShowWindow(m_impl);
	else
		SDL_HideWindow(m_impl);

	return *this;
}

Window& Window::setVerticalSyncEnabled(bool enabled)
{
	// TODO(bill):

	return *this;
}

Window& Window::setFramerateLimit(u32 limit)
{
	if (limit > 0)
		m_frameTimeLimit = seconds(1.0f / (f32)limit);
	else
		m_frameTimeLimit = Time::Zero;

	return *this;
}

void Window::display()
{
	SDL_GL_SwapWindow(m_impl);

	if (m_frameTimeLimit != Time::Zero)
	{
		Time::sleep(m_frameTimeLimit - m_clock.getElapsedTime());
		m_clock.restart();
	}

}

INTERNAL Input::Key convertFromSDL_ScanCode(u32 code)
{
	using namespace Input;
	switch (code)
	{
	default:
		return Key::Unknown;
	case SDL_SCANCODE_A:
		return Key::A;
	case SDL_SCANCODE_B:
		return Key::B;
	case SDL_SCANCODE_C:
		return Key::C;
	case SDL_SCANCODE_D:
		return Key::D;
	case SDL_SCANCODE_E:
		return Key::E;
	case SDL_SCANCODE_F:
		return Key::F;
	case SDL_SCANCODE_G:
		return Key::G;
	case SDL_SCANCODE_H:
		return Key::H;
	case SDL_SCANCODE_I:
		return Key::I;
	case SDL_SCANCODE_J:
		return Key::J;
	case SDL_SCANCODE_K:
		return Key::K;
	case SDL_SCANCODE_L:
		return Key::L;
	case SDL_SCANCODE_M:
		return Key::M;
	case SDL_SCANCODE_N:
		return Key::N;
	case SDL_SCANCODE_O:
		return Key::O;
	case SDL_SCANCODE_P:
		return Key::P;
	case SDL_SCANCODE_Q:
		return Key::Q;
	case SDL_SCANCODE_R:
		return Key::R;
	case SDL_SCANCODE_S:
		return Key::S;
	case SDL_SCANCODE_T:
		return Key::T;
	case SDL_SCANCODE_U:
		return Key::U;
	case SDL_SCANCODE_V:
		return Key::V;
	case SDL_SCANCODE_W:
		return Key::W;
	case SDL_SCANCODE_X:
		return Key::X;
	case SDL_SCANCODE_Y:
		return Key::Y;
	case SDL_SCANCODE_Z:
		return Key::Z;
	case SDL_SCANCODE_0:
		return Key::Num0;
	case SDL_SCANCODE_1:
		return Key::Num1;
	case SDL_SCANCODE_2:
		return Key::Num2;
	case SDL_SCANCODE_3:
		return Key::Num3;
	case SDL_SCANCODE_4:
		return Key::Num4;
	case SDL_SCANCODE_5:
		return Key::Num5;
	case SDL_SCANCODE_6:
		return Key::Num6;
	case SDL_SCANCODE_7:
		return Key::Num7;
	case SDL_SCANCODE_8:
		return Key::Num8;
	case SDL_SCANCODE_9:
		return Key::Num9;
	case SDL_SCANCODE_ESCAPE:
		return Key::Escape;
	case SDL_SCANCODE_LCTRL:
		return Key::LControl;
	case SDL_SCANCODE_LSHIFT:
		return Key::LShift;
	case SDL_SCANCODE_LALT:
		return Key::LAlt;
	case SDL_SCANCODE_LGUI:
		return Key::LSystem;
	case SDL_SCANCODE_RCTRL:
		return Key::RControl;
	case SDL_SCANCODE_RSHIFT:
		return Key::RShift;
	case SDL_SCANCODE_RALT:
		return Key::RAlt;
	case SDL_SCANCODE_RGUI:
		return Key::RSystem;
	case SDL_SCANCODE_MENU:
		return Key::Menu;
	case SDL_SCANCODE_LEFTBRACKET:
		return Key::LBracket;
	case SDL_SCANCODE_RIGHTBRACKET:
		return Key::RBracket;
	case SDL_SCANCODE_SEMICOLON:
		return Key::SemiColon;
	case SDL_SCANCODE_COMMA:
		return Key::Comma;
	case SDL_SCANCODE_PERIOD:
		return Key::Period;
	case SDL_SCANCODE_APOSTROPHE:
		return Key::Apostrophe;
	case SDL_SCANCODE_SLASH:
		return Key::Slash;
	case SDL_SCANCODE_BACKSLASH:
		return Key::BackSlash;
	case SDL_SCANCODE_EQUALS:
		return Key::Equal;
	case SDL_SCANCODE_MINUS:
		return Key::Minus;
	case SDL_SCANCODE_SPACE:
		return Key::Space;
	case SDL_SCANCODE_RETURN:
		return Key::Return;
	case SDL_SCANCODE_BACKSPACE:
		return Key::BackSpace;
	case SDL_SCANCODE_TAB:
		return Key::Tab;
	case SDL_SCANCODE_GRAVE:
		return Key::GraveAccent;
	case SDL_SCANCODE_PAGEUP:
		return Key::PageUp;
	case SDL_SCANCODE_PAGEDOWN:
		return Key::PageDown;
	case SDL_SCANCODE_END:
		return Key::End;
	case SDL_SCANCODE_HOME:
		return Key::Home;
	case SDL_SCANCODE_INSERT:
		return Key::Insert;
	case SDL_SCANCODE_DELETE:
		return Key::Delete;
	case SDL_SCANCODE_KP_PLUS:
		return Key::Add;
	case SDL_SCANCODE_KP_MINUS:
		return Key::Subtract;
	case SDL_SCANCODE_KP_MULTIPLY:
		return Key::Multiply;
	case SDL_SCANCODE_KP_DIVIDE:
		return Key::Divide;
	case SDL_SCANCODE_LEFT:
		return Key::Left;
	case SDL_SCANCODE_RIGHT:
		return Key::Right;
	case SDL_SCANCODE_UP:
		return Key::Up;
	case SDL_SCANCODE_DOWN:
		return Key::Down;
	case SDL_SCANCODE_KP_0:
		return Key::Numpad0;
	case SDL_SCANCODE_KP_1:
		return Key::Numpad1;
	case SDL_SCANCODE_KP_2:
		return Key::Numpad2;
	case SDL_SCANCODE_KP_3:
		return Key::Numpad3;
	case SDL_SCANCODE_KP_4:
		return Key::Numpad4;
	case SDL_SCANCODE_KP_5:
		return Key::Numpad5;
	case SDL_SCANCODE_KP_6:
		return Key::Numpad6;
	case SDL_SCANCODE_KP_7:
		return Key::Numpad7;
	case SDL_SCANCODE_KP_8:
		return Key::Numpad8;
	case SDL_SCANCODE_KP_9:
		return Key::Numpad9;
	case SDL_SCANCODE_F1:
		return Key::F1;
	case SDL_SCANCODE_F2:
		return Key::F2;
	case SDL_SCANCODE_F3:
		return Key::F3;
	case SDL_SCANCODE_F4:
		return Key::F4;
	case SDL_SCANCODE_F5:
		return Key::F5;
	case SDL_SCANCODE_F6:
		return Key::F6;
	case SDL_SCANCODE_F7:
		return Key::F7;
	case SDL_SCANCODE_F8:
		return Key::F8;
	case SDL_SCANCODE_F9:
		return Key::F9;
	case SDL_SCANCODE_F10:
		return Key::F10;
	case SDL_SCANCODE_F11:
		return Key::F11;
	case SDL_SCANCODE_F12:
		return Key::F12;
	case SDL_SCANCODE_F13:
		return Key::F13;
	case SDL_SCANCODE_F14:
		return Key::F14;
	case SDL_SCANCODE_F15:
		return Key::F15;
	case SDL_SCANCODE_PAUSE:
		return Key::Pause;
	}
	return Key::Unknown;
}

INTERNAL bool convertEvent(SDL_Event& e, Event& event)
{
	if (e.type == SDL_WINDOWEVENT)
	{
		if (e.window.event == SDL_WINDOWEVENT_RESIZED)
		{
			event.type = Event::Resized;
			event.size.width = e.window.data1;
			event.size.height = e.window.data2;

			return true;
		}

		if (e.window.event == SDL_WINDOWEVENT_CLOSE)
		{
			event.type = Event::Closed;
			return true;
		}

		if (e.window.event == SDL_WINDOWEVENT_FOCUS_GAINED)
		{
			event.type = Event::GainedFocus;
			return true;
		}

		if (e.window.event == SDL_WINDOWEVENT_FOCUS_LOST)
		{
			event.type = Event::LostFocus;
			return true;
		}

		if (e.window.event == SDL_WINDOWEVENT_MOVED)
		{
			event.type = Event::Moved;
			event.move.x = e.window.data1;
			event.move.y = e.window.data2;

			return true;
		}
	}

	if (e.type == SDL_KEYDOWN)
	{
		event.type = Event::KeyPressed;
		event.key.code = convertFromSDL_ScanCode(e.key.keysym.scancode);
		u16 mod{e.key.keysym.mod};
		if (mod & KMOD_ALT)
			event.key.alt = true;
		if (mod & KMOD_CTRL)
			event.key.ctrl = true;
		if (mod & KMOD_SHIFT)
			event.key.shift = true;
		if (mod & KMOD_GUI)
			event.key.system = true;
		if (mod & KMOD_CAPS)
			event.key.capsLock = true;
		if (mod & KMOD_NUM)
			event.key.numLock = true;
		return true;
	}

	if (e.type == SDL_KEYUP)
	{
		event.type = Event::KeyReleased;
		event.key.code = convertFromSDL_ScanCode(e.key.keysym.scancode);
		u16 mod{e.key.keysym.mod};
		if (mod & KMOD_ALT)
			event.key.alt = true;
		if (mod & KMOD_CTRL)
			event.key.ctrl = true;
		if (mod & KMOD_SHIFT)
			event.key.shift = true;
		if (mod & KMOD_GUI)
			event.key.system = true;
		if (mod & KMOD_CAPS)
			event.key.capsLock = true;
		if (mod & KMOD_NUM)
			event.key.numLock = true;
		return true;
	}

	if (e.type == SDL_MOUSEMOTION)
	{
		event.type = Event::MouseMoved;
		event.mouseMove.x = e.motion.x;
		event.mouseMove.y = e.motion.y;

		return true;
	}

	if (e.type == SDL_MOUSEBUTTONDOWN)
	{
		event.type = Event::MouseButtonPressed;
		event.mouseButton.button = (Input::Mouse)e.button.button;
		event.mouseButton.clicks = e.button.clicks;

		event.mouseMove.x = e.button.x;
		event.mouseMove.y = e.button.y;

		return true;
	}

	if (e.type == SDL_MOUSEBUTTONUP)
	{
		event.type = Event::MouseButtonReleased;
		event.mouseButton.button = (Input::Mouse)e.button.button;
		event.mouseButton.clicks = e.button.clicks;

		event.mouseMove.x = e.button.x;
		event.mouseMove.y = e.button.y;

		return true;
	}

	if (e.type == SDL_MOUSEWHEEL)
	{
		event.type = Event::MouseWheelScrolled;
		event.mouseWheelScroll.deltaX = e.wheel.x;
		event.mouseWheelScroll.deltaY = e.wheel.y;

		return true;
	}

	// TODO(bill): handle Joystick events

	return false;
}

bool Window::pollEvent(Event& event)
{
	SDL_Event e;
	if (!SDL_PollEvent(&e))
		return false;

	return convertEvent(e, event);
}

bool Window::waitEvent(Event& event)
{
	SDL_Event e;
	if (!SDL_WaitEvent(&e))
		return false;

	return convertEvent(e, event);
}
} // namespace Dunjun
