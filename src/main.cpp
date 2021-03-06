
// For Ludum Dare 33 : You are the Monster

// By Tristan Macdonald (Lasty)
//

// Local includes
#include "game.h"


// SDL2 includes
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#ifdef __WIN32__
	#undef main
#endif

// Standard includes
#include <stdexcept>
#include <memory>
#include <fstream>
#include <iostream>


void InitSDL2()
{
	auto sdl_init = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
	if (sdl_init < 0)
	{
		throw std::runtime_error("SDL Call failed");
	}

	auto ttf_init = TTF_Init();
	if (ttf_init < 0)
	{
		throw std::runtime_error("SDL TTF init  failed");
	}

	auto image_init = IMG_Init(0);
	if (image_init < 0)
	{
		throw std::runtime_error("SDL IMG  init  failed");
	}

	auto mixer_init = Mix_Init(0);
	if (mixer_init < 0)
	{
		throw std::runtime_error("SDL IMG  init  failed");
	}
}

void QuitSDL2()
{
	SDL_Quit();
}


//Create window and Game class object, run event loop
void RunGame(std::string data_path)
{
	auto win_flags = SDL_WINDOW_RESIZABLE;

	auto window = std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)>
		{SDL_CreateWindow("LD33 Monster", 50, 50, 1200, 800, win_flags), SDL_DestroyWindow};

	Game game{data_path, window.get()};

	bool running = true;
	Uint32 last_time = SDL_GetTicks();

	Uint32 fps_timer = SDL_GetTicks();
	int fps_frames = 0;

	while(running and game.GetRunning())
	{

		//Process event loop
		SDL_Event event;
		while(SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_MOUSEMOTION:
					game.MouseMove(event.motion);
					break;

				case SDL_MOUSEBUTTONDOWN:
					game.MouseDown(event.button);
					break;

				case SDL_MOUSEBUTTONUP:
					game.MouseUp(event.button);
					break;

				case SDL_MOUSEWHEEL:
					game.MouseWheel(event.wheel);
					break;

				case SDL_KEYDOWN:
					if (event.key.keysym.sym == SDLK_ESCAPE) { running = false; }

					game.KeyDown(event.key);
					break;

				case SDL_KEYUP:
					game.KeyUp(event.key);
					break;

				case SDL_QUIT:
					running = false;
					break;


			}
		}


		// Update

		Uint32 this_time = SDL_GetTicks();

		float dt = (this_time - last_time) / 1000.0f;
		last_time = this_time;

		//const float FPS = 30;
		//float dt = 1.0f / FPS;

		fps_frames++;
		if (this_time > fps_timer + 1000)
		{

			std::cout << "FPS: " << fps_frames << std::endl;

			fps_frames = 0;
			fps_timer = this_time;
		}


		game.Update(dt);


		// Render

		game.Render();


		SDL_Delay(1);  //To prevent too high FPS

	}
}


std::string FindDataDirectory()
{
	for(auto path : {"", "../", "../../"} )
	{
		std::string path_dir = std::string(path) + "data/";
		std::string try_path = path_dir + "data_directory.txt";

		std::ifstream in{try_path.c_str()};
		if (in)
		{
			return path_dir;
		}
	}

	throw std::runtime_error("Could not locate data directory");
}

int main()
{
	InitSDL2();

	std::string data_path = FindDataDirectory();

	RunGame(data_path);


	QuitSDL2();
	return 0;
}
