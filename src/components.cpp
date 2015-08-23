//
// Created by Tristan on 23/08/2015.
//

#include "components.h"


#include "entity.h"
#include "renderer.h"

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



CollisionComponent::CollisionComponent(Entity *entity, int w, int h)
: entity(entity)
{
	boundingbox.w = w;
	boundingbox.h = h;

	const auto & pos = entity->GetPosition();

	SetPosition(pos.x, pos.y);
}


void CollisionComponent::SetPosition(int x, int y)
{
	boundingbox.x = x - (boundingbox.w / 2);
	boundingbox.y = y - (boundingbox.h / 2);
}


////////////////////////////////////////////////////////////////////////////////



MovableComponent::MovableComponent(Entity *entity, int x, int y)
:entity(entity)
,position{x, y}
{

}

void MovableComponent::SetPosition(int x, int y)
{
	position.x = x;
	position.y = y;
}


////////////////////////////////////////////////////////////////////////////////


DebugComponent::DebugComponent(Entity *entity, Renderer &renderer, Font &font, std::string debug_text, Colour colour)
: entity(entity)
, renderer(renderer)
, text(renderer, font, debug_text, colour)
, debug_text(debug_text)
{

}

void DebugComponent::SetText(const std::string new_text)
{
	debug_text = new_text;
	text.SetText(new_text);
}


void DebugComponent::Render(int x, int y, Camera &cam)
{
	int xoff = 0;
	int yoff = 0;

	if (entity->GetCollision())
	{
		SDL_Rect bb = entity->GetCollision()->GetBoundingBox();

		renderer.DrawRect(bb, cam);

		xoff = bb.x - x;
		yoff = bb.y - y;
	}

	text.Render(x+xoff, y-yoff, 0.5f, cam);

}


////////////////////////////////////////////////////////////////////////////////
