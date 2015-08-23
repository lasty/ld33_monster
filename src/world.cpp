//
// Created by Tristan on 22/08/2015.
//

#include "world.h"

// Standard includes
#include <fstream>
#include <iostream>
#include <assert.h>
#include <algorithm>


Colour cursor_colour{1.0f, 1.0f, 0.2f, 1.0f};
Colour cursor_fill_colour{0.5f, 0.5f, 0.5f, 0.3f};


World::World(Renderer &renderer, ParticleSystem &particle_system, const std::string &data_path, SpriteSheet &sprite_sheet)
: renderer(renderer)
, particle_system(particle_system)
, terrain(renderer, data_path+"terrain.xcf")
, tile1(terrain, 32, 0, 0, 1, 1)
, tile2(terrain, 32, 1, 0, 1, 1)
, tile3(terrain, 32, 2, 0, 1, 1)
, tile4(terrain, 32, 3, 0, 1, 1)

, tile_cursor_border(renderer, {0, 0, 32, 32}, cursor_colour, cursor_fill_colour, true)

, debug_font(data_path+"fonts/SourceSansPro/SourceSansPro-Regular.ttf", 14)

, entity_factory(renderer, debug_font, sprite_sheet)
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


bool World::PositionValid(int x, int y) const
{
	return (x >= 0 and x < width and y >= 0 and y < width);
}


void World::NewMap(int x, int y, TileDef &block)
{
	assert(x > 0);
	assert(y > 0);

	entity_list.clear();

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

const TileDef &World::GetTile(int x, int y) const
{
	unsigned index = GetIndex(x, y);
	TileDef *t = tilemap.at(index);
	assert(t);
	return *t;
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
	std::cout << "Attempting to load map ..." << std::endl;

	std::ifstream in(filename);

	int w = 0;
	int h = 0;
	in >> w >> h;

	std::cout << "got width: " << w << "  and height: " << h << "..." << std::endl;

	assert(w);
	assert(h);
	assert(in);

	NewMap(w, h, GetTileDef("none"));

	for(int y=0; y<height; y++)
	{
		for(int x=0; x<width; x++)
		{
			std::string def_name;
			in >> def_name;

			SetTile(x, y, GetTileDef(def_name));
		}
	}

	//Entities

	entity_list.clear();

	int num_ents = 0;
	in >> num_ents;

	std::cout << "parsing  " << num_ents <<  " entities..." << std::endl;

	for (int i = 0; i<num_ents; i++)
	{
		int entx = 0;
		int enty = 0;
		std::string entname;

		in >> entx >> enty >> entname;
		SpawnEntity(entname, entx, enty);
	}

	std::cout << "Done!" << std::endl;

}


void World::Save(const std::string filename)
{
	std::cout << "Saving map..." << std::endl;

	std::ofstream out(filename, std::ios::trunc);

	//Tile Map

	out << width << " " << height << std::endl;

	for(int y=0; y<height; y++)
	{
		for(int x=0; x<width; x++)
		{
			TileDef def = GetTile(x, y);
			out << def.def_name << " ";
		}
		out << std::endl;
	}
	out << std::endl;


	//Entities
	out << entity_list.size() << std::endl;

	for(auto &ent : entity_list)
	{
		SDL_Point pos = ent->GetPositionAsPoint();
		out << pos.x << " " << pos.y << " " << ent->name << std::endl;
	}


	std::cout << "Saved!" << std::endl;

}


void World::SetupTileDefs()
{
	tiledef_map["wall"] = TileDef{&tile4, true, "wall"};
	tiledef_map["none"] = TileDef{&tile1, false, "none"};
}


void World::Update(float dt)
{
	for(auto & entity : entity_list)
	{
		entity->Update(dt);
	}

	RemoveDeadEntities();
}


void World::Render(Camera &cam)
{
	for (int x = 0; x< width; x++)
	{
		for (int y=0; y < height; y++)
		{
			SDL_Point tile_pos{x*32, y*32};

			TileDef & def = GetTile(x, y);
			assert(def.tile);
			def.tile->Render(tile_pos.x, tile_pos.y, cam);
		}
	}


	for(auto & entity : entity_list)
	{
		entity->Render(cam);
	}


	tile_cursor_border.Render(cam);
}



void World::SetTileCursor(SDL_Point point)
{
	tile_cursor = GetTilePos(point);
	tile_cursor_border.SetPos(tile_cursor.x * 32, tile_cursor.y * 32);
}


void World::SetEntityCursor(SDL_Point point)
{
	entity_cursor = point;
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


void World::PasteTile(const std::string &def_name)
{
	SetTile(tile_cursor.x, tile_cursor.y, GetTileDef(def_name));
}


void World::PasteEntity(const std::string &def_name)
{
	SpawnEntity(def_name, entity_cursor.x, entity_cursor.y);
}


void World::SpawnEntity(const std::string &name, int x, int y)
{
	std::unique_ptr<Entity> e = entity_factory.Create(name, this, x, y);
	entity_list.push_back(std::move(e));
}


void World::RemoveDeadEntities()
{
	auto partition = std::remove_if(entity_list.begin(), entity_list.end(), [](auto &e){ return e->ShouldRemove(); });

	entity_list.erase(partition, entity_list.end());
}


bool World::HasCollisionWorld(const SDL_Rect &boundingbox) const
{
	//Check to see if outside world boundaries

	SDL_Rect world_rect{0, 0, 32*width, 32*height};
	if (not SDL_HasIntersection(&boundingbox, &world_rect)) { return true; }

	//Edge cases ugh There's probably a much better way to do this...
	SDL_Rect world_rect_top{0, -32, 32 * (width), 32};
	if (SDL_HasIntersection(&boundingbox, &world_rect_top)) { return true; }

	SDL_Rect world_rect_bot{0, 32 * (height), 32 * (width), 32};
	if (SDL_HasIntersection(&boundingbox, &world_rect_bot)) { return true; }

	SDL_Rect world_rect_left{-32, 0, 32, 32 * (height)};
	if (SDL_HasIntersection(&boundingbox, &world_rect_left)) { return true; }

	SDL_Rect world_rect_right{32 * width, 0, 32, 32 * height};
	if (SDL_HasIntersection(&boundingbox, &world_rect_right)) { return true; }


	//Check all the tiles
	SDL_Rect tile_rect{0,0, 32, 32};

	//TODO Could be optimized to only take a few tiles into account
	for(int x=0; x<width; x++)
	{
		for (int y=0; y<height; y++)
		{
			if (GetTile(x,y).solid)
			{
				tile_rect.x = 32 * x;
				tile_rect.y = 32 * y;

				if (SDL_HasIntersection(&boundingbox, &tile_rect))
				{
					return true;
				}

			}
		}
	}
	return false;
}


bool World::HasCollisionEntity(const SDL_Rect &boundingbox, Entity *ignore_entity) const
{
	for(auto & entity : entity_list)
	{
		if (entity.get() == ignore_entity) continue;
		if (not entity->GetCollision()) continue;

		const SDL_Rect & bb2 = entity->GetCollision()->GetBoundingBox();
		if (SDL_HasIntersection(&boundingbox, &bb2))
		{
			return true;
		}
	}

	return false;
}


bool World::HasCollisionAny(const SDL_Rect &boundingbox, Entity *ignore_entity) const
{
	return HasCollisionWorld(boundingbox) or HasCollisionEntity(boundingbox, ignore_entity);
}


void World::AddParticleEffect(SDL_Point point, const std::string &string)
{
	particle_system.AddParticleEffect(string, point.x, point.y);
}
