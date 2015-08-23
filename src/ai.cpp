//
// Created by Tristan on 23/08/2015.
//

#include "ai.h"


#include "entity.h"

////////////////////////////////////////////////////////////////////////////////


BaseAI::BaseAI(Entity *entity, World *world)
:entity(entity)
, world(world)
{

}

World &BaseAI::GetWorld()
{
	assert(world);
	return *world;
}

const World &BaseAI::GetWorld() const
{
	assert(world);
	return *world;
}

Entity &BaseAI::GetEntity()
{
	assert(entity);
	return *entity;
}

const Entity &BaseAI::GetEntity() const
{
	assert(entity);
	return *entity;
}


void BaseAI::SetRandomState(std::vector<std::string> list)
{
	int r = rand() % (int)list.size();
	assert(r >=0 and r < (int) list.size());

	SetState(list.at(r));

}

void BaseAI::SetPause(float newpause)
{
	pause_timer = newpause;
}

void BaseAI::Update(float dt)
{
	if (pause_timer > 0)
	{
		pause_timer -= dt;
		return;
	}

	pause_timer = 0.5f;

	AITick();

}

////////////////////////////////////////////////////////////////////////////////


SimpleMoverAI::SimpleMoverAI(Entity *entity, World *world)
: BaseAI(entity, world)
{

}


void SimpleMoverAI::AITick()
{
	const auto & state = GetState();

	if(state == "idle")
	{
		SetRandomState({"move_left", "move_right"});
	}

	else if(state == "move_left")
	{
		SetPause(2.0f);
		SetRandomState({"move_right"});
	}

	else if(state == "move_right")
	{
		SetPause(2.0f);
		SetRandomState({"move_left"});
	}

}


void SimpleMoverAI::Update(float dt)
{
	BaseAI::Update(dt);

	glm::vec2 pos = GetEntity().GetPosition()->GetPosition();
	float speed = 32.0f;

	if (GetState() == "move_left")
	{
		pos.x -= speed * dt;
	}
	else if (GetState() == "move_right")
	{
		pos.x += speed * dt;
	}

	GetEntity().GetPosition()->SetPosition(pos.x, pos.y);

}
