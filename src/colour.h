//
// Created by Tristan on 22/08/2015.
//


#pragma once

// GLM Includes
#include <glm/vec4.hpp>

// SDL includes
#include <SDL_pixels.h>

// Standard includes
#include <string>

class Colour
{
public:
	Colour(float r, float g, float b, float a);
	Colour(const std::string &name);

	void SetFloat(float r, float g, float b, float a);
	void SetInt(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

private:

	SDL_Color sdl_colour;
	glm::vec4 vec4_colour;

public:

	const SDL_Color & GetSDLColor() const { return sdl_colour; }
	const glm::vec4 & GetVec4() const { return vec4_colour; }

};


