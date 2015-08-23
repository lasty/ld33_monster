//
// Created by Tristan on 23/08/2015.
//

#include "entityfactory.h"
#include "components.h"


#include <iostream>


Colour debug_text_colour { "yellow" };


EntityFactory::EntityFactory(Renderer &renderer, Font &debug_font, SpriteSheet &sprite_sheet)
: renderer(renderer)
, debug_font(debug_font)
, sprite_sheet(sprite_sheet)
{

}


std::unique_ptr<Entity> EntityFactory::Create(const std::string &entitydefname, int x, int y)
{
	std::unique_ptr<Entity> ent{new Entity(entitydefname)};

	ent->AddComponent(new MovableComponent(ent.get(), x, y));

	if (entitydefname == "snake")
	{
		ent->AddComponent(new SpriteComponent(sprite_sheet.GetSprite("snake")));

		ent->AddComponent(new CollisionComponent(ent.get(), 32, 16));

	}
	else if (entitydefname == "hero")
	{
		ent->AddComponent(new SpriteComponent(sprite_sheet.GetSprite("hero")));

		ent->AddComponent(new CollisionComponent(ent.get(), 16, 32));

	}
	else if (entitydefname == "bat")
	{
		ent->AddComponent(new SpriteComponent(sprite_sheet.GetSprite("bat")));
		ent->AddComponent(new CollisionComponent(ent.get(), 32, 32));
	}
	else if (entitydefname == "spikes")
	{
		ent->AddComponent(new SpriteComponent(sprite_sheet.GetSprite("spikes")));
		ent->AddComponent(new CollisionComponent(ent.get(), 32, 32));
	}
	else
	{
		std::cout << "Unknown entity type: " << entitydefname << std::endl;
		throw std::runtime_error("Unknown entity type");
	}

	ent->AddComponent(new DebugComponent(ent.get(), renderer, debug_font, entitydefname, debug_text_colour));


	return ent;
}


void EntityFactory::SetupEntityList()
{

}
