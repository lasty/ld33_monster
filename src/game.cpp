//
// Created by Tristan on 22/08/2015.
//

#include "game.h"
#include "colour.h"


#include <vector>


Colour colour_red { "red" };
Colour colour_yellow { "yellow" };
Colour colour_white { "white" };

Colour colour_background { 0.0f, 0.0f, 0.0f, 1.0f };

std::vector<std::string> frame_names { "bat1", "bat2", "bat3", "bat4" };
//std::vector<std::string> frame_names { "snake1", "snake2", "snake3", "snake4", "snake5", "snake6" };
//std::vector<std::string> frame_names { "hero1", "hero2", "hero3", "hero4", "hero5", "hero6", "hero7", "hero8" };

//std::vector<std::string> frame_names { "rock1", "rock2"};
//std::vector<std::string> frame_names { "rock_break1", "rock_break2", "rock_break3", "rock_break4" };

//std::vector<std::string> frame_names { "spikes1", "spikes2", "spikes3", "spikes4", "spikes5", "spikes6", "spikes7" };

//std::vector<std::string> frame_names { "chest"};
//std::vector<std::string> frame_names { "bag"};




Game::Game(std::string data_path, SDL_Window *window)
: data_path(data_path)
, renderer(window)


, title_font(data_path+"fonts/Bangers/Bangers.ttf", 24 * 4)
, sub_title_font(data_path+"fonts/Bitter/Bitter-Regular.ttf", 24)

, title_text(renderer, title_font, "You are the Monster!", colour_red)
, sub_title_text(renderer, sub_title_font, "Ludum Dare 33", colour_yellow)


, sprite_sheet(renderer, data_path)


, particle_system(renderer, data_path)

, world(renderer, data_path)

{

	world.RandomMap(10, 5);


}



void Game::Update(float dt)
{

	sprite_frame -= dt;
	if (sprite_frame < 0.0f)
	{
		sprite_frame = 0.2f;
		frame = (frame + 1) % frame_names.size();
	}

	particle_system.Update(dt);

}



void Game::Render()
{
	renderer.SetDrawColour(colour_background);
	renderer.Clear();

	renderer.SetDrawColour(colour_white);


	world.Render();



	title_text.Render(50, 50);
	sub_title_text.Render(50, 50 + title_text.GetHeight());


	Sprite &s = sprite_sheet.GetSprite(frame_names.at(frame));

	s.Render(200, 200, 4);


	particle_system.Render();


	renderer.Present();
}


void Game::KeyDown(const SDL_KeyboardEvent &event)
{
	if(event.keysym.sym == SDLK_q)  QuitGame();

	if (event.keysym.sym == SDLK_SPACE)
	{
		particle_system.AddParticleEffect("dust", 200, 200);
		particle_system.AddParticleEffect("spark", 400, 200);
		particle_system.AddParticleEffect("blood", 200, 400);
		particle_system.AddParticleEffect("blood_pool", 400, 400);
	}

	if (event.keysym.sym == SDLK_n)
	{
		world.RandomMap(40, 20);
	}

}


void Game::KeyUp(const SDL_KeyboardEvent &event)
{

}

void Game::QuitGame()
{
	game_running = false;
}
