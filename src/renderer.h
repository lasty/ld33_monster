
#pragma once


// Local includes
#include "surface.h"
#include "colour.h"


// SDL includes
#include <SDL_render.h>


// Standard includes
#include <memory>

class Renderer
{
public:
	Renderer(SDL_Window *window);

private:
	std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> renderer;

public:

	void Clear();
	void Present();

	void SetDrawColour(const Colour &colour);

	void Blit(Surface &surf, SDL_Rect *src, SDL_Rect *dest);

public:
	SDL_Renderer *Get() { return renderer.get(); }

};


