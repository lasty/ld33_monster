//
// Created by Tristan on 23/08/2015.
//

#include "entity.h"


#include "components.h"
#include "ai.h"


Entity::Entity(std::string name)
:name(name)
{

}

void Entity::AddComponent(Component *take_ownership)
{
	components.emplace_back(take_ownership);


	//Setup quick access for a couple of frequently accessed components
	//Limit to one per entity

	CollisionComponent *coll = dynamic_cast<CollisionComponent*>(take_ownership);
	if (coll)
	{
		assert(collision == nullptr);
		collision = coll;
	}

	MovableComponent *mov = dynamic_cast<MovableComponent*>(take_ownership);
	if (mov)
	{
		assert(movable == nullptr);
		movable = mov;
	}


	BaseAI *ai = dynamic_cast<BaseAI*>(take_ownership);
	if (ai)
	{
		assert(base_ai == nullptr);
		base_ai = ai;
	}

}


SDL_Point Entity::GetPositionAsPoint() const
{
	SDL_Point p{-1, -1};
	if (movable)
	{
		const auto & pos = movable->GetPosition();
		p.x = (int)pos.x;
		p.y = (int)pos.y;
	}
	return p;
}


const std::string *Entity::GetAIStateName() const
{
	if (not base_ai) return nullptr;

	return &base_ai->GetState();
}


void Entity::Update(float dt)
{
	for(auto &comp : components)
	{
		comp->Update(dt);
	}
}


void Entity::Render(Camera &cam)
{
	if (not movable) return;  //must have a position to render

	const auto & pos = movable->GetPosition();

	for(auto &comp : components)
	{
		comp->Render(pos.x, pos.y, cam);
	}

}


