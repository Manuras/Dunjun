#include <Dunjun/Game.hpp>

int main(int argc, char** argv)
{
	Dunjun::Game::init();
	Dunjun::Game::run();
	Dunjun::Game::cleanup();

	return 0;
}
