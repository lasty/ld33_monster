//
// Created by Tristan on 22/08/2015.
//

#include "particle.h"


Particle::Particle(int particle_type, glm::vec2 position, glm::vec2 velocity, glm::vec2 acceleration, float size, float ttl)
: last_position(position)
, position(position)
, velocity(velocity)
, acceleration(acceleration)
, size(size)
, time(0.0f)
, ttl(ttl)
, particle_type(particle_type)
{

}


void Particle::Update(float dt)
{
	time += dt;

	last_position = position;

	velocity += acceleration * dt;
	position += velocity * dt;
}


int Particle::GetFrame(int num_frames) const
{
	int f = int((time / ttl) * num_frames);

	if (f < 0) f = 0;
	if (f > num_frames) f = num_frames;

	return f;
}

