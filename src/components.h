//
// Created by Tristan on 23/08/2015.
//


#pragma once


#include "animatedsprite.h"
#include "camera.h"



class Component
{
public:
	Component() {}
	virtual ~Component() {}

	virtual void Render(int x, int y, Camera &cam) { }
	virtual void Update(float dt) { }
};


class SpriteComponent : public Component
{
public:
	SpriteComponent(AnimatedSprite s)
	: animated_sprite(s)
	{ }

private:
	AnimatedSprite animated_sprite;
	int zoom = 1;

	void Update(float dt) override
	{
		animated_sprite.Update(dt);
	}

	void Render(int x, int y, Camera &cam) override
	{
		animated_sprite.Render(x, y, zoom, cam);
	}


};

