//
// Created by Tristan on 22/08/2015.
//


#pragma once


#include <SDL_rect.h>


struct Camera
{
	int offset_x = -10;
	int offset_y = -10;

	int zoom = 1;


	SDL_Point ScreenToWorld(int x, int y) const
	{
		SDL_Point p{x + offset_x, y + offset_y};
		//TODO zoom;
		return p;
	}

	SDL_Point WorldToScreen(int x, int y) const
	{
		SDL_Point p{x - offset_x, y - offset_y};
		//TODO zoom;
		return p;
	}


	void PanCamera(int x, int y)
	{
		offset_x += x;
		offset_y += y;
	}

};


