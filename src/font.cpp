//
// Created by Tristan on 22/08/2015.
//

#include "font.h"

#include <stdexcept>


Font::Font(const std::string &filename, int pointsize)
: font(TTF_OpenFont(filename.c_str(), pointsize), TTF_CloseFont)
{

	if (not font.get())
	{
		throw std::runtime_error("Could not open font file");
	}

}
