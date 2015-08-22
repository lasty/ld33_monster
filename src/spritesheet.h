//
// Created by Tristan on 22/08/2015.
//


#pragma once


#include "surface.h"
#include "sprite.h"
#include "renderer.h"
#include "animatedsprite.h"

#include <map>
#include <vector>


class SpriteSheet
{
public:
	SpriteSheet(Renderer &renderer, const std::string &data_path);

private:

	Renderer &renderer;
	Surface sprites1;

	std::map<std::string, Animation> spritelist;

	void SetupSprites();

public:

	Animation & GetAnimation(const std::string &name);
	AnimatedSprite GetSprite(const std::string &name);


};


