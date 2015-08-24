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

	//Try splitting horizontal and vertical components, getting buggy with both at the same time


	//Horizontal
	glm::vec2 new_pos_horiz = pos;
	new_pos_horiz.x += (velocity.x * dt);

	bool collided_world_horiz = entity->GetCollision()->HasWorldCollisionAt((int)new_pos_horiz.x, (int)new_pos_horiz.y);
	bool collided_entity_horiz = entity->GetCollision()->HasEntityCollisionAt((int)new_pos_horiz.x, (int)new_pos_horiz.y);
	bool collided_any_horiz = collided_world_horiz or collided_entity_horiz;

	//Vertical
	glm::vec2 new_pos_vert = pos;
	new_pos_vert.y += (velocity.y * dt);

	bool collided_world_vert = entity->GetCollision()->HasWorldCollisionAt((int)new_pos_vert.x, (int)new_pos_vert.y);
	bool collided_entity_vert = entity->GetCollision()->HasEntityCollisionAt((int)new_pos_vert.x, (int)new_pos_vert.y);
	bool collided_any_vert = collided_world_vert or collided_entity_vert;


	//pos += (velocity * dt);  TODO

	//SDL_Point newpos{int(pos.x), int(pos.y)};  //TODO?

	if (collided_any_horiz)
	{
		float radius = entity->GetCollision()->GetBoundingBox().w / 2;
		glm::vec2 collision_point = new_pos_horiz + (glm::normalize(velocity) * radius);
		SDL_Point collision_pt { int(collision_point.x), int(collision_point.y) };

		//rebound in other direction
		velocity.x = velocity.x * -0.5f;

		float how_hard = glm::distance(new_pos_horiz, pos_old);

		if (how_hard > 0.1f)
		{
			if (collided_world_horiz)
			{
				world->AddParticleEffect(collision_pt, "dust");
			}
			else //collided with entity
			{
				world->AddParticleEffect(collision_pt, "blood");
			}
		}
	}
	else
	{
		pos.x = new_pos_horiz.x;
	}

	if (collided_any_vert)
	{
		float radius = entity->GetCollision()->GetBoundingBox().h / 2;
		glm::vec2 collision_point = new_pos_vert + (glm::normalize(velocity) * radius);
		SDL_Point collision_pt { int(collision_point.x), int(collision_point.y) };

		//rebound in other direction
		velocity.y = velocity.y * -0.5f;

		float how_hard = glm::distance(new_pos_vert, pos_old);

		if (how_hard > 0.1f)
		{
			if (collided_world_vert)
			{
				world->AddParticleEffect(collision_pt, "dust");
			}
			else //collided with entity
			{
				world->AddParticleEffect(collision_pt, "blood");
			}
		}
	}
	else
	{
		pos.y = new_pos_vert.y;
	}

	//if (pos_old != pos)
	{
		//place new position
		entity->GetPosition()->SetPosition(pos.x, pos.y);
		entity->GetCollision()->SetPosition((int)pos.x, (int)pos.y);
	}

}


void PhysicsComponent::Impulse(const glm::vec2 &force)
{
	velocity += force;
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
