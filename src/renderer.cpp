//
// Created by Tristan on 22/08/2015.
//

#include "renderer.h"

//const auto renderer_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
const auto renderer_flags = SDL_RENDERER_ACCELERATED;

Renderer::Renderer(SDL_Window *window)
: renderer{SDL_CreateRenderer(window, -1, renderer_flags), SDL_DestroyRenderer}
{
	if(not renderer.get())
	{
		throw std::runtime_error("Could not create SDL Renderer");
	}

	SDL_SetRenderDrawBlendMode(Get(), SDL_BLENDMODE_BLEND);

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


void Renderer::DrawRect(const SDL_Rect &rect, Camera &cam)
{
	SDL_Rect r = cam.WorldToScreen(rect);

	SDL_RenderDrawRect(Get(), &r);
}


void Renderer::Blit(Surface &surf, SDL_Rect *src, SDL_Rect *dest)
{
	SDL_RenderCopy(Get(), surf.GetTexture(), src, dest);
}

