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
#include "particlesystem.h"
#include "world.h"
#include "gui.h"

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
	SDL_Rect rect;

	bool game_running = true;

	bool pan_camera = false;
	bool pan_left = false;
	bool pan_right = false;
	bool pan_up = false;
	bool pan_down = false;

public:

	void Update(float dt);

	void Render();

	void KeyDown(const SDL_KeyboardEvent &event);
	void KeyUp(const SDL_KeyboardEvent &event);

	void MouseMove(const SDL_MouseMotionEvent &event);
	void MouseDown(const SDL_MouseButtonEvent &event);
	void MouseUp(const SDL_MouseButtonEvent &event);

	void QuitGame();


	void SetupGUI();
	void AlignGUI();


	Font title_font;
	Font sub_title_font;
	Font small_font;

	GUI gui;

	Label title_text;
	Label sub_title_text;
	Border title_border;
	Button test_button;

	SpriteSheet sprite_sheet;

	//AnimatedSprite bat;
	//AnimatedSprite rock;
	//AnimatedSprite rock_break;
	//
	//AnimatedSprite spikes;
	//AnimatedSprite snake;
	//AnimatedSprite bag;
	//
	//AnimatedSprite hero;


	ParticleSystem particle_system;


	Camera screen_camera;
	Camera world_camera;

	World world;


public:

	SDL_Point ScreenToWorld(int x, int y) { return world_camera.ScreenToWorld(x, y); }
	SDL_Point WorldToScreen(int x, int y) { return world_camera.WorldToScreen(x, y); }



	//Level editor
	void SetSelectedTile(const std::string &string);
	std::string selected_tile = "none";
	bool painting = false;


	//Entity editor
	void SetSelectedEntity(const std::string &string);
	std::string selected_entity = "hero";


	// Getters
	bool GetRunning() const { return game_running; }
	const SDL_Rect& GetRect() const { return rect; }


	void PasteSelectedTile();

	void LoadLevel(int i);

	void MouseWheel(const SDL_MouseWheelEvent &event);
};


