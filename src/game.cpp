//
// Created by Tristan on 22/08/2015.
//

#include "game.h"


Game::Game(SDL_Window *window)
: renderer(window)
{

}


void Game::Update(float dt)
{

}


void Game::Render()
{
	renderer.Clear();


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
