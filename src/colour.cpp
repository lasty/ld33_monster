//
// Created by Tristan on 22/08/2015.
//

#include "colour.h"


Colour::Colour(float r, float g, float b, float a)
{
	SetFloat(r, g, b, a);
}


Colour::Colour(const std::string &name)
{
	if (name == "red") SetFloat(1.0f, 0.0f, 0.0f, 1.0f);
	else if (name == "green") SetFloat(0.0f, 1.0f, 0.0f, 1.0f);
	else if (name == "blue") SetFloat(0.0f, 0.0f, 1.0f, 1.0f);
	else if (name == "yellow") SetFloat(1.0f, 1.0f, 0.0f, 1.0f);
	else if (name == "white") SetFloat(1.0f, 1.0f, 1.0f, 1.0f);

}


void Colour::SetFloat(float r, float g, float b, float a)
{
	vec4_colour = glm::vec4{r, g, b, a};

	sdl_colour = SDL_Color{ uint8_t(r * 255.0f), uint8_t(g * 255.0f), uint8_t(b * 255.0f), uint8_t(a * 255.0f) };
}


void Colour::SetInt(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	sdl_colour = SDL_Color{ r, g, b, a };
	vec4_colour = glm::vec4{ r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f };
}

