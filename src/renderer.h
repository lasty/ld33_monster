
#pragma once


// Local includes
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


public:
	SDL_Renderer *get() { return renderer.get(); }

};


