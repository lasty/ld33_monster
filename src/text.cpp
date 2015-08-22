//
// Created by Tristan on 22/08/2015.
//

#include "text.h"


Text::Text(Renderer &renderer, Font &font, const std::string &text, const SDL_Color &col)
: Surface(renderer, TTF_RenderText_Blended(font.GetFont(), text.c_str(), col))
, font(font)
, text(text)
, colour(col)
{
	UpdateTexture();

}


void Text::SetText(const std::string &new_text)
{
	if(text != new_text)
	{
		SetSurface(TTF_RenderText_Blended(font.GetFont(), text.c_str(), colour));
		UpdateTexture();
	}
}


void Text::SetColour(const SDL_Color &new_colour)
{
	colour = new_colour;

	SetSurface(TTF_RenderText_Blended(font.GetFont(), text.c_str(), colour));
	UpdateTexture();

}


void Text::SetBoth(const std::string &new_text, const SDL_Color &new_colour)
{
	colour = new_colour;

	SetSurface(TTF_RenderText_Blended(font.GetFont(), text.c_str(), colour));
	UpdateTexture();
}

