//
// Created by Tristan on 22/08/2015.
//


#pragma once


#include "renderer.h"
#include "sprite.h"
#include "particle.h"

#include <string>
#include <map>
#include <vector>


class ParticleSystem
{
public:
	ParticleSystem(Renderer &renderer, const std::string &data_path);

private:
	Renderer &renderer;
	Surface particles1;
	std::map<std::string, int> particle_type_map;
	std::vector<std::vector<Sprite>> particle_types;

	std::vector<Particle> particle_list;

	void SetupParticle(const std::string &name, Surface& surface, int size, int x, int y, int num);
	void SetupParticles();

public:

	void Update(float dt);

	void RemoveDeadParticles();

	void Render(Camera &cam);


	void AddParticleEffect(const std::string name,  int x, int y);


};


