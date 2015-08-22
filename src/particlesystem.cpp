//
// Created by Tristan on 22/08/2015.
//

#include "particlesystem.h"

#include <algorithm>

#include <glm/gtc/random.hpp>


ParticleSystem::ParticleSystem(Renderer &renderer, const std::string &data_path)
: renderer(renderer)
, particles1(renderer, data_path+"particles.xcf")
{
	SetupParticles();
}

void ParticleSystem::SetupParticle(const std::string &name, Surface& surface, int size, int x, int y, int num)
{
	std::vector<Sprite> spritelist;
	for(int i=0; i<num; i++, x++)
	{
		spritelist.push_back(Sprite{surface, size, x, y, 1, 1});
	}

	particle_types.push_back(std::move(spritelist));
	particle_type_map[name] = ((int)particle_types.size() - 1);
}


void ParticleSystem::SetupParticles()
{
	SetupParticle("dust", particles1, 16, 0, 0, 8);
	SetupParticle("spark", particles1, 16, 0, 1, 8);
	SetupParticle("blood", particles1, 16, 0, 2, 8);
	SetupParticle("blood_pool", particles1, 16, 0, 3, 8);

}


void ParticleSystem::Update(float dt)
{
	for(auto & particle : particle_list)
	{
		particle.Update(dt);
	}

	RemoveDeadParticles();
}

void ParticleSystem::RemoveDeadParticles()
{
	auto partition = std::remove_if(particle_list.begin(), particle_list.end(), [](Particle &p) { return p.IsAlive(); });
	particle_list.erase(partition, particle_list.end());
}

void ParticleSystem::Render()
{
	for(auto & particle : particle_list)
	{
		auto pindex = particle.GetType();
		assert(pindex >=0 and pindex < particle_types.size());

		auto &ptype = particle_types.at(pindex);
		auto frame = particle.GetFrame(ptype.size());

		assert(frame >=0 and frame < ptype.size());

		Sprite &particlesprite = ptype.at(frame);

		particlesprite.Render(particle.GetX(), particle.GetY(), particle.GetSize());

	}
}


void ParticleSystem::AddParticleEffect(const std::string name, int x, int y)
{
	int pindex = particle_type_map.at(name);

	float rand_initial_spread = 5.0f;
	float velocity_spread = 100.0f;
	glm::vec2 gravity{0.0f, 800.0f};
	float ttl = 1.0f;
	float size = 2.0f;
	int num = 10;

	if (name == "dust")
	{
		num = 10;
		size=2.0f;
		velocity_spread = 10.0f;
		gravity.y = -10.0f;
		ttl = 1.5f;
	}
	else if (name == "spark")
	{
		num = 20;
		gravity.y = 100.0f;
		size=1.0f;
		ttl = 0.5f;
		velocity_spread = 200.0f;
		rand_initial_spread = 1.0f;
	}
	else if (name == "blood")
	{
		num = 5;
		ttl = 0.5f;
		gravity.y = 400.0f;
	}
	else if (name == "blood_pool")
	{
		num = 2;
		gravity.y = 0.4f;
		ttl = 3.0f;
		velocity_spread = 1.0f;
		rand_initial_spread = 1.0f;
	}


	for(int i=0; i< num; i++)
	{
		glm::vec2 position{x, y};
		position += glm::diskRand(rand_initial_spread);
		glm::vec2 velocity = glm::diskRand(velocity_spread);
		glm::vec2 acceleration = gravity;

		float size2 = glm::gaussRand(size, 0.5f);
		if (size2 < 1.0f) size2 = 1.0f;
		float ttl2 = glm::gaussRand(ttl, 0.9f);
		if (ttl2 < 0.1f) ttl2 = 1.0f;

		particle_list.push_back(Particle(pindex, position, velocity, acceleration, size2, ttl2));
	}

}

