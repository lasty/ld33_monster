//
// Created by Tristan on 22/08/2015.
//

#include "game.h"

SDL_Color colour_red { 255, 0, 0, 255 };

Game::Game(std::string data_path, SDL_Window *window)
: data_path(data_path)
, renderer(window)


, title_font(data_path+"fonts/Bangers/Bangers.ttf", 24)
, title_text(renderer, title_font, "You are the Monster", colour_red)
{

}


void Game::Update(float dt)
{

}


void Game::Render()
{
	renderer.Clear();

	renderer.Blit(title_text, nullptr, nullptr);

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
