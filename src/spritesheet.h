//
// Created by Tristan on 22/08/2015.
//


#pragma once


#include "surface.h"
#include "sprite.h"
#include "renderer.h"

#include <map>


class SpriteSheet
{
public:
	SpriteSheet(Renderer &renderer, const std::string &data_path);

private:

	Renderer &renderer;
	Surface sprites1;

	std::map<std::string, Sprite> spritelist;

	void SetupSprites();

public:

	Sprite & GetSprite(const std::string name);


};


