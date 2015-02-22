#ifndef DUNJUN_GAME_HPP
#define DUNJUN_GAME_HPP

#include <Dunjun/Math.hpp>

struct GLFWwindow;

namespace Dunjun
{
namespace Game
{
	void init();
	void run();
	void cleanup();

	GLFWwindow* getGlfwWindow();
	Vector2 getWindowSize();

} // namespace Game
} // namespace Dunjun

#endif 
