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



const TileDef * BaseAI::PeekMap(int x, int y) const
{
	auto mappos = world->GetTilePos(GetEntity().GetPositionAsPoint());

	mappos.x += x;
	mappos.y += y;

	if (not GetWorld().PositionValid(mappos.x, mappos.y))
	{
		return nullptr;
	}

	return &GetWorld().GetTile(mappos.x, mappos.y);

}

Entity * BaseAI::PeekEntity(int x, int y) const
{
	return nullptr;
}


SDL_Rect BaseAI::GetBoundingBox() const
{
	assert(GetEntity().GetCollision());

	return GetEntity().GetCollision()->GetBoundingBox();
}

SDL_Rect BaseAI::GetSensorLeft() const
{
	SDL_Rect bb = GetBoundingBox();

	//2 pixels to the left?
	bb.x -= 2;
	bb.w = 2;
	return bb;
}


SDL_Rect BaseAI::GetSensorRight() const
{
	SDL_Rect bb = GetBoundingBox();

	bb.x += bb.w;
	bb.w = 2;
	return bb;
}


bool BaseAI::CollidesWorld(const SDL_Rect &rect) const
{
	return GetWorld().HasCollisionWorld(rect);
}


bool BaseAI::CollidesEntities(const SDL_Rect &rect) const
{
	return GetWorld().HasCollisionEntity(rect, &GetEntity());
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
		SetPause(0.5f);
		//SetRandomState({"move_right"});
	}

	else if(state == "move_right")
	{
		SetPause(0.5f);
		//SetRandomState({"move_left"});
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

		//const TileDef * peek = PeekMap(-1, 0);
		//if (peek and peek->solid)
		if(CollidesWorld(GetSensorLeft()))
		{
			SetState("move_right");
		}

	}
	else if (GetState() == "move_right")
	{
		pos.x += speed * dt;

		//const TileDef * peek = PeekMap(1, 0);
		//if (peek and peek->solid)
		if(CollidesWorld(GetSensorRight()))
		{
			SetState("move_left");
		}

	}

	GetEntity().GetPosition()->SetPosition(pos.x, pos.y);

}
