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

Colour button_border { 0.4f, 0.5f, 0.6f, 1.0f };
Colour button_background { 0.1f, 0.2f, 0.3f, 0.5f };
Colour button_text { 0.9f, 0.8f, 0.7f, 1.0f };

Colour colour_background { 0.1f, 0.2f, 0.3f, 1.0f };


Game::Game(std::string data_path, SDL_Window *window)
: data_path(data_path)
, renderer(window)
, rect{0, 0, 0, 0}

, title_font(data_path+"fonts/Bangers/Bangers.ttf", 24 * 4)
, sub_title_font(data_path+"fonts/Bitter/Bitter-Regular.ttf", 24)
, small_font(data_path+"fonts/SourceSansPro/SourceSansPro-Regular.ttf", 14)

, title_text(renderer, title_font, "You are the Monster!", colour_red, 50, 50)
, sub_title_text(renderer, sub_title_font, "Ludum Dare 33", colour_yellow, 50, 250)
, title_border(renderer, {}, colour_white, border_background, true)
, test_button(renderer, {}, small_font, "Test Button", button_border, button_background, button_text)

, sprite_sheet(renderer, data_path)

, particle_system(renderer, data_path)

, world(renderer, particle_system, data_path, sprite_sheet)

{
	SDL_GetWindowSize(window, &rect.w, &rect.h);

	world.RandomMap(10, 5);

	//bat = sprite_sheet.GetSprite("bat");
	//
	//rock = sprite_sheet.GetSprite("rock");
	//rock_break = sprite_sheet.GetSprite("rock_break");
	//
	//spikes = sprite_sheet.GetSprite("spikes");
	//snake = sprite_sheet.GetSprite("snake");
	//
	//bag = sprite_sheet.GetSprite("bag");
	//
	//hero = sprite_sheet.GetSprite("hero");

	SetupGUI();

	LoadLevel(1);


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
	if (pan_left) world_camera.PanCamera(-1, 0);
	if (pan_right) world_camera.PanCamera(1, 0);
	if (pan_up) world_camera.PanCamera(0, -1);
	if (pan_down) world_camera.PanCamera(0, 1);


	//bat.Update(dt);
	//rock.Update(dt);
	//rock_break.Update(dt);
	//
	//spikes.Update(dt);
	//snake.Update(dt);
	//bag.Update(dt);
	//
	//hero.Update(dt);

	world_camera.Update(dt);

	world.Update(dt);

	if (painting) { PasteSelectedTile(); }

	particle_system.Update(dt);

}



void Game::Render()
{
	renderer.SetDrawColour(colour_background);
	renderer.Clear();
	renderer.SetDrawColour(colour_white);

	if (state == GameState::maingame)
	{
		world.Render(world_camera);

		particle_system.Render(world_camera);
	}


	if (state == GameState::menu)
	{
		gui.Render();
	}

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

	if (event.keysym.sym == SDLK_F9)
	{
		world.Load(data_path+"tilemap.txt");
	}

	if (event.keysym.sym == SDLK_F5)
	{
		world.Save(data_path+"tilemap.txt");
	}



	if (event.keysym.sym == SDLK_w) pan_up = true;
	if (event.keysym.sym == SDLK_a) pan_left = true;
	if (event.keysym.sym == SDLK_s) pan_down = true;
	if (event.keysym.sym == SDLK_d) pan_right = true;

	if (event.keysym.sym == SDLK_1)  { SetSelectedTile("none");  SetSelectedEntity("spikes"); }
	if (event.keysym.sym == SDLK_2)  { SetSelectedTile("wall");  SetSelectedEntity("bat"); }


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
		world_camera.PanCamera(-event.xrel, -event.yrel);
	}

	SDL_Point worldpos = world_camera.ScreenToWorld(event.x, event.y);
	world.SetTileCursor(worldpos);
	world.SetEntityCursor(worldpos);

}

void Game::MouseDown(const SDL_MouseButtonEvent &event)
{
	if (event.button == 3) painting = true;

	if (event.button == 1) world.PasteEntity(selected_entity);

	if (event.button == 2) pan_camera = true;
}

void Game::MouseUp(const SDL_MouseButtonEvent &event)
{
	if (event.button == 3) painting = false;

	if (event.button == 2) pan_camera = false;
}

void Game::SetSelectedTile(const std::string &string)
{
	selected_tile = string;
}

void Game::SetSelectedEntity(const std::string &string)
{
	selected_entity = string;
}


void Game::PasteSelectedTile()
{
	world.PasteTile(selected_tile);
}

void Game::LoadLevel(int i)
{
	world.Load(data_path+"tilemap.txt");

	world_camera.offset_x = -32;
	world_camera.offset_y = -32;
	world_camera.SetZoom(4);
}

void Game::MouseWheel(const SDL_MouseWheelEvent &event)
{
	world_camera.ZoomCamera(event.y / 4.0f);
}
