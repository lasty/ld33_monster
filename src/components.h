//
// Created by Tristan on 23/08/2015.
//


#pragma once


#include "animatedsprite.h"
#include "camera.h"
#include "colour.h"
#include "font.h"
#include "text.h"


class Entity;
class World;


class Component
{
public:
	Component();

	virtual ~Component();

	virtual void Render(int x, int y, Camera &cam);

	virtual void Update(float dt);
};


////////////////////////////////////////////////////////////////////////////////


class SpriteComponent : public Component
{
public:
	SpriteComponent(AnimatedSprite s);

private:
	AnimatedSprite animated_sprite;
	int zoom = 1;

public:
	void Update(float dt) override;

	void Render(int x, int y, Camera &cam) override;
};


////////////////////////////////////////////////////////////////////////////////


class CollisionComponent : public Component
{
public:
	CollisionComponent(Entity *entity, World *world, int w, int h);

private:
	Entity *entity = nullptr;
	World *world = nullptr;
	SDL_Rect boundingbox;

public:
	void SetPosition(int x, int y);
	const SDL_Rect & GetBoundingBox() const { return boundingbox; }

	bool HasCollision() const;
};


////////////////////////////////////////////////////////////////////////////////


class MovableComponent : public Component
{
public:
	MovableComponent(Entity *entity, int x, int y);

private:
	Entity *entity = nullptr;
	SDL_Point position;

public:
	void SetPosition(int x, int y);
	const SDL_Point & GetPosition() const { return position; }
};


////////////////////////////////////////////////////////////////////////////////


class DebugComponent : public Component
{
public:
	DebugComponent(Entity *entity,Renderer &renderer, Font &font, std::string debug_text, Colour colour);

private:
	Entity *entity = nullptr;
	Renderer &renderer;
	Text text;
	std::string debug_text;

public:
	void SetText(const std::string new_text);

	void Render(int x, int y, Camera &cam) override;

};


////////////////////////////////////////////////////////////////////////////////

