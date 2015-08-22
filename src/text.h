//
// Created by Tristan on 22/08/2015.
//


#pragma once

#include "surface.h"
#include "font.h"


class Text : public Surface
{
public:
	Text(Renderer &renderer, Font &font, const std::string &text, const SDL_Color &col);

private:
	Font &font;
	std::string text;
	SDL_Color colour;

public:
	void SetText(const std::string &new_text);
	void SetColour(const SDL_Color &new_colour);
	void SetBoth(const std::string &new_text, const SDL_Color &new_colour);


};


