#include <Dunjun/Gamepad.hpp>

namespace Dunjun
{
	Gamepad::Gamepad(u32 index)
	: index(index)
	{
		reset();
	}

	Gamepad::~Gamepad()
	{
		if (isConnected())
			setVibration(0, 0);
	}

	void Gamepad::reset()
	{
		ZeroMemory(&m_xinputState, sizeof(XINPUT_STATE));
		if (XInputGetState(index, &m_xinputState) == ERROR_SUCCESS)
		{

		}

		for (auto& button : state.buttons)
			button = false;
		state.leftThumbstick = state.rightThumbstick = {0, 0};
		state.leftTrigger = state.rightTrigger = 0;
	}

	bool Gamepad::isConnected()
	{
		DWORD result = XInputGetState((DWORD)index, &m_xinputState);

		return result == 0;
	}

	// Can take values from 0-1
	void Gamepad::setVibration(f32 leftMotor, f32 rightMotor)
	{
		XINPUT_VIBRATION vibration;
		vibration.wLeftMotorSpeed = static_cast<WORD>(leftMotor * 0xFFFF);
		vibration.wRightMotorSpeed = static_cast<WORD>(rightMotor * 0xFFFF);

		XInputSetState(index, &vibration);
	}

	void Gamepad::update()
	{
		return;
		state.buttons[(u16)GamepadButton::DpadUp] =
			(m_xinputState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP) > 0;
		state.buttons[(u16)GamepadButton::DpadDown] =
			(m_xinputState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) > 0;
		state.buttons[(u16)GamepadButton::DpadLeft] =
			(m_xinputState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) > 0;
		state.buttons[(u16)GamepadButton::DpadRight] =
			(m_xinputState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) > 0;

		state.buttons[(u16)GamepadButton::Start] =
			(m_xinputState.Gamepad.wButtons & XINPUT_GAMEPAD_START) > 0;
		state.buttons[(u16)GamepadButton::Back] =
			(m_xinputState.Gamepad.wButtons & XINPUT_GAMEPAD_BACK) > 0;

		state.buttons[(u16)GamepadButton::LeftThumb] =
			(m_xinputState.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB) > 0;
		state.buttons[(u16)GamepadButton::RightThumb] =
			(m_xinputState.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB) > 0;

		state.buttons[(u16)GamepadButton::LeftShoulder] =
			(m_xinputState.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) > 0;
		state.buttons[(u16)GamepadButton::RightShoulder] =
			(m_xinputState.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) > 0;


		state.buttons[(u16)GamepadButton::A] =
			(m_xinputState.Gamepad.wButtons & XINPUT_GAMEPAD_A) > 0;
		state.buttons[(u16)GamepadButton::B] =
			(m_xinputState.Gamepad.wButtons & XINPUT_GAMEPAD_B) > 0;
		state.buttons[(u16)GamepadButton::X] =
			(m_xinputState.Gamepad.wButtons & XINPUT_GAMEPAD_X) > 0;
		state.buttons[(u16)GamepadButton::Y] =
			(m_xinputState.Gamepad.wButtons & XINPUT_GAMEPAD_Y) > 0;

		state.leftTrigger = m_xinputState.Gamepad.bLeftTrigger / 255.0f;
		state.rightTrigger = m_xinputState.Gamepad.bRightTrigger / 255.0f;


		state.leftThumbstick.x = m_xinputState.Gamepad.sThumbLX / 32767.0f;
		state.leftThumbstick.y = m_xinputState.Gamepad.sThumbLY / 32767.0f;

		state.rightThumbstick.x = m_xinputState.Gamepad.sThumbRX / 32767.0f;
		state.rightThumbstick.y = m_xinputState.Gamepad.sThumbRY / 32767.0f;
	}
} // namespace Dunjun
