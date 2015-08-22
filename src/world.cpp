//
// Created by Tristan on 22/08/2015.
//

#include "world.h"

// Standard includes
#include <assert.h>


Colour cursor_colour{1.0f, 1.0f, 0.2f, 1.0f};
Colour cursor_fill_colour{0.5f, 0.5f, 0.5f, 0.3f};


World::World(Renderer &renderer, const std::string &data_path)
: renderer(renderer)
, terrain(renderer, data_path+"terrain.xcf")
, tile1(terrain, 32, 0, 0, 1, 1)
, tile2(terrain, 32, 1, 0, 1, 1)
, tile3(terrain, 32, 2, 0, 1, 1)
, tile4(terrain, 32, 3, 0, 1, 1)

, tile_cursor_border(renderer, {0, 0, 32, 32}, cursor_colour, cursor_fill_colour, true)
{
	SetupTileDefs();
}


unsigned World::GetIndex(int x, int y) const
{
	int ret{y * width + x};

	assert(ret >= 0);
	assert(ret < (int)tilemap.size());
	return (unsigned)ret;
}


void World::NewMap(int x, int y, TileDef &block)
{
	assert(x > 0);
	assert(y > 0);

	tilemap.clear();
	tilemap.reserve(unsigned(x * y));
	width = x;
	height = y;

	for (int i=0; i< (x*y); i++)
	{
		tilemap.push_back(&block);
	}

	assert((int)tilemap.size() == width * height);
	assert(width * height == x * y);
}


TileDef &World::GetTile(int x, int y)
{
	unsigned index = GetIndex(x, y);
	TileDef *t = tilemap.at(index);
	assert(t);
	return *t;
}


void World::SetTile(int x, int y, TileDef &new_block)
{
	unsigned index = GetIndex(x, y);
	tilemap.at(index) = &new_block;
}


TileDef &World::GetTileDef(const std::string &name)
{
	return tiledef_map.at(name);
}


void World::RandomMap(int w, int h)
{
	NewMap(w, h, GetTileDef("none"));

	for (int x=0; x<width; x++)
	{
		for(int y=0; y<height; y++)
		{
			if (rand() %2 == 0)
			{
				SetTile(x, y, GetTileDef("wall"));
			}
		}
	}
}


void World::Load(const std::string filename)
{

}

void World::Save(const std::string filename)
{

}


void World::SetupTileDefs()
{

	tiledef_map["wall"] = TileDef{&tile4, true};
	tiledef_map["none"] = TileDef{&tile1, true};



}


void World::Update(float dt)
{

}

void World::Render(Camera &cam)
{
	for (int x = 0; x< width; x++)
	{
		for (int y=0; y < height; y++)
		{
			SDL_Point tile_pos = cam.WorldToScreen(x*32, y*32);

			TileDef & def = GetTile(x, y);
			assert(def.tile);
			def.tile->Render(tile_pos.x, tile_pos.y, cam.zoom);
		}
	}

	tile_cursor_border.Render(cam);
}



void World::HighlightTile(SDL_Point point)
{
	tile_cursor = GetTilePos(point);
	tile_cursor_border.SetPos(tile_cursor.x * 32, tile_cursor.y * 32);

}


SDL_Point World::GetTilePos(SDL_Point point)
{
	point.x /= 32;
	point.y /= 32;

	if (point.x <0) point.x = 0;
	if (point.x >= width) point.x = width -1;

	if (point.y <0) point.y = 0;
	if (point.y >= height) point.y = height -1;

	return point;
}
