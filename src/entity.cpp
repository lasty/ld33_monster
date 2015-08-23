//
// Created by Tristan on 23/08/2015.
//

#include "entity.h"


#include "components.h"


Entity::Entity(std::string name)
:name(name)
{

}

void Entity::AddComponent(Component *take_ownership)
{
	components.emplace_back(take_ownership);
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
	for(auto &comp : components)
	{
		comp->Render(x, y, cam);
	}

}
