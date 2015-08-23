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
	EntityFactory(SpriteSheet &sprite_sheet);

private:
	SpriteSheet &sprite_sheet;

	void SetupEntityList();

public:

	std::unique_ptr<Entity> Create(const std::string &entitydefname, int x, int y);

};


