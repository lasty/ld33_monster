//
// Created by Tristan on 22/08/2015.
//


#pragma once

// Local Includes
#include "renderer.h"
#include "font.h"
#include "text.h"
#include "tile.h"
#include "spritesheet.h"

// SDL includes
#include <SDL_events.h>

// Standard includes



class Game
{
public:
	Game(std::string data_path, SDL_Window *window);

private:
	std::string data_path;
	Renderer renderer;

	bool game_running = true;

public:

	void Update(float dt);

	void Render();

	void KeyDown(const SDL_KeyboardEvent &event);
	void KeyUp(const SDL_KeyboardEvent &event);
	void QuitGame();



	Font title_font;
	Font sub_title_font;

	Text title_text;
	Text sub_title_text;


	Surface terrain;

	Tile tile1;
	Tile tile2;
	Tile tile3;
	Tile tile4;


	SpriteSheet sprite_sheet;
	int frame = 0;
	float sprite_frame = 0.2f;

public:
	bool GetRunning() const { return game_running; }

};


