//
// Created by Tristan on 23/08/2015.
//


#pragma once


#include "entity.h"
#include "spritesheet.h"

#include <memory>


class EntityFactory
{
public:
	EntityFactory(Renderer &renderer, Font &debug_font, SpriteSheet &sprite_sheet);

private:
	Renderer &renderer;
	Font &debug_font;
	SpriteSheet &sprite_sheet;

	void SetupEntityList();

public:

	std::unique_ptr<Entity> Create(const std::string &entitydefname, World *world, int x, int y);

};


