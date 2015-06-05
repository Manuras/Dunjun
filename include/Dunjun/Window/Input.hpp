#ifndef DUNJUN_WINDOW_INPUT_HPP
#define DUNJUN_WINDOW_INPUT_HPP

#include <Dunjun/Common.hpp>

#include <Dunjun/System/OpenGL.hpp>
#include <Dunjun/Window/Window.hpp>

#include <Dunjun/Math.hpp>
#include <Dunjun/System/Time.hpp>

#include <vector>
#include <string>

namespace Dunjun
{
namespace Input
{
enum class Key
{
	Unknown = -1, // Unhandled key
	A = 0,        // The A key
	B,            // The B key
	C,            // The C key
	D,            // The D key
	E,            // The E key
	F,            // The F key
	G,            // The G key
	H,            // The H key
	I,            // The I key
	J,            // The J key
	K,            // The K key
	L,            // The L key
	M,            // The M key
	N,            // The N key
	O,            // The O key
	P,            // The P key
	Q,            // The Q key
	R,            // The R key
	S,            // The S key
	T,            // The T key
	U,            // The U key
	V,            // The V key
	W,            // The W key
	X,            // The X key
	Y,            // The Y key
	Z,            // The Z key
	Num0,         // The 0 key
	Num1,         // The 1 key
	Num2,         // The 2 key
	Num3,         // The 3 key
	Num4,         // The 4 key
	Num5,         // The 5 key
	Num6,         // The 6 key
	Num7,         // The 7 key
	Num8,         // The 8 key
	Num9,         // The 9 key
	Escape,       // The Escape key
	LControl,     // The left Control key
	LShift,       // The left Shift key
	LAlt,         // The left Alt key
	LSystem,      // The left OS specific key: window (Windows and Linux), apple (MacOS X), ...
	RControl,     // The right Control key
	RShift,       // The right Shift key
	RAlt,         // The right Alt key
	RSystem,     // The right OS specific key: window (Windows and Linux), apple (MacOS X), ...
	Menu,        // The Menu key
	LBracket,    // The [ key
	RBracket,    // The ] key
	SemiColon,   // The ; key
	Comma,       // The , key
	Period,      // The . key
	Apostrophe,  // The ' key
	Slash,       // The / key
	BackSlash,   // The \ key
	Equal,       // The = key
	Minus,       // The - key
	Space,       // The Space key
	Return,      // The Return key
	BackSpace,   // The Backspace key
	Tab,         // The Tabulation key
	GraveAccent, // The ` key
	World1,      // Non-US #1
	World2,      // Non-US #2
	PageUp,      // The Page up key
	PageDown,    // The Page down key
	End,         // The End key
	Home,        // The Home key
	Insert,      // The Insert key
	Delete,      // The Delete key
	Add,         // The + key
	Subtract,    // The - key
	Multiply,    // The * key
	Divide,      // The / key
	Left,        // Left arrow
	Right,       // Right arrow
	Up,          // Up arrow
	Down,        // Down arrow
	Numpad0,     // The numpad 0 key
	Numpad1,     // The numpad 1 key
	Numpad2,     // The numpad 2 key
	Numpad3,     // The numpad 3 key
	Numpad4,     // The numpad 4 key
	Numpad5,     // The numpad 5 key
	Numpad6,     // The numpad 6 key
	Numpad7,     // The numpad 7 key
	Numpad8,     // The numpad 8 key
	Numpad9,     // The numpad 9 key
	NumpadEnter, // The numpad Enter key
	F1,          // The F1 key
	F2,          // The F2 key
	F3,          // The F3 key
	F4,          // The F4 key
	F5,          // The F5 key
	F6,          // The F6 key
	F7,          // The F7 key
	F8,          // The F8 key
	F9,          // The F9 key
	F10,         // The F10 key
	F11,         // The F11 key
	F12,         // The F12 key
	F13,         // The F13 key
	F14,         // The F14 key
	F15,         // The F15 key
	Pause,       // The Pause key

	KeyCount     // Keep last -- the total number of keyboard keys
};

enum class Mouse
{
	Button1 = 1,
	Button2 = 2,
	Button3 = 3,
	Button4 = 4,
	Button5 = 5,
	Button6 = 6,
	Button7 = 7,
	Button8 = 8,

	ButtonLeft = Button1,
	ButtonRight = Button2,
	ButtonMiddle = Button3,
};


enum class ControllerButton : u32
{
	A = 0,
	B,
	X,
	Y,

	Back,
	Guide,
	Start,

	LeftStick,
	RightStick,

	LeftShoulder,
	RightShoulder,

	DpadUp,
	DpadDown,
	DpadLeft,
	DpadRight,

	Count,
};

enum class ControllerAxis
{
	LeftX = 0,
	LeftY,

	RightX,
	RightY,

	TriggerLeft,
	TriggerRight,

	Count,
};

enum class CursorMode
{
	Normal,
	Hidden,
	Disabled,
};

void setup();
void cleanup();

void setCursorMode(CursorMode mode);
void setStickyKeys(bool sticky);
void setStickyMouseButtons(bool sticky);

bool isKeyPressed(Key key);

Vector2 getCursorPosition();
Vector2 getCursorPosition(const Window& relativeTo);

void setCursorPosition(const Window& relativeTo, const Vector2& pos);

bool isMouseButtonPressed(Mouse button);

// Vector2 getScrollOffset();

bool isControllerPresent(u32 controllerIndex);
bool isControllerButtonPressed(u32 controllerIndex,
							   ControllerButton button);
f32 getControllerAxis(u32 controllerIndex, ControllerAxis axis);


// TODO(bill): Get type of gamepad rather than name
// NOTE(bill): Strings are UTF-8
std::string getControllerName(u32 controllerIndex);
void setControllerVibration(u32 controllerIndex, f32 leftMotor, f32 rightMotor);

// NOTE(bill): Strings are UTF-8
std::string getClipboardString();
void setClipboardString(const std::string& str);
} // namespace Input
} // namespace Dunjun

#endif
