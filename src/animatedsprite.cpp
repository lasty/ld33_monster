//
// Created by Tristan on 22/08/2015.
//

#include "animatedsprite.h"


AnimatedSprite::AnimatedSprite(Animation &animation)
: animation(&animation)
, frame_time(animation.frame_time)
{

}


void AnimatedSprite::Update(float dt)
{
	frame_time -= dt;
	if (frame_time < 0.0f)
	{
		frame++;

		if (frame >= animation->frames.size())
		{
			frame = 0;
			finished = true;
		}

		frame_time = animation->frame_time;
	}
}

void AnimatedSprite::Render(int x, int y, int zoom, Camera &cam)
{
	assert(animation);
	assert(frame >=0 and frame <= (int)animation->frames.size());

	Sprite &sprite = animation->frames.at((unsigned)frame);

	sprite.Render(x, y, zoom, cam);
}
