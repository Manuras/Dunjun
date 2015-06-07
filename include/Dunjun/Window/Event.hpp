#ifndef DUNJUN_WINDOW_EVENT_HPP
#define DUNJUN_WINDOW_EVENT_HPP

#include <Dunjun/Window/Input.hpp>

namespace Dunjun
{
struct Event
{
	struct SizeEvent
	{
		u32 width;
		u32 height;
	};

	struct MoveEvent
	{
		s32 x;
		s32 y;
	};

	struct KeyEvent
	{
		Input::Key code;
		bool alt;
		bool ctrl;
		bool shift;
		bool system;
		bool capsLock;
		bool numLock;
	};

	// TODO(bill): TextEvents

	struct MouseMoveEvent
	{
		s32 x;
		s32 y;
	};

	struct MouseButtonEvent
	{
		Input::Mouse button;
		u8 clicks; // 1 for single-click, 2 for double-click, etc.
		s32 x;
		s32 y;
	};

	struct MouseWheelScrollEvent
	{
		s32 deltaX;
		s32 deltaY;
	};

	// TODO(bill): Joystick events
	// TODO(bill): Controller events
	// TODO(bill): Drag and Drop Events
	// TODO(bill): Clipboard Events

	struct ControllerButtonEvent
	{
		u32 index;
		Input::ControllerButton button;
	};

	struct ControllerConnectEvent
	{
		u32 index;
	};

	struct ControllerAxisEvent
	{
		u32 index;
		Input::ControllerAxis axis;
		f32 value;
	};

	enum EventType
	{
		Unknown, // A type that is not supported yet

		Closed,
		Resized,
		LostFocus,
		GainedFocus,
		Moved,

		KeyPressed,
		KeyReleased,

		MouseWheelScrolled,
		MouseButtonPressed,
		MouseButtonReleased,
		MouseMoved,
		MouseEntered,
		MouseLeft,

		ControllerButtonPressed,
		ControllerButtonReleased,

		ControllerConnected,
		ControllerDisconnected,
		ControllerRemapped,

		ControllerAxisMoved,

		// TODO(bill): Implement all the event types possible

		Count // Keep last - total number of event types
	};

	EventType type;

	union
	{
		SizeEvent             size;
		MoveEvent             move;
		KeyEvent              key;
		MouseMoveEvent        mouseMove;
		MouseButtonEvent      mouseButton;
		MouseWheelScrollEvent mouseWheelScroll;

		// TODO(bill): Joystick event types
		ControllerConnectEvent controller;
		ControllerButtonEvent controllerButton;
		ControllerAxisEvent   controllerAxis;

	};
};
} // namespace Dunjun

#endif
