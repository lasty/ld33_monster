//
// Created by Tristan on 22/08/2015.
//


#pragma once

#include "surface.h"
#include "font.h"
#include "colour.h"


class Text : public Surface
{
public:
	Text(Renderer &renderer, Font &font, const std::string &text, const Colour &col);

private:
	Font &font;
	std::string text;
	Colour colour;

public:
	void SetText(const std::string &new_text);
	void SetColour(const Colour &new_colour);
	void SetBoth(const std::string &new_text, const Colour &new_colour);


};


