//
// Created by Tristan on 22/08/2015.
//

#include "game.h"
#include "colour.h"


#include <vector>


Colour colour_red { "red" };
Colour colour_yellow { "yellow" };
Colour colour_white { "white" };

Colour border_background { 1.0f, 1.0f, 1.0f, 0.1f };

Colour colour_background { 0.1f, 0.2f, 0.3f, 1.0f };


Game::Game(std::string data_path, SDL_Window *window)
: data_path(data_path)
, renderer(window)
, rect{0, 0, 0, 0}

, title_font(data_path+"fonts/Bangers/Bangers.ttf", 24 * 4)
, sub_title_font(data_path+"fonts/Bitter/Bitter-Regular.ttf", 24)

, title_text(renderer, title_font, "You are the Monster!", colour_red, 50, 50)
, sub_title_text(renderer, sub_title_font, "Ludum Dare 33", colour_yellow, 50, 250)
, title_border(renderer, {}, colour_white, border_background, true)
, test_button(renderer, {}, sub_title_font, "Test Button", colour_white, border_background, colour_yellow)

, sprite_sheet(renderer, data_path)

, particle_system(renderer, data_path)

, world(renderer, data_path)

{
	SDL_GetWindowSize(window, &rect.w, &rect.h);

	world.RandomMap(10, 5);

	bat = sprite_sheet.GetSprite("bat");

	rock = sprite_sheet.GetSprite("rock");
	rock_break = sprite_sheet.GetSprite("rock_break");

	spikes = sprite_sheet.GetSprite("spikes");
	snake = sprite_sheet.GetSprite("snake");

	bag = sprite_sheet.GetSprite("bag");

	hero = sprite_sheet.GetSprite("hero");

	SetupGUI();

}


void Game::SetupGUI()
{
	gui.AddWidget(title_border);
	gui.AddWidget(title_text);
	gui.AddWidget(sub_title_text);

	gui.AddWidget(test_button);

	AlignGUI();
}


void Game::AlignGUI()
{
	title_text.AlignInside(GetRect(), 0, 50);
	title_border.AlignOutside(title_text, 10);

	sub_title_text.AlignWith(title_border, 0, 1);

	test_button.AlignWith(sub_title_text, 0, 10);

}


void Game::Update(float dt)
{
	//int pan_speed = 1;
	if (pan_left) camera.PanCamera(-1, 0);
	if (pan_right) camera.PanCamera(1, 0);
	if (pan_up) camera.PanCamera(0, -1);
	if (pan_down) camera.PanCamera(0, 1);


	bat.Update(dt);
	rock.Update(dt);
	rock_break.Update(dt);

	spikes.Update(dt);
	snake.Update(dt);
	bag.Update(dt);

	hero.Update(dt);


	particle_system.Update(dt);

}



void Game::Render()
{
	renderer.SetDrawColour(colour_background);
	renderer.Clear();

	renderer.SetDrawColour(colour_white);


	world.Render(camera);


	bat.Render(200, 200, 4);
	rock.Render(300, 200, 4);
	rock_break.Render(400, 200, 4);

	snake.Render(500, 200, 4);
	bag.Render(600, 200, 4);

	hero.Render(200, 400, 4);
	spikes.Render(400, 400, 4);

	particle_system.Render();


	gui.Render();



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


	if (event.keysym.sym == SDLK_w) pan_up = true;
	if (event.keysym.sym == SDLK_a) pan_left = true;
	if (event.keysym.sym == SDLK_s) pan_down = true;
	if (event.keysym.sym == SDLK_d) pan_right = true;
}


void Game::KeyUp(const SDL_KeyboardEvent &event)
{
	if (event.keysym.sym == SDLK_w) pan_up = false;
	if (event.keysym.sym == SDLK_a) pan_left = false;
	if (event.keysym.sym == SDLK_s) pan_down = false;
	if (event.keysym.sym == SDLK_d) pan_right = false;


}

void Game::QuitGame()
{
	game_running = false;
}


void Game::MouseMove(const SDL_MouseMotionEvent &event)
{
	if (pan_camera)
	{
		camera.PanCamera(-event.xrel, -event.yrel);
	}

	SDL_Point worldpos = camera.ScreenToWorld(event.x, event.y);
	world.HighlightTile(worldpos);

}

void Game::MouseDown(const SDL_MouseButtonEvent &event)
{
	if (event.button == 2 or event.button == 3) pan_camera = true;
}

void Game::MouseUp(const SDL_MouseButtonEvent &event)
{
	if (event.button == 2 or event.button == 3) pan_camera = false;
}
