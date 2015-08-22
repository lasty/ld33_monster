//
// Created by Tristan on 22/08/2015.
//

#include "tile.h"

#include "renderer.h"

Tile::Tile(Surface &surf, int size, int x, int y, int w, int h)
: surface(surf)
, renderer(surf.GetRenderer())
, src_rect{x*size, y*size, w*size, h*size}
, dest_rect{0, 0, w*size, h*size}
{

}


void Tile::Render(int x, int y)
{
	dest_rect.x = x;
	dest_rect.y = y;

	renderer.Blit(surface, &src_rect, &dest_rect);
}


void Tile::Render(int x, int y, Camera &cam)
{
	dest_rect.x = x;
	dest_rect.y = y;

	SDL_Rect dest = cam.WorldToScreen(dest_rect);

	renderer.Blit(surface, &src_rect, &dest);
}
