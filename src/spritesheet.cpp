//
// Created by Tristan on 22/08/2015.
//

#include "spritesheet.h"


SpriteSheet::SpriteSheet(Renderer &renderer, const std::string &data_path)
: renderer(renderer)
, sprites1(renderer, data_path+"sprites1.xcf")
{

	SetupSprites();

}

Animation &SpriteSheet::GetAnimation(const std::string &name)
{
	auto it = spritelist.find(name);
	if (it == spritelist.end())
	{
		throw std::runtime_error("Sprite name not found");
	}

	return it->second;
}


AnimatedSprite SpriteSheet::GetSprite(const std::string &name)
{
	AnimatedSprite sprite{GetAnimation(name)};
	return sprite;
}



void SpriteSheet::SetupSprites()
{
	spritelist["bat"] = Animation{ 0.1f,
								   { Sprite{sprites1, 32, 0, 0, 1, 1}
								   , Sprite{sprites1, 32, 1, 0, 1, 1}
								   , Sprite{sprites1, 32, 2, 0, 1, 1}
								   , Sprite{sprites1, 32, 3, 0, 1, 1}}};

	spritelist["rock"] = Animation{ 0.1f,
									{ Sprite{sprites1, 32, 0, 1, 1, 1}
									,  Sprite{sprites1, 32, 1, 1, 1, 1}}};

	spritelist["rock_break"] = Animation{ 0.1f,
										  { Sprite{sprites1, 32, 0, 2, 1, 1}
										  ,  Sprite{sprites1, 32, 1, 2, 1, 1}
										  ,  Sprite{sprites1, 32, 2, 2, 1, 1}
										  ,  Sprite{sprites1, 32, 3, 2, 1, 1}}};

	spritelist["spikes"] = Animation{ 0.1f,
									  { Sprite{sprites1, 32, 0, 3, 1, 1}
									  ,  Sprite{sprites1, 32, 1, 3, 1, 1}
									  ,  Sprite{sprites1, 32, 2, 3, 1, 1}
									  ,  Sprite{sprites1, 32, 3, 3, 1, 1}
									  ,  Sprite{sprites1, 32, 4, 3, 1, 1}
									  ,  Sprite{sprites1, 32, 5, 3, 1, 1}
									  ,  Sprite{sprites1, 32, 6, 3, 1, 1}}};

	spritelist["chest"] = Animation{ 0.1f, { Sprite{sprites1, 32, 7, 0, 1, 1}}};

	spritelist["bag"] = Animation{ 0.1f, { Sprite{sprites1, 32, 7, 1, 1, 1}}};


	spritelist["hero"] = Animation{ 0.1f,
									{ Sprite{sprites1, 16, 0, 14, 1, 2}
									, Sprite{sprites1, 16, 1, 14, 1, 2}
									, Sprite{sprites1, 16, 2, 14, 1, 2}
									, Sprite{sprites1, 16, 3, 14, 1, 2}
									, Sprite{sprites1, 16, 4, 14, 1, 2}
									, Sprite{sprites1, 16, 5, 14, 1, 2}
									, Sprite{sprites1, 16, 6, 14, 1, 2}
									, Sprite{sprites1, 16, 7, 14, 1, 2}}};

	spritelist["snake"] = Animation{ 0.1f,
									 { Sprite{sprites1, 16, 0, 9, 2, 1}
									 , Sprite{sprites1, 16, 2, 9, 2, 1}
									 , Sprite{sprites1, 16, 4, 9, 2, 1}
									 , Sprite{sprites1, 16, 6, 9, 2, 1}
									 , Sprite{sprites1, 16, 8, 9, 2, 1}
									 , Sprite{sprites1, 16, 10, 9, 2, 1}}};


}


