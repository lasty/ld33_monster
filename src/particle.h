//
// Created by Tristan on 22/08/2015.
//


#pragma once


#include <glm/vec2.hpp>


class Particle
{
public:
	Particle(int particle_type, glm::vec2 position, glm::vec2 velocity,  glm::vec2 acceleration, float size, float ttl);

private:

	glm::vec2 last_position;
	glm::vec2 position;
	glm::vec2 velocity;
	glm::vec2 acceleration;

	float size;

	float time;
	float ttl;

	int particle_type = 0;

public:

	void Update(float dt);

	int GetX() const { return (int) position.x; }
	int GetY() const { return (int) position.y; }

	int GetLastX() const { return (int) last_position.x; }
	int GetLastY() const { return (int) last_position.y; }

	int GetSize() const { return (int) size; }

	int GetType() const { return particle_type; }

	int GetFrame(int num_frames) const;

	bool IsAlive() const { return time > ttl; }

};


