//
// Created by Tristan on 23/08/2015.
//

#include "entityfactory.h"
#include "components.h"


#include <iostream>


EntityFactory::EntityFactory(SpriteSheet &sprite_sheet)
: sprite_sheet(sprite_sheet)
{

}


std::unique_ptr<Entity> EntityFactory::Create(const std::string &entitydefname, int x, int y)
{
	std::unique_ptr<Entity> ent{new Entity(entitydefname)};

	ent->SetPos(x, y);

	if (entitydefname == "snake")
	{
		ent->AddComponent(new SpriteComponent(sprite_sheet.GetSprite("snake")));
	}
	else if (entitydefname == "hero")
	{
		ent->AddComponent(new SpriteComponent(sprite_sheet.GetSprite("hero")));
	}
	else if (entitydefname == "bat")
	{
		ent->AddComponent(new SpriteComponent(sprite_sheet.GetSprite("bat")));
	}
	else if (entitydefname == "spikes")
	{
		ent->AddComponent(new SpriteComponent(sprite_sheet.GetSprite("spikes")));
	}

	else
	{
		std::cout << "Unknown entity type: " << entitydefname << std::endl;
		throw std::runtime_error("Unknown entity type");
	}

	return ent;
}


void EntityFactory::SetupEntityList()
{

}
