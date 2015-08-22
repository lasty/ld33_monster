//
// Created by Tristan on 22/08/2015.
//

#include "sprite.h"

#include "renderer.h"


Sprite::Sprite(Surface &surface, int size, int x, int y, int w, int h)
: renderer(&surface.GetRenderer())
, surface(&surface)
, src_rect{size*x, size*y, size*w, size*h}
, dest_rect{0, 0, size*w, size*h}
, offset_x(w*size/2)
, offset_y(h*size/2)
{

	assert(renderer);
	assert(this->surface);
}


void Sprite::Render(int x, int y, int zoom)
{
	assert(renderer);
	assert(surface);

	dest_rect.x = x - offset_x;
	dest_rect.y = y - offset_y;
	dest_rect.w = src_rect.w * zoom;
	dest_rect.h = src_rect.h * zoom;

	renderer->Blit(*surface, &src_rect, &dest_rect);
}

