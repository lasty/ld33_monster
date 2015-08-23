//
// Created by Tristan on 22/08/2015.
//

#pragma once

// Local includes
#include "sprite.h"
#include "tile.h"
#include "renderer.h"
#include "camera.h"
#include "gui.h"
#include "entityfactory.h"

// Standard includes
#include <vector>
#include <string>
#include <map>


struct TileDef
{
	Tile *tile;
	bool solid;

	std::string def_name;
};



class World
{
public:
	World(Renderer &renderer, const std::string &data_path, SpriteSheet &sprite_sheet);

private:
	Renderer &renderer;

	//tilemap stuff

	Surface terrain;

	int width = 0;
	int height = 0;

	std::vector<TileDef*> tilemap;

	std::map<std::string, TileDef> tiledef_map;

	unsigned GetIndex(int x, int y) const;

	void NewMap(int x, int y, TileDef &block);
	TileDef & GetTile(int x, int y);
	void SetTile(int x, int y, TileDef &new_block);
	TileDef & GetTileDef(const std::string &name);

	void SetupTileDefs();

	Tile tile1;
	Tile tile2;
	Tile tile3;
	Tile tile4;


	//tile cursor stuff
	Border tile_cursor_border;
	SDL_Point tile_cursor{0, 0};


	//entity stuff

	EntityFactory entity_factory;
	std::vector<Entity> entity_list;

	//entity cursor stuff
	SDL_Point entity_cursor{0, 0};


public:

	void RandomMap(int w, int h);

	void Load(const std::string filename);
	void Save(const std::string filename);


	void Update(float dt);
	void Render(Camera &cam);

	void SetTileCursor(SDL_Point point);
	void SetEntityCursor(SDL_Point point);

	SDL_Point GetTilePos(SDL_Point point);

	void PasteTile(const std::string &def_name);
	void PasteEntity(const std::string &def_name);


	void SpawnEntity(const std::string &name, int x, int y);

	void RemoveDeadEntities();
};


