//
// Created by Tristan on 23/08/2015.
//


#pragma once

#include "camera.h"
#include "components.h"


#include <string>
#include <vector>
#include <memory>


class BaseAI;


class Entity
{
public:
	Entity(std::string name);

	Entity(Entity &&move_construct) = default;
	Entity & operator=(Entity &&move_assign) = default;

	std::string name;

private:
	//int x = 0;
	//int y = 0;

	bool alive = true;

	//Common component references
	MovableComponent * movable = nullptr;
	CollisionComponent * collision = nullptr;

	BaseAI * base_ai = nullptr;

private:
	std::vector<std::unique_ptr<Component>> components;

public:
	void AddComponent(Component * take_ownership);


	SDL_Point GetPositionAsPoint() const;
	MovableComponent * GetPosition() const { return movable; }
	CollisionComponent * GetCollision() const { return collision; }
	const std::string * GetAIStateName() const;

	void Update(float dt);

	void Render(Camera &cam);

	bool ShouldRemove() const { return not alive; }
};


