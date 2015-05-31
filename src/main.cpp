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
#include <Dunjun/Input.hpp>

using namespace Dunjun;

int main(int argc, char** argv)
{
	SDL_Init(SDL_INIT_EVERYTHING);

	Window window;
	window.create({854, 480}, "Dunjun");
	
	while (window.isOpen())
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				window.close();
		}


		if (Input::isKeyPressed(Input::Key::Escape))
			window.close();
		
		//if (Input::isMouseButtonPressed(Input::Mouse::Button1))
		//	window.close();


		window.display();
	}


	window.close();

	SDL_Quit();

	return 0;
}
