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


Entity EntityFactory::Create(const std::string &entitydefname, int x, int y)
{
	Entity ent{entitydefname};

	if (entitydefname == "snake")
	{
		ent.AddComponent(new SpriteComponent(sprite_sheet.GetSprite("snake")));
		ent.SetPos(x, y);
	}
	else if (entitydefname == "hero")
	{
		ent.AddComponent(new SpriteComponent(sprite_sheet.GetSprite("hero")));
		ent.SetPos(x, y);
	}
	else if (entitydefname == "bat")
	{
		ent.AddComponent(new SpriteComponent(sprite_sheet.GetSprite("bat")));
		ent.SetPos(x, y);
	}
	else if (entitydefname == "spikes")
	{
		ent.AddComponent(new SpriteComponent(sprite_sheet.GetSprite("spikes")));
		ent.SetPos(x, y);
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
