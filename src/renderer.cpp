//
// Created by Tristan on 22/08/2015.
//

#include "renderer.h"

const auto renderer_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;

Renderer::Renderer(SDL_Window *window)
: renderer{SDL_CreateRenderer(window, -1, renderer_flags), SDL_DestroyRenderer}
{
	if(not renderer.get())
	{
		throw std::runtime_error("Could not create SDL Renderer");
	}
}


void Renderer::Clear()
{
	SDL_RenderClear(Get());
}



void Renderer::Present()
{
	SDL_RenderPresent(Get());
}


void Renderer::SetDrawColour(const Colour &colour)
{
	SDL_SetRenderDrawColor(Get(), colour.GetSDLColor().r, colour.GetSDLColor().g,
						   colour.GetSDLColor().b, colour.GetSDLColor().a);
}


void Renderer::Blit(Surface &surf, SDL_Rect *src, SDL_Rect *dest)
{
	SDL_RenderCopy(Get(), surf.GetTexture(), src, dest);
}

