//
// Created by Tristan on 22/08/2015.
//


#pragma once

// Local Includes
#include "renderer.h"

// SDL includes
#include <SDL_events.h>

// Standard includes



class Game
{
public:
	Game(SDL_Window *window);

private:
	Renderer renderer;

	bool game_running = true;

public:

	void Update(float dt);

	void Render();

	void KeyDown(const SDL_KeyboardEvent &event);
	void KeyUp(const SDL_KeyboardEvent &event);
	void QuitGame();


public:
	bool GetRunning() const { return game_running; }

};


