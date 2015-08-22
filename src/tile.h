//
// Created by Tristan on 22/08/2015.
//


#pragma once


#include "surface.h"


class Tile
{
public:
	Tile(Surface &surf, int size, int x, int y, int w, int h);

private:

	Surface &surface;
	Renderer &renderer;
	SDL_Rect src_rect;
	SDL_Rect dest_rect;


public:

	void Render(int x, int y);
	void Render(int x, int y, int zoom);

};


