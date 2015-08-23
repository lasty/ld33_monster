//
// Created by Tristan on 22/08/2015.
//


#pragma once


// Local includes
#include "sprite.h"
#include "camera.h"

// Standard includes
#include <vector>

struct Animation
{
	float frame_time = 0.2f;
	std::vector<Sprite> frames;
};



class AnimatedSprite
{
public:
	AnimatedSprite() = default;
	AnimatedSprite(Animation &animation);

private:
	Animation *animation = nullptr;

	int frame = 0;
	float frame_time;
	bool finished = false;


public:
	void Update(float dt);

	void Render(int x, int y, float  zoom, Camera &cam);

	bool GetFinished() const { return finished; }

};


