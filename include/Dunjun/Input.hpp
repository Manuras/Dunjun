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
	using MouseButton = int;

	enum KeyState : u32
	{
		Release = 0,
		Press = 1,
	};

	enum class InputMode : u32
	{
		Cursor,
		StickyKeys,
		StickyMouseButtons,
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

		Gamepad_maxCount = 4,
	};


	using GamepadButtons = std::vector<b8>;

	// TODO(bill): create enum for value;
	void setInputMode(InputMode mode, int value);

	// TODO(bill): Enums for Keys
	KeyState getKey(Key key);


	Vector2 getCursorPosition();
	void setCursorPosition(const Vector2& pos);

	f64 getTime();
	void setTime(f64 time);

	// TODO(bill): Handle Gamepad
	void updateGamepads();

	bool isGamepadPresent(GamepadId gamepadId);
	GamepadAxes getGamepadAxes(GamepadId gamepadId);
	GamepadButtons getGamepadButtons(GamepadId gamepadId);
	std::string getGamepadName(GamepadId gamepadId);

} // namespace Input
} // namespace Dunjun

#endif
