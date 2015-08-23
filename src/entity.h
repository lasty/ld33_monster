//
// Created by Tristan on 23/08/2015.
//


#pragma once

#include "camera.h"
#include "components.h"


#include <string>
#include <vector>
#include <memory>



class Entity
{
public:
	Entity(std::string name);

	Entity(Entity &&move_construct) = default;
	Entity & operator=(Entity &&move_assign) = default;

	std::string name;

	int x = 0;
	int y = 0;

	bool alive = true;

private:
	std::vector<std::unique_ptr<Component>> components;

public:
	void AddComponent(Component * take_ownership);


	void Update(float dt);

	void Render(Camera &cam);

	void SetPos(int xx, int yy)
	{
		x=xx;
		y=yy;
	}

	bool ShouldRemove() const { return not alive; }
};


