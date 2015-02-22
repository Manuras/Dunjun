#ifndef DUNJUN_GAMEPAD_HPP
#define DUNJUN_GAMEPAD_HPP

// TODO(bill) IMPORTANT(bill): This is Windows specific code.
//                             Please fix soon to be platform independent.

// TODO(bill): Remove XInput only controller

#include <Dunjun/Math.hpp>
#include <Dunjun/Common.hpp>

#define WIN32_LEAN_AND_MEAN
#define WIN32_MEAN_AND_LEAN
#include <Windows.h>

#include <Xinput.h>

namespace Dunjun
{
	enum class GamepadButton : u16
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

class Gamepad
{
public:
	explicit Gamepad(u32 index);

	virtual ~Gamepad();

	void reset();
	bool isConnected();
	// Can take values from 0-1
	void setVibration(f32 leftMotor, f32 rightMotor);
	void update();

	struct State
	{
		b8 buttons[(u16)GamepadButton::Count];
		Vector2 leftThumbstick;
		Vector2 rightThumbstick;
		f32 leftTrigger;
		f32 rightTrigger;
	} state;

	ReadOnly<u32, Gamepad> index;
private:
	XINPUT_STATE m_xinputState;
};
} // namespace Dunjun

#endif
