//
// Created by Tristan on 22/08/2015.
//

#include "game.h"
#include "colour.h"

Colour colour_red { "red" };
Colour colour_yellow { "yellow" };
Colour colour_white { "white" };

Colour colour_background { 0.1f, 0.2f, 0.3f, 1.0f };

Game::Game(std::string data_path, SDL_Window *window)
: data_path(data_path)
, renderer(window)


, title_font(data_path+"fonts/Bangers/Bangers.ttf", 24 * 4)
, sub_title_font(data_path+"fonts/Bitter/Bitter-Regular.ttf", 24)

, title_text(renderer, title_font, "You are the Monster!", colour_red)
, sub_title_text(renderer, sub_title_font, "Ludum Dare 33", colour_yellow)


, terrain(renderer, data_path+"terrain.xcf")

, tile1(terrain, 32, 0, 0, 1, 1)
, tile2(terrain, 32, 1, 0, 1, 1)
, tile3(terrain, 32, 2, 0, 1, 1)
, tile4(terrain, 32, 3, 0, 1, 1)

{

}


void Game::Update(float dt)
{

}



void Game::Render()
{
	renderer.SetDrawColour(colour_background);
	renderer.Clear();

	renderer.SetDrawColour(colour_white);

	for (int x = 0; x< 20; x++)
	{
		for (int y=0; y < 10; y++)
		{
			tile1.Render(x * 32* 2, y * 32 * 2, 2);
		}
	}


	title_text.Render(50, 50);
	sub_title_text.Render(50, 50 + title_text.GetHeight());




	renderer.Present();
}


void Game::KeyDown(const SDL_KeyboardEvent &event)
{
	if(event.keysym.sym == SDLK_q)  QuitGame();

}


void Game::KeyUp(const SDL_KeyboardEvent &event)
{

}

void Game::QuitGame()
{
	game_running = false;
}
