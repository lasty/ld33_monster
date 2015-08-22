//
// Created by Tristan on 22/08/2015.
//


#pragma once


//SDL Includes
#include <SDL_ttf.h>

//Standard includes
#include <memory>


class Font
{
public:
	Font(const std::string &filename, int pointsize);

private:
	std::unique_ptr<TTF_Font, decltype(&TTF_CloseFont)> font;

public:
	TTF_Font * GetFont() const { return font.get(); }
};


