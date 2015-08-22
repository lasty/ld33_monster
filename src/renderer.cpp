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
	SDL_RenderClear(get());
}



void Renderer::Present()
{
	SDL_RenderPresent(get());
}


