#ifndef DUNJUN_INPUT_HPP
#define DUNJUN_INPUT_HPP

#include <Dunjun/Common.hpp>

#include <Dunjun/OpenGL.hpp>
#include <GLFW/glfw3.h>

#include <Dunjun/Math.hpp>

#include <vector>
#include <string>

namespace Dunjun
{
namespace Input
{
	using Key = int;
	
	enum MouseButton
	{
		MouseButton_1 = 0,
		MouseButton_2 = 1,
		MouseButton_3 = 2,
		MouseButton_4 = 3,
		MouseButton_5 = 4,
		MouseButton_6 = 5,
		MouseButton_7 = 6,
		MouseButton_8 = 7,

		MouseButton_Last = MouseButton_8,

		MouseButton_Left = MouseButton_1,
		MouseButton_Right = MouseButton_2,
		MouseButton_Middle = MouseButton_3,
	};


	enum State
	{
		Release = 0,
		Press = 1,
	};

	struct GamepadAxes
	{
		Vector2 leftThumbstick;
		Vector2 rightThumbstick;
		f32 leftTrigger;
		f32 rightTrigger;
	};

	enum class XboxButton
	{
		DpadUp = 0,
		DpadDown = 1,
		DpadLeft = 2,
		DpadRight = 3,

		Start = 4,
		Back = 5,

		LeftThumb = 6,
		RightThumb = 7,

		LeftShoulder = 8,
		RightShoulder = 9,

		A = 10,
		B = 11,
		X = 12,
		Y = 13,

		Count = 14,
	};

	enum GamepadId
	{
		Gamepad_1 = 0,
		Gamepad_2 = 1,
		Gamepad_3 = 2,
		Gamepad_4 = 3,

		Gamepad_MaxCount = 4,
	};

	using GamepadButtons = std::vector<b8>;

	enum class CursorMode
	{
		Normal,
		Hidden,
		Disabled,
	};

	void setup();

	void setCursorMode(CursorMode mode);
	void setStickyKeys(bool sticky);
	void setStickyMouseButtons(bool sticky);

	// TODO(bill): Enums for Keys
	State getKey(Key key);

	Vector2 getCursorPosition();
	void setCursorPosition(const Vector2& pos);

	State getMouseButton(MouseButton button);
	
	Vector2 getScrollOffset();


	f64 getTime();
	void setTime(f64 time);
	



	// TODO(bill) IMPORTANT(bill): Handle other platforms rather than just
	//                             Windows. I.e. not XInput
	void updateGamepads();

	bool isGamepadPresent(GamepadId gamepadId);
	GamepadAxes getGamepadAxes(GamepadId gamepadId);
	GamepadButtons getGamepadButtons(GamepadId gamepadId);
	std::string getGamepadName(GamepadId gamepadId);

} // namespace Input
} // namespace Dunjun

#endif
