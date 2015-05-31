#include <Dunjun/Config.hpp>
#ifdef DUNJUN_SYSTEM_WINDOWS
#include <Dunjun/Input.hpp>

#include <Dunjun/Game.hpp>

#define VC_EXTRALEAN
#define WIN32_LEAN_AND_MEAN
#define WIN32_MEAN_AND_LEAN
#include <Windows.h>

#include <Xinput.h>

#include <SDL/SDL.h>

#include <array>
#include <chrono>

namespace Dunjun
{
namespace Input
{
GLOBAL std::array<XINPUT_STATE, Gamepad_Count> g_gamepadStates;

void setup()
{
	for (int i{0}; i < Gamepad_Count; i++)
	{
		memset(&g_gamepadStates[i], 0, sizeof(XINPUT_STATE));
		if (isGamepadPresent((GamepadId)i))
			setGamepadVibration((GamepadId)i, 0, 0);
	}

	setStickyKeys(true);
	setStickyMouseButtons(true);
}

void cleanup()
{
	for (int i{0}; i < Gamepad_Count; i++)
	{
		if (isGamepadPresent((GamepadId)i))
			setGamepadVibration((GamepadId)i, 0, 0);
	}
}

void setCursorMode(CursorMode mode)
{
	/*if (mode == CursorMode::Normal)
		glfwSetInputMode(Window::getHandle(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	if (mode == CursorMode::Hidden)
		glfwSetInputMode(Window::getHandle(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	if (mode == CursorMode::Disabled)
		glfwSetInputMode(Window::getHandle(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);*/
}

void setStickyKeys(bool sticky)
{
	//glfwSetInputMode(Window::getHandle(), GLFW_STICKY_KEYS, sticky);
}

void setStickyMouseButtons(bool sticky)
{
	//glfwSetInputMode(Window::getHandle(), GLFW_STICKY_MOUSE_BUTTONS, sticky);
}

// Keyboard
bool isKeyPressed(Key key)
{
	int code{0};

	switch (key)
	{
	default:
		code = 0;
		break;
	case Key::A:
		code = SDL_SCANCODE_A;
		break;
	case Key::B:
		code = SDL_SCANCODE_B;
		break;
	case Key::C:
		code = SDL_SCANCODE_C;
		break;
	case Key::D:
		code = SDL_SCANCODE_D;
		break;
	case Key::E:
		code = SDL_SCANCODE_E;
		break;
	case Key::F:
		code = SDL_SCANCODE_F;
		break;
	case Key::G:
		code = SDL_SCANCODE_G;
		break;
	case Key::H:
		code = SDL_SCANCODE_H;
		break;
	case Key::I:
		code = SDL_SCANCODE_I;
		break;
	case Key::J:
		code = SDL_SCANCODE_J;
		break;
	case Key::K:
		code = SDL_SCANCODE_K;
		break;
	case Key::L:
		code = SDL_SCANCODE_L;
		break;
	case Key::M:
		code = SDL_SCANCODE_M;
		break;
	case Key::N:
		code = SDL_SCANCODE_N;
		break;
	case Key::O:
		code = SDL_SCANCODE_O;
		break;
	case Key::P:
		code = SDL_SCANCODE_P;
		break;
	case Key::Q:
		code = SDL_SCANCODE_Q;
		break;
	case Key::R:
		code = SDL_SCANCODE_R;
		break;
	case Key::S:
		code = SDL_SCANCODE_S;
		break;
	case Key::T:
		code = SDL_SCANCODE_T;
		break;
	case Key::U:
		code = SDL_SCANCODE_U;
		break;
	case Key::V:
		code = SDL_SCANCODE_V;
		break;
	case Key::W:
		code = SDL_SCANCODE_W;
		break;
	case Key::X:
		code = SDL_SCANCODE_X;
		break;
	case Key::Y:
		code = SDL_SCANCODE_Y;
		break;
	case Key::Z:
		code = SDL_SCANCODE_Z;
		break;
	case Key::Num0:
		code = SDL_SCANCODE_0;
		break;
	case Key::Num1:
		code = SDL_SCANCODE_1;
		break;
	case Key::Num2:
		code = SDL_SCANCODE_2;
		break;
	case Key::Num3:
		code = SDL_SCANCODE_3;
		break;
	case Key::Num4:
		code = SDL_SCANCODE_4;
		break;
	case Key::Num5:
		code = SDL_SCANCODE_5;
		break;
	case Key::Num6:
		code = SDL_SCANCODE_6;
		break;
	case Key::Num7:
		code = SDL_SCANCODE_7;
		break;
	case Key::Num8:
		code = SDL_SCANCODE_8;
		break;
	case Key::Num9:
		code = SDL_SCANCODE_9;
		break;
	case Key::Escape:
		code = SDL_SCANCODE_ESCAPE;
		break;
	case Key::LControl:
		code = SDL_SCANCODE_LCTRL;
		break;
	case Key::LShift:
		code = SDL_SCANCODE_LSHIFT;
		break;
	case Key::LAlt:
		code = SDL_SCANCODE_LALT;
		break;
	case Key::LSystem:
		code = SDL_SCANCODE_LGUI;
		break;
	case Key::RControl:
		code = SDL_SCANCODE_RCTRL;
		break;
	case Key::RShift:
		code = SDL_SCANCODE_RSHIFT;
		break;
	case Key::RAlt:
		code = SDL_SCANCODE_RALT;
		break;
	case Key::RSystem:
		code = SDL_SCANCODE_RGUI;
		break;
	case Key::Menu:
		code = SDL_SCANCODE_MENU;
		break;
	case Key::LBracket:
		code = SDL_SCANCODE_LEFTBRACKET;
		break;
	case Key::RBracket:
		code = SDL_SCANCODE_RIGHTBRACKET;
		break;
	case Key::SemiColon:
		code = SDL_SCANCODE_SEMICOLON;
		break;
	case Key::Comma:
		code = SDL_SCANCODE_COMMA;
		break;
	case Key::Period:
		code = SDL_SCANCODE_PERIOD;
		break;
	case Key::Apostrophe:
		code = SDL_SCANCODE_APOSTROPHE;
		break;
	case Key::Slash:
		code = SDL_SCANCODE_SLASH;
		break;
	case Key::BackSlash:
		code = SDL_SCANCODE_BACKSLASH;
		break;
	case Key::Equal:
		code = SDL_SCANCODE_EQUALS;
		break;
	case Key::Minus:
		code = SDL_SCANCODE_MINUS;
		break;
	case Key::Space:
		code = SDL_SCANCODE_SPACE;
		break;
	case Key::Return:
		code = SDL_SCANCODE_RETURN;
		break;
	case Key::BackSpace:
		code = SDL_SCANCODE_BACKSPACE;
		break;
	case Key::Tab:
		code = SDL_SCANCODE_TAB;
		break;
	case Key::GraveAccent:
		code = SDL_SCANCODE_GRAVE;
		break;
	case Key::World1:
		code = 0; // TODO(bill):
		break;
	case Key::World2:
		code = 0; // TODO(bill):
		break;
	case Key::PageUp:
		code = SDL_SCANCODE_PAGEUP;
		break;
	case Key::PageDown:
		code = SDL_SCANCODE_PAGEDOWN;
		break;
	case Key::End:
		code = SDL_SCANCODE_END;
		break;
	case Key::Home:
		code = SDL_SCANCODE_HOME;
		break;
	case Key::Insert:
		code = SDL_SCANCODE_INSERT;
		break;
	case Key::Delete:
		code = SDL_SCANCODE_DELETE;
		break;
	case Key::Add:
		code = SDL_SCANCODE_KP_PLUS;
		break;
	case Key::Subtract:
		code = SDL_SCANCODE_KP_MINUS;
		break;
	case Key::Multiply:
		code = SDL_SCANCODE_KP_MULTIPLY;
		break;
	case Key::Divide:
		code = SDL_SCANCODE_KP_DIVIDE;
		break;
	case Key::Left:
		code = SDL_SCANCODE_LEFT;
		break;
	case Key::Right:
		code = SDL_SCANCODE_RIGHT;
		break;
	case Key::Up:
		code = SDL_SCANCODE_UP;
		break;
	case Key::Down:
		code = SDL_SCANCODE_DOWN;
		break;
	case Key::Numpad0:
		code = SDL_SCANCODE_KP_0;
		break;
	case Key::Numpad1:
		code = SDL_SCANCODE_KP_1;
		break;
	case Key::Numpad2:
		code = SDL_SCANCODE_KP_2;
		break;
	case Key::Numpad3:
		code = SDL_SCANCODE_KP_3;
		break;
	case Key::Numpad4:
		code = SDL_SCANCODE_KP_4;
		break;
	case Key::Numpad5:
		code = SDL_SCANCODE_KP_5;
		break;
	case Key::Numpad6:
		code = SDL_SCANCODE_KP_6;
		break;
	case Key::Numpad7:
		code = SDL_SCANCODE_KP_7;
		break;
	case Key::Numpad8:
		code = SDL_SCANCODE_KP_8;
		break;
	case Key::Numpad9:
		code = SDL_SCANCODE_KP_9;
		break;
	case Key::F1:
		code = SDL_SCANCODE_F1;
		break;
	case Key::F2:
		code = SDL_SCANCODE_F2;
		break;
	case Key::F3:
		code = SDL_SCANCODE_F3;
		break;
	case Key::F4:
		code = SDL_SCANCODE_F4;
		break;
	case Key::F5:
		code = SDL_SCANCODE_F5;
		break;
	case Key::F6:
		code = SDL_SCANCODE_F6;
		break;
	case Key::F7:
		code = SDL_SCANCODE_F7;
		break;
	case Key::F8:
		code = SDL_SCANCODE_F8;
		break;
	case Key::F9:
		code = SDL_SCANCODE_F9;
		break;
	case Key::F10:
		code = SDL_SCANCODE_F10;
		break;
	case Key::F11:
		code = SDL_SCANCODE_F11;
		break;
	case Key::F12:
		code = SDL_SCANCODE_F12;
		break;
	case Key::F13:
		code = SDL_SCANCODE_F13;
		break;
	case Key::F14:
		code = SDL_SCANCODE_F14;
		break;
	case Key::F15:
		code = SDL_SCANCODE_F15;
		break;
	case Key::Pause:
		code = SDL_SCANCODE_PAUSE;
		break;
	}

	if (code == 0)
		return false;

	const u8* state{SDL_GetKeyboardState(nullptr)};
	
	return state[code] != 0;
}

// Cursor

Vector2 getCursorPosition()
{
	// TODO(bill): get global cursor position
	int x, y;
	SDL_GetMouseState(&x, &y);

	return{(f32)x, (f32)y};
}

Vector2 getCursorPosition(const Window& relativeTo)
{
	int x, y;
	SDL_GetMouseState(&x, &y);

	return Vector2{(f32)x, (f32)y};
}

void setCursorPosition(const Window& relativeTo, const Vector2& pos)
{
	SDL_WarpMouseInWindow(relativeTo.getNativeHandle(), pos.x, pos.y);
}

// Mouse
bool isMouseButtonPressed(Mouse button)
{
	return (SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON((int)button)) != 0;
}

// Vector2 getScrollOffset() { return Vector2(g_scrollX, g_scrollY); }

// Gamepads
void updateGamepads()
{
	for (usize i{0}; i < Gamepad_Count; i++)
		isGamepadPresent((GamepadId)i);
}

bool isGamepadPresent(GamepadId gamepadId)
{
	if (gamepadId < Gamepad_Count)
		return XInputGetState(gamepadId, &g_gamepadStates[gamepadId]) == 0;
	return false;
}

GamepadAxes getGamepadAxes(GamepadId gamepadId)
{
	GamepadAxes axes;

	axes.leftTrigger = g_gamepadStates[gamepadId].Gamepad.bLeftTrigger / 255.0f;
	axes.rightTrigger =
	    g_gamepadStates[gamepadId].Gamepad.bRightTrigger / 255.0f;

	axes.leftThumbstick.x =
	    g_gamepadStates[gamepadId].Gamepad.sThumbLX / 32767.0f;
	axes.leftThumbstick.y =
	    g_gamepadStates[gamepadId].Gamepad.sThumbLY / 32767.0f;

	axes.rightThumbstick.x =
	    g_gamepadStates[gamepadId].Gamepad.sThumbRX / 32767.0f;
	axes.rightThumbstick.y =
	    g_gamepadStates[gamepadId].Gamepad.sThumbRY / 32767.0f;

	return axes;
}

GamepadButtons getGamepadButtons(GamepadId gamepadId)
{
	GamepadButtons buttons((usize)XboxButton::Count);

	buttons[(int)XboxButton::DpadUp] =
	    (g_gamepadStates[gamepadId].Gamepad.wButtons &
	     XINPUT_GAMEPAD_DPAD_UP) != 0;
	buttons[(int)XboxButton::DpadDown] =
	    (g_gamepadStates[gamepadId].Gamepad.wButtons &
	     XINPUT_GAMEPAD_DPAD_DOWN) != 0;
	buttons[(int)XboxButton::DpadLeft] =
	    (g_gamepadStates[gamepadId].Gamepad.wButtons &
	     XINPUT_GAMEPAD_DPAD_LEFT) != 0;
	buttons[(int)XboxButton::DpadRight] =
	    (g_gamepadStates[gamepadId].Gamepad.wButtons &
	     XINPUT_GAMEPAD_DPAD_RIGHT) != 0;

	buttons[(int)XboxButton::Start] =
	    (g_gamepadStates[gamepadId].Gamepad.wButtons & XINPUT_GAMEPAD_START) !=
	    0;
	buttons[(int)XboxButton::Back] =
	    (g_gamepadStates[gamepadId].Gamepad.wButtons & XINPUT_GAMEPAD_BACK) !=
	    0;

	buttons[(int)XboxButton::LeftThumb] =
	    (g_gamepadStates[gamepadId].Gamepad.wButtons &
	     XINPUT_GAMEPAD_LEFT_THUMB) != 0;
	buttons[(int)XboxButton::RightThumb] =
	    (g_gamepadStates[gamepadId].Gamepad.wButtons &
	     XINPUT_GAMEPAD_RIGHT_THUMB) != 0;

	buttons[(int)XboxButton::LeftShoulder] =
	    (g_gamepadStates[gamepadId].Gamepad.wButtons &
	     XINPUT_GAMEPAD_LEFT_SHOULDER) != 0;
	buttons[(int)XboxButton::RightShoulder] =
	    (g_gamepadStates[gamepadId].Gamepad.wButtons &
	     XINPUT_GAMEPAD_RIGHT_SHOULDER) != 0;

	buttons[(int)XboxButton::A] =
	    (g_gamepadStates[gamepadId].Gamepad.wButtons & XINPUT_GAMEPAD_A) != 0;
	buttons[(int)XboxButton::B] =
	    (g_gamepadStates[gamepadId].Gamepad.wButtons & XINPUT_GAMEPAD_B) != 0;
	buttons[(int)XboxButton::X] =
	    (g_gamepadStates[gamepadId].Gamepad.wButtons & XINPUT_GAMEPAD_X) != 0;
	buttons[(int)XboxButton::Y] =
	    (g_gamepadStates[gamepadId].Gamepad.wButtons & XINPUT_GAMEPAD_Y) != 0;

	return buttons;
}

bool isGamepadButtonPressed(GamepadId gamepadId, XboxButton button)
{
	return getGamepadButtons(gamepadId)[(usize)button];
}

std::string getGamepadName(GamepadId gamepadId)
{
	return {}; //glfwGetJoystickName(gamepadId);
}

void setGamepadVibration(GamepadId gamepadId, f32 leftMotor, f32 rightMotor)
{
	XINPUT_VIBRATION vibration;

	vibration.wLeftMotorSpeed = static_cast<WORD>(leftMotor * 0xFFFF);
	vibration.wRightMotorSpeed = static_cast<WORD>(rightMotor * 0xFFFF);

	XInputSetState((u32)gamepadId, &vibration);
}

// Clipboard
std::string getClipboardString()
{
	return{};// return glfwGetClipboardString(Window::getHandle());
}

void setClipboardString(const std::string& str)
{
	//glfwSetClipboardString(Window::getHandle(), str.c_str());
}

} // namespace Input
} // namespace Dunjun

#endif
