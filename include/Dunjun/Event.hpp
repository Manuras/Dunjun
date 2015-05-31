#ifndef DUNJUN_EVENT_HPP
#define DUNJUN_EVENT_HPP

#include <Dunjun/Input.hpp>

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

	enum EventType
	{
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

		// TODO(bill): EventTypes:
		// Joystick/Controllers

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
	};
};
} // namespace Dunjun

#endif