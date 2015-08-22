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
		UpdateTexture();
	}
}


void Surface::Lock()
{

}


void Surface::Unlock()
{

}


void Surface::SetBlend(SDL_BlendMode mode)
{
	SDL_SetSurfaceBlendMode(surface.get(), mode);
}


void Surface::SetSurface(SDL_Surface *ptr)
{
	surface.reset(ptr);
}


void Surface::UpdateTexture()
{
	texture.reset(SDL_CreateTextureFromSurface(renderer.Get(), surface.get()));
}

