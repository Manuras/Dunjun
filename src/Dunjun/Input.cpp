#include <Dunjun/Input.hpp>

#include <Dunjun/Game.hpp>

namespace Dunjun
{
namespace Input
{
	KeyState getKey(Key key)
	{
		return static_cast<KeyState>(glfwGetKey(Game::getGlfwWindow(), key));
	}

	void setInputMode(InputMode mode, int value)
	{
		int m = 0;
		if (mode == InputMode::Cursor)
			m = GLFW_CURSOR;
		if (mode == InputMode::StickyKeys)
			m = GLFW_STICKY_KEYS;
		if (mode == InputMode::StickyMouseButtons)
			m = GLFW_STICKY_MOUSE_BUTTONS;


		glfwSetInputMode(Game::getGlfwWindow(),
						 m, value);
	}

	Vector2 getCursorPosition()
	{
		f64 x, y;
		glfwGetCursorPos(Game::getGlfwWindow(), &x, &y);

		return Vector2(x, y);
	}

	void setCursorPosition(const Vector2& pos)
	{
		glfwSetCursorPos(Game::getGlfwWindow(),
						 static_cast<f64>(pos.x),
						 static_cast<f64>(pos.y));
	}

} // namespace Input
} // namespace Dunjun
