//
// Created by Tristan on 22/08/2015.
//

#include "surface.h"

// Local includes
#include "renderer.h"


// SDL Includes
#include <SDL_image.h>


Surface::Surface(Renderer &renderer, int width, int height)
: Surface(renderer, SDL_CreateRGBSurface(0,width,height,32,0,0,0,0))
{

}


Surface::Surface(Renderer &renderer, const std::string &filename)
: Surface(renderer, IMG_Load(filename.c_str()))
{

}


Surface::Surface(Renderer &renderer, SDL_Surface *ptr)
: renderer(renderer)
, surface(ptr, SDL_FreeSurface)
, texture(nullptr, SDL_DestroyTexture)
{
	if(ptr)
	{
		UpdateSurface();
		UpdateTexture();
	}
}


void Surface::Lock()
{

}


void Surface::Unlock()
{

}


void Surface::UpdateSurface()
{
	surface_rect = SDL_Rect {0, 0, surface->w, surface->h};
}


SDL_Rect Surface::GetRectOffset(int x, int y)
{
	SDL_Rect ret = GetRect();
	ret.x = x;
	ret.y = y;
	return ret;
}


void Surface::Render(int x, int y, int zoom)
{
	SDL_Rect dest { x, y, surface_rect.w * zoom, surface_rect.h * zoom };

	renderer.Blit(*this, &surface_rect, &dest);
}


void Surface::Render(int x, int y)
{
	SDL_Rect dest { x, y, surface_rect.w, surface_rect.h};

	renderer.Blit(*this, &surface_rect, &dest);
}


void Surface::Render(int x, int y, float zoom, Camera &cam)
{
	SDL_Rect dest { x, y, surface_rect.w, surface_rect.h};
	SDL_Rect cam_dest = cam.WorldToScreen(dest);
	cam_dest.w *= zoom;
	cam_dest.h *= zoom;

	renderer.Blit(*this, &surface_rect, &cam_dest);
}


void Surface::SetBlend(SDL_BlendMode mode)
{
	SDL_SetSurfaceBlendMode(surface.get(), mode);
}


void Surface::SetSurface(SDL_Surface *ptr)
{
	surface.reset(ptr);
	UpdateSurface();
}


void Surface::UpdateTexture()
{
	texture.reset(SDL_CreateTextureFromSurface(renderer.Get(), surface.get()));
}

