//
// Created by Tristan on 24/08/2015.
//

#include "input.h"

#include "entity.h"
#include "world.h"


void Input::Clear()
{
	move_left = move_right = jump = false;
}

glm::vec2 Input::GetVector() const
{
	glm::vec2 v;
	if (move_left) v.x -= 1.0f;
	if (move_right) v.x += 1.0f;

	if(jump) v.y -= 1.0f;
	return v;
}


////////////////////////////////////////////////////////////////////////////////


InputControllerComponent::InputControllerComponent(Entity *entity, World *world, Input *input)
: entity(entity)
, world(world)
, input(input)
{

}



void InputControllerComponent::Update(float dt)
{
	assert(entity);
	glm::vec2 pos = entity->GetPosition()->GetPosition();
	glm::vec2 dir;

	float walk_speed = 128.0f;
	float jump_speed = 320.0f;

	if (input->move_left)
	{
		dir.x -= walk_speed;
		//dir.y -= 1.0f;
	}

	if (input->move_right)
	{
		dir.x += walk_speed;
		//dir.y -= 1.0f;

	}

	if (input->jump)
	{
		dir.y -= jump_speed;
	}

	if (entity->GetPhysics())
	{
		dir *= dt * 16.0f;
		entity->GetPhysics()->Impulse(dir);
	}
	else
	{
		pos += dir * dt;
		entity->GetPosition()->SetPosition(pos.x, pos.y);
	}

}


