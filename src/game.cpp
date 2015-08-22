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
