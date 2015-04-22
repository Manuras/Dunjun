#include <Dunjun/Config.hpp>
#ifdef DUNJUN_SYSTEM_OSX
#include <Dunjun/Input.hpp>

#include <Dunjun/Window.hpp>
#include <Dunjun/Game.hpp>

#include <chrono>

namespace Dunjun
{
namespace Input
{

void setup()
{
	// glfwSetScrollCallback(Game::getGlfwWindow(), scrollCallback);

	for (int i = 0; i < Gamepad_Count; i++)
	{
		// memset(&g_gamepadStates[i], 0, sizeof(XINPUT_STATE));
		if (isGamepadPresent((GamepadId)i))
			setGamepadVibration((GamepadId)i, 0, 0);
	}

	setStickyKeys(true);
	setStickyMouseButtons(true);
}

void cleanup()
{
	for (int i = 0; i < Gamepad_Count; i++)
	{
		if (isGamepadPresent((GamepadId)i))
			setGamepadVibration((GamepadId)i, 0, 0);
	}
}

void setCursorMode(CursorMode mode)
{
	if (mode == CursorMode::Normal)
		glfwSetInputMode(Window::g_ptr, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	if (mode == CursorMode::Hidden)
		glfwSetInputMode(Window::g_ptr, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	if (mode == CursorMode::Disabled)
		glfwSetInputMode(Window::g_ptr, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void setStickyKeys(bool sticky)
{
	glfwSetInputMode(Window::g_ptr, GLFW_STICKY_KEYS, sticky);
}

void setStickyMouseButtons(bool sticky)
{
	glfwSetInputMode(Window::g_ptr, GLFW_STICKY_MOUSE_BUTTONS, sticky);
}

// Keyboard
bool isKeyPressed(Key key)
{
	int code = 0;

	switch (key)
	{
	default:
		code = 0;
		break;
	case Key::A:
		code = GLFW_KEY_A;
		break;
	case Key::B:
		code = GLFW_KEY_B;
		break;
	case Key::C:
		code = GLFW_KEY_C;
		break;
	case Key::D:
		code = GLFW_KEY_D;
		break;
	case Key::E:
		code = GLFW_KEY_E;
		break;
	case Key::F:
		code = GLFW_KEY_F;
		break;
	case Key::G:
		code = GLFW_KEY_G;
		break;
	case Key::H:
		code = GLFW_KEY_H;
		break;
	case Key::I:
		code = GLFW_KEY_I;
		break;
	case Key::J:
		code = GLFW_KEY_J;
		break;
	case Key::K:
		code = GLFW_KEY_K;
		break;
	case Key::L:
		code = GLFW_KEY_L;
		break;
	case Key::M:
		code = GLFW_KEY_M;
		break;
	case Key::N:
		code = GLFW_KEY_N;
		break;
	case Key::O:
		code = GLFW_KEY_O;
		break;
	case Key::P:
		code = GLFW_KEY_P;
		break;
	case Key::Q:
		code = GLFW_KEY_Q;
		break;
	case Key::R:
		code = GLFW_KEY_R;
		break;
	case Key::S:
		code = GLFW_KEY_S;
		break;
	case Key::T:
		code = GLFW_KEY_T;
		break;
	case Key::U:
		code = GLFW_KEY_U;
		break;
	case Key::V:
		code = GLFW_KEY_V;
		break;
	case Key::W:
		code = GLFW_KEY_W;
		break;
	case Key::X:
		code = GLFW_KEY_X;
		break;
	case Key::Y:
		code = GLFW_KEY_Y;
		break;
	case Key::Z:
		code = GLFW_KEY_Z;
		break;
	case Key::Num0:
		code = GLFW_KEY_0;
		break;
	case Key::Num1:
		code = GLFW_KEY_1;
		break;
	case Key::Num2:
		code = GLFW_KEY_2;
		break;
	case Key::Num3:
		code = GLFW_KEY_3;
		break;
	case Key::Num4:
		code = GLFW_KEY_4;
		break;
	case Key::Num5:
		code = GLFW_KEY_5;
		break;
	case Key::Num6:
		code = GLFW_KEY_6;
		break;
	case Key::Num7:
		code = GLFW_KEY_7;
		break;
	case Key::Num8:
		code = GLFW_KEY_8;
		break;
	case Key::Num9:
		code = GLFW_KEY_9;
		break;
	case Key::Escape:
		code = GLFW_KEY_ESCAPE;
		break;
	case Key::LControl:
		code = GLFW_KEY_LEFT_CONTROL;
		break;
	case Key::LShift:
		code = GLFW_KEY_LEFT_SHIFT;
		break;
	case Key::LAlt:
		code = GLFW_KEY_LEFT_ALT;
		break;
	case Key::LSystem:
		code = GLFW_KEY_LEFT_SUPER;
		break;
	case Key::RControl:
		code = GLFW_KEY_RIGHT_CONTROL;
		break;
	case Key::RShift:
		code = GLFW_KEY_RIGHT_SHIFT;
		break;
	case Key::RAlt:
		code = GLFW_KEY_RIGHT_ALT;
		break;
	case Key::RSystem:
		code = GLFW_KEY_RIGHT_SUPER;
		break;
	case Key::Menu:
		code = GLFW_KEY_MENU;
		break;
	case Key::LBracket:
		code = GLFW_KEY_LEFT_BRACKET;
		break;
	case Key::RBracket:
		code = GLFW_KEY_RIGHT_BRACKET;
		break;
	case Key::SemiColon:
		code = GLFW_KEY_SEMICOLON;
		break;
	case Key::Comma:
		code = GLFW_KEY_COMMA;
		break;
	case Key::Period:
		code = GLFW_KEY_PERIOD;
		break;
	case Key::Apostrophe:
		code = GLFW_KEY_APOSTROPHE;
		break;
	case Key::Slash:
		code = GLFW_KEY_SLASH;
		break;
	case Key::BackSlash:
		code = GLFW_KEY_BACKSLASH;
		break;
	case Key::Equal:
		code = GLFW_KEY_EQUAL;
		break;
	case Key::Minus:
		code = GLFW_KEY_MINUS;
		break;
	case Key::Space:
		code = GLFW_KEY_SPACE;
		break;
	case Key::Return:
		code = GLFW_KEY_ENTER;
		break;
	case Key::BackSpace:
		code = GLFW_KEY_BACKSPACE;
		break;
	case Key::Tab:
		code = GLFW_KEY_TAB;
		break;
	case Key::GraveAccent:
		code = GLFW_KEY_GRAVE_ACCENT;
		break;
	case Key::World1:
		code = GLFW_KEY_WORLD_1;
		break;
	case Key::World2:
		code = GLFW_KEY_WORLD_2;
		break;
	case Key::PageUp:
		code = GLFW_KEY_PAGE_UP;
		break;
	case Key::PageDown:
		code = GLFW_KEY_PAGE_DOWN;
		break;
	case Key::End:
		code = GLFW_KEY_END;
		break;
	case Key::Home:
		code = GLFW_KEY_HOME;
		break;
	case Key::Insert:
		code = GLFW_KEY_INSERT;
		break;
	case Key::Delete:
		code = GLFW_KEY_DELETE;
		break;
	case Key::Add:
		code = GLFW_KEY_KP_ADD;
		break;
	case Key::Subtract:
		code = GLFW_KEY_KP_SUBTRACT;
		break;
	case Key::Multiply:
		code = GLFW_KEY_KP_MULTIPLY;
		break;
	case Key::Divide:
		code = GLFW_KEY_KP_DIVIDE;
		break;
	case Key::Left:
		code = GLFW_KEY_LEFT;
		break;
	case Key::Right:
		code = GLFW_KEY_RIGHT;
		break;
	case Key::Up:
		code = GLFW_KEY_UP;
		break;
	case Key::Down:
		code = GLFW_KEY_DOWN;
		break;
	case Key::Numpad0:
		code = GLFW_KEY_KP_0;
		break;
	case Key::Numpad1:
		code = GLFW_KEY_KP_1;
		break;
	case Key::Numpad2:
		code = GLFW_KEY_KP_2;
		break;
	case Key::Numpad3:
		code = GLFW_KEY_KP_3;
		break;
	case Key::Numpad4:
		code = GLFW_KEY_KP_4;
		break;
	case Key::Numpad5:
		code = GLFW_KEY_KP_5;
		break;
	case Key::Numpad6:
		code = GLFW_KEY_KP_6;
		break;
	case Key::Numpad7:
		code = GLFW_KEY_KP_7;
		break;
	case Key::Numpad8:
		code = GLFW_KEY_KP_8;
		break;
	case Key::Numpad9:
		code = GLFW_KEY_KP_9;
		break;
	case Key::F1:
		code = GLFW_KEY_F1;
		break;
	case Key::F2:
		code = GLFW_KEY_F2;
		break;
	case Key::F3:
		code = GLFW_KEY_F3;
		break;
	case Key::F4:
		code = GLFW_KEY_F4;
		break;
	case Key::F5:
		code = GLFW_KEY_F5;
		break;
	case Key::F6:
		code = GLFW_KEY_F6;
		break;
	case Key::F7:
		code = GLFW_KEY_F7;
		break;
	case Key::F8:
		code = GLFW_KEY_F8;
		break;
	case Key::F9:
		code = GLFW_KEY_F9;
		break;
	case Key::F10:
		code = GLFW_KEY_F10;
		break;
	case Key::F11:
		code = GLFW_KEY_F11;
		break;
	case Key::F12:
		code = GLFW_KEY_F12;
		break;
	case Key::F13:
		code = GLFW_KEY_F13;
		break;
	case Key::F14:
		code = GLFW_KEY_F14;
		break;
	case Key::F15:
		code = GLFW_KEY_F15;
		break;
	case Key::Pause:
		code = GLFW_KEY_PAUSE;
		break;

		// TODO(bill): Implement Extra Keys
		// 		case Key::Tilde:
		// 		{
		// #if defined(_WIN32) // Windows

		// #elif defined(__APPLE__) && defined(__MACH__) // Mac OS X

		// #else // UNIX/POSIX

		// #endif
		// 		}
		// 		break;
	}

	if (code == 0)
		return false;

	return static_cast<bool>(glfwGetKey(Window::g_ptr, code));
}

// Cursor
Vector2 getCursorPosition()
{
	f64 x, y;
	glfwGetCursorPos(Window::g_ptr, &x, &y);

	return Vector2(x, y);
}

void setCursorPosition(const Vector2& pos)
{
	glfwSetCursorPos(
	    Window::g_ptr, static_cast<f64>(pos.x), static_cast<f64>(pos.y));
}

// Mouse
bool isMouseButtonPressed(Mouse button)
{
	return static_cast<bool>(glfwGetMouseButton(Window::g_ptr, (int)button));
}

// Vector2 getScrollOffset() { return Vector2(g_scrollX, g_scrollY); }

// Time
Time getTime()
{ 
	auto now = std::chrono::high_resolution_clock::now().time_since_epoch();

	return microseconds(std::chrono::duration_cast<std::chrono::microseconds>(now).count());
}

// Gamepads
void updateGamepads()
{
	for (usize i = 0; i < Gamepad_Count; i++)
		isGamepadPresent((GamepadId)i);
}

bool isGamepadPresent(GamepadId gamepadId)
{
	return glfwJoystickPresent(GLFW_JOYSTICK_1 + (int)gamepadId);
}

GamepadAxes getGamepadAxes(GamepadId gamepadId)
{
	GamepadAxes axes;

	int count = 0;
	const f32* glfwAxes = glfwGetJoystickAxes(GLFW_JOYSTICK_1 + (int)gamepadId, &count);

	if (count >= 3)
	{
		axes.leftThumbstick = Vector2(glfwAxes[0], glfwAxes[1]);
		axes.rightThumbstick = Vector2(glfwAxes[2], glfwAxes[3]);
		// TODO(bill): get the trigger values for an xbox controller on OSX
		axes.leftTrigger = 0.0f;
		axes.rightTrigger = 0.0f;
	}

	return axes;
}

GamepadButtons getGamepadButtons(GamepadId gamepadId)
{
	GamepadButtons buttons((usize)XboxButton::Count);

	// TODO(bill): Get Gamepad button values for OSX

	int count = 0;
	const u8* glfwButtons = glfwGetJoystickButtons(GLFW_JOYSTICK_1 + (int)gamepadId, &count);

	buttons[(int)XboxButton::DpadUp] = false;
	buttons[(int)XboxButton::DpadDown] = false;
	buttons[(int)XboxButton::DpadLeft] = false;
	buttons[(int)XboxButton::DpadRight] = false;

	buttons[(int)XboxButton::Start] = glfwButtons[9];
	buttons[(int)XboxButton::Back] = glfwButtons[8];

	buttons[(int)XboxButton::LeftThumb] = glfwButtons[10];
	buttons[(int)XboxButton::RightThumb] = glfwButtons[11];

	buttons[(int)XboxButton::LeftShoulder] = glfwButtons[6];
	buttons[(int)XboxButton::RightShoulder] = glfwButtons[7];

	buttons[(int)XboxButton::A] = glfwButtons[2];
	buttons[(int)XboxButton::B] = glfwButtons[1];
	buttons[(int)XboxButton::X] = glfwButtons[3];
	buttons[(int)XboxButton::Y] = glfwButtons[0];

	return buttons;
}

bool isGamepadButtonPressed(GamepadId gamepadId, XboxButton button)
{
	return getGamepadButtons(gamepadId)[(usize)button];
}

std::string getGamepadName(GamepadId gamepadId)
{
	return glfwGetJoystickName(gamepadId);
}

void setGamepadVibration(GamepadId gamepadId, f32 leftMotor, f32 rightMotor)
{
	// TODO(bill): Set Gamepad vibration for OSX
}

// Clipboard
std::string getClipboardString()
{
	return glfwGetClipboardString(Window::g_ptr);
}

void setClipboardString(const std::string& str)
{
	glfwSetClipboardString(Window::g_ptr, str.c_str());
}

} // namespace Input
} // namespace Dunjun

#endif
