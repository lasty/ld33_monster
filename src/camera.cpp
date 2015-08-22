//
// Created by Tristan on 22/08/2015.
//

#include "camera.h"

//#include <iostream>


SDL_Point Camera::ScreenToWorld(int x, int y) const
{
	SDL_Point p{x, y};
	p.x /= zoom;
	p.y /= zoom;

	p.x += offset_x;
	p.y += offset_y;
	return p;
}


SDL_Point Camera::WorldToScreen(int x, int y) const
{
	SDL_Point p{ int( x - offset_x), int(y - offset_y)};

	p.x *= zoom;
	p.y *= zoom;

	return p;
}


SDL_Rect Camera::WorldToScreen(SDL_Rect rect) const
{
	rect.x -= offset_x;
	rect.y -= offset_y;

	rect.x *= zoom;
	rect.y *= zoom;
	rect.w *= zoom;
	rect.h *= zoom;

	return rect;
}


void Camera::Update(float dt)
{
	if (fabs(set_zoom - zoom) < 0.05f) zoom = set_zoom;
	else if (set_zoom > zoom) zoom += dt * 5.0f;
	else if (set_zoom < zoom) zoom -= dt* 5.0f;

}

void Camera::PanCamera(int x, int y)
{
	offset_x += float(x) / zoom;
	offset_y += float(y) / zoom;
}


void Camera::SetZoom(float new_zoom)
{
	set_zoom = zoom = new_zoom;
}


void Camera::ZoomCamera(float amount)
{
	set_zoom += amount;

	if (set_zoom <= 0.5f) set_zoom = 0.5f;
	if (set_zoom > 4.0f) set_zoom = 4.0f;

	//std::cout << "set zoom:  " << set_zoom << std::endl;
}
