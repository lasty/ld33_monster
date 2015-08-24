//
// Created by Tristan on 23/08/2015.
//


#pragma once


#include "components.h"
#include "world.h"
#include "input.h"

#include <vector>


class BaseAI : public Component
{
public:
	BaseAI(Entity *entity, World *world);

private:
	Entity *entity = nullptr;
	World *world = nullptr;


	std::string state = "idle";
	float pause_timer = 0.2f;

protected:
	World & GetWorld();
	const World & GetWorld() const;

	Entity & GetEntity();
	const Entity & GetEntity() const;


	const TileDef * PeekMap(int x, int y) const;

	Entity * PeekEntity(int x, int y) const;


	SDL_Rect GetBoundingBox() const;

	SDL_Rect GetSensorLeft() const;
	SDL_Rect GetSensorRight() const;

	bool CollidesWorld(const SDL_Rect& rect) const;
	bool CollidesEntities(const SDL_Rect& rect) const;


	void SetState(const std::string &newstate) { state = newstate; }


	void SetRandomState(std::vector<std::string> list);

	void SetPause(float newpause);


	virtual void AITick() { }


public:

	virtual void Update(float dt) override;


	const std::string & GetState() const { return state; }

};



////////////////////////////////////////////////////////////////////////////////


class SimpleMoverAI : public BaseAI
{
public:
	SimpleMoverAI(Entity *entity, World *world, Input *input);

protected:
	float pause_timer = 0.2f;
	Input *input = nullptr;

public:
	void AITick() override;


	virtual void Update(float dt) override;
};

