//
// Created by Tristan on 22/08/2015.
//


#pragma once


#include "surface.h"

class Sprite
{
public:
	Sprite() = default;
	Sprite(Surface &surface, int size, int x, int y, int w, int h);

private:
	Renderer *renderer = nullptr;
	Surface *surface = nullptr;

	SDL_Rect src_rect;
	SDL_Rect dest_rect;
	int offset_x;
	int offset_y;

public:

	void Render(int x, int y, int zoom);


};


