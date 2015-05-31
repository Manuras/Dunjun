//#include <Dunjun/Game.hpp>
//
//int main(int argc, char** argv)
//{
//	Dunjun::Game::init();
//	Dunjun::Game::run();
//	Dunjun::Game::cleanup();
//
//	return 0;
//}

#include <Dunjun/Window.hpp>

using namespace Dunjun;

int main(int argc, char** argv)
{
	SDL_Init(SDL_INIT_EVERYTHING);

	Window window;
	window.create({854, 480}, "Dunjun", Style::Visible | Style::Resizable);

	Time::sleep(seconds(2));


	window.close();

	SDL_Quit();

	return 0;
}
