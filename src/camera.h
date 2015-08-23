//
// Created by Tristan on 22/08/2015.
//


#pragma once


#include <SDL_rect.h>


struct Camera
{
	float offset_x = 0.0f;
	float offset_y = 0.0f;

	float zoom = 1.0f;
	float set_zoom = 1.0f;


	SDL_Point ScreenToWorld(int x, int y) const;

	SDL_Point WorldToScreen(int x, int y) const;

	SDL_Rect WorldToScreen(SDL_Rect rect) const;

	SDL_Rect WorldToScreen(SDL_Rect rect, float size) const;

	void Update(float dt);

	void PanCamera(int x, int y);

	void SetZoom(float new_zoom);
	void ZoomCamera(float amount);

};


