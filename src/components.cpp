//
// Created by Tristan on 23/08/2015.
//

#include "components.h"


#include "entity.h"
#include "renderer.h"
#include "world.h"


#include <glm/geometric.hpp>

#include <iostream>
#include <sstream>


////////////////////////////////////////////////////////////////////////////////


Component::Component()
{}

Component::~Component()
{}

void Component::Render(int x, int y, Camera &cam)
{ }

void Component::Update(float dt)
{ }


////////////////////////////////////////////////////////////////////////////////


SpriteComponent::SpriteComponent(AnimatedSprite s)
: animated_sprite(s)
{ }


void SpriteComponent::Update(float dt)
{
	animated_sprite.Update(dt);
}


void SpriteComponent::Render(int x, int y, Camera &cam)
{
	animated_sprite.Render(x, y, zoom, cam);
}


////////////////////////////////////////////////////////////////////////////////



CollisionComponent::CollisionComponent(Entity *entity, World *world, int w, int h)
: entity(entity)
, world(world)
{
	boundingbox.w = w;
	boundingbox.h = h;

	const auto & pos = entity->GetPositionAsPoint();

	SetPosition(pos.x, pos.y);
}


void CollisionComponent::SetPosition(int x, int y)
{
	boundingbox.x = x - (boundingbox.w / 2);
	boundingbox.y = y - (boundingbox.h / 2);
}


float CollisionComponent::GetRadius() const
{
	float max = glm::max(boundingbox.w, boundingbox.h);
	return max/2.0f;
}

bool CollisionComponent::HasEntityCollisionAt(int x, int y) const
{
	if (not world) return false;

	SDL_Rect newbb = boundingbox;
	newbb.x = x - (boundingbox.w / 2);
	newbb.y = y - (boundingbox.h / 2);

	return world->HasCollisionEntity(newbb, entity);

}


bool CollisionComponent::HasWorldCollisionAt(int x, int y) const
{
	if (not world) return false;

	SDL_Rect newbb = boundingbox;
	newbb.x = x - (boundingbox.w / 2);
	newbb.y = y - (boundingbox.h / 2);

	return world->HasCollisionWorld(newbb);
}


bool CollisionComponent::HasCollisionAt(int x, int y) const
{
	return HasWorldCollisionAt(x, y) or HasEntityCollisionAt(x, y);
}



bool CollisionComponent::HasCollision() const
{
	if (not world) return false;

	return world->HasCollisionAny(boundingbox, entity);
}


////////////////////////////////////////////////////////////////////////////////


MovableComponent::MovableComponent(Entity *entity, int x, int y)
:entity(entity)
,position{x, y}
{

}

void MovableComponent::SetPosition(float x, float y)
{
	position.x = x;
	position.y = y;
}


////////////////////////////////////////////////////////////////////////////////


PhysicsComponent::PhysicsComponent(Entity *entity, World *world, bool gravity)
: entity(entity)
, world(world)
, gravity(gravity)
{
	assert(entity);
	assert(world);

}

void PhysicsComponent::Update(float dt)
{
	assert(entity);
	assert(entity->GetCollision());
	assert(entity->GetPosition());


	glm::vec2 pos = entity->GetPosition()->GetPosition();
	glm::vec2 pos_old = pos;

	if (gravity)
	{
		//pos.y += 1;
		glm::vec2 gravity_vec { 0.0f, 32 * 18.0f };

		velocity += (gravity_vec * dt);
	}

	pos += (velocity * dt);

	SDL_Point newpos{int(pos.x), int(pos.y)};

	bool collided_world = entity->GetCollision()->HasWorldCollisionAt(newpos.x, newpos.y);
	bool collided_entity = entity->GetCollision()->HasEntityCollisionAt(newpos.x, newpos.y);
	bool collided_any = collided_world or collided_entity;

	if (collided_any)
	{
		float radius = entity->GetCollision()->GetRadius();
		glm::vec2 collision_point = pos + (glm::normalize(velocity) * radius);
		SDL_Point collision_pt { int(collision_point.x), int(collision_point.y) };

		//rebound in other direction
		velocity = velocity * -0.5f;

		float how_hard = glm::distance(pos, pos_old);

		if (how_hard > 0.1f)
		{

			if (collided_world)
			{
				world->AddParticleEffect(collision_pt, "dust");
			}
			else //collided with entity
			{
				world->AddParticleEffect(collision_pt, "spark");
			}
		}
	}
	else
	{
		//place new position
		entity->GetPosition()->SetPosition(pos.x, pos.y);
		entity->GetCollision()->SetPosition(newpos.x, newpos.y);
	}

}


////////////////////////////////////////////////////////////////////////////////


Colour bounding_box_colour1 { "green" };
Colour bounding_box_colour2 { "red" };

DebugComponent::DebugComponent(Entity *entity, Renderer &renderer, Font &font, std::string debug_text, Colour colour)
: entity(entity)
, renderer(renderer)
, text(renderer, font, debug_text, colour)
, debug_text(debug_text)
{

}


void DebugComponent::SetText(const std::string &new_text)
{
	if (debug_text != new_text)
	{
		debug_text = new_text;
		text.SetText(new_text);
	}
}


void DebugComponent::Update(float dt)
{
	std::stringstream ss;

	ss << entity->name;

	if (entity->GetAIStateName())
	{
		ss << " - " <<  *entity->GetAIStateName();
	}

	SetText(ss.str());
}


void DebugComponent::Render(int x, int y, Camera &cam)
{
	int xoff = 0;
	int yoff = 0;

	if (entity->GetCollision())
	{
		SDL_Rect bb = entity->GetCollision()->GetBoundingBox();

		if (entity->GetCollision()->HasCollision())
		{
			renderer.SetDrawColour(bounding_box_colour2);
		}
		else
		{
			renderer.SetDrawColour(bounding_box_colour1);
		}


		renderer.DrawRect(bb, cam);

		xoff = bb.x - x;
		yoff = bb.y - y;
	}

	text.Render(x+xoff, y-yoff, 0.5f, cam);

}




////////////////////////////////////////////////////////////////////////////////
