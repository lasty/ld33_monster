//
// Created by Tristan on 23/08/2015.
//


#pragma once


#include "animatedsprite.h"
#include "camera.h"
#include "colour.h"
#include "font.h"
#include "text.h"


#include <glm/vec2.hpp>


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
	float zoom = 1.0f;

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
	float GetRadius() const;

	bool HasEntityCollisionAt(int x, int y) const;
	bool HasWorldCollisionAt(int x, int y) const;
	bool HasCollisionAt(int x, int y) const;

	bool HasCollision() const;
};


////////////////////////////////////////////////////////////////////////////////


class MovableComponent : public Component
{
public:
	MovableComponent(Entity *entity, int x, int y);

private:
	Entity *entity = nullptr;
	glm::vec2 position;

public:
	void SetPosition(float x, float y);
	const glm::vec2 & GetPosition() const { return position; }

};


////////////////////////////////////////////////////////////////////////////////


class PhysicsComponent : public Component
{
public:
	PhysicsComponent(Entity *entity, World *world, bool gravity);

private:
	Entity *entity = nullptr;
	World *world = nullptr;
	bool gravity = true;


	glm::vec2 velocity;

public:
	void Update(float dt) override;

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

