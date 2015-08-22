//
// Created by Tristan on 22/08/2015.
//

#pragma once

// Local includes
#include "sprite.h"
#include "tile.h"
#include "renderer.h"


// Standard includes
#include <vector>
#include <string>
#include <map>


struct TileDef
{
	Tile *tile;
	bool solid;
};


class EntityDef
{

};


class Entity
{

};


class World
{
public:
	World(Renderer &renderer, const std::string &data_path);

private:
	Renderer &renderer;
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


public:

	void RandomMap(int w, int h);

	void Load(const std::string filename);
	void Save(const std::string filename);


	void Update(float dt);
	void Render();

};


