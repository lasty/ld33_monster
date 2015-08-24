//
// Created by Tristan on 24/08/2015.
//


#pragma once


#include "components.h"

class Entity;
class World;

#include <glm/vec2.hpp>


////////////////////////////////////////////////////////////////////////////////


class Input
{
public:
	Input() = default;

	bool move_left = false;
	bool move_right = false;
	bool jump = false;

	void Clear();

	glm::vec2 GetVector() const;

};



class InputControllerComponent : public Component
{
public:
	InputControllerComponent(Entity *entity, World *world, Input *input);

private:
	Entity *entity = nullptr;
	World *world = nullptr;
	Input *input = nullptr;

public:
	virtual void Update(float dt) override;
};
