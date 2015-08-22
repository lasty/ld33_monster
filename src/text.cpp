//
// Created by Tristan on 22/08/2015.
//

#include "text.h"


Text::Text(Renderer &renderer, Font &font, const std::string &text, const Colour &col)
: Surface(renderer, TTF_RenderText_Blended(font.GetFont(), text.c_str(), col.GetSDLColor()))
, font(font)
, text(text)
, colour(col)
{
	SetBlend(SDL_BLENDMODE_BLEND);

	UpdateTexture();
}


void Text::SetText(const std::string &new_text)
{
	if(text != new_text)
	{
		SetSurface(TTF_RenderText_Blended(font.GetFont(), text.c_str(), colour.GetSDLColor()));
		SetBlend(SDL_BLENDMODE_BLEND);
		UpdateTexture();

		text = new_text;
	}
}


void Text::SetColour(const Colour &new_colour)
{
	colour = new_colour;

	SetSurface(TTF_RenderText_Blended(font.GetFont(), text.c_str(), colour.GetSDLColor()));
	SetBlend(SDL_BLENDMODE_BLEND);

	UpdateTexture();

}


void Text::SetBoth(const std::string &new_text, const Colour &new_colour)
{
	colour = new_colour;
	text = new_text;

	SetSurface(TTF_RenderText_Blended(font.GetFont(), text.c_str(), colour.GetSDLColor()));
	SetBlend(SDL_BLENDMODE_BLEND);

	UpdateTexture();
}

