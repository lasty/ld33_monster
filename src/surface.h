//
// Created by Tristan on 22/08/2015.
//

#pragma once


//Wrapper around SDL surface class, and render texture


// Local includes
class Renderer;//#include "renderer.h"

// SDL includes
#include <SDL_surface.h>
#include <SDL_render.h>

// Standard includes
#include <memory>
#include <assert.h>


class Surface
{
public:
	Surface(Renderer &renderer, int width, int height);
	Surface(Renderer &renderer, const std::string &filename);
	Surface(Renderer &renderer, SDL_Surface *ptr);

private:
	Renderer &renderer;
	std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)> surface;
	std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> texture;

	SDL_Rect surface_rect;
	SDL_BlendMode blend_mode = SDL_BLENDMODE_NONE;

public:

	void SetBlend(SDL_BlendMode mode);

	void Lock();
	void Unlock();

	void UpdateSurface();
	void UpdateTexture();

	SDL_Rect GetRectOffset(int x, int y);


	void Render(int x, int y);
	void Render(int x, int y, int zoom);


protected:
	void SetSurface(SDL_Surface *ptr);


public:
	SDL_Surface * GetSurface() const { return surface.get(); }
	SDL_Texture * GetTexture() const { return texture.get(); }

	const SDL_Rect & GetRect() const { return surface_rect; }

	int GetWidth() const { return GetRect().w; }
	int GetHeight() const { return GetRect().h; }

};


