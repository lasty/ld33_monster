//
// Created by Tristan on 22/08/2015.
//

#include "gui.h"

#include <SDL.h>


Widget::Widget(Renderer &renderer, SDL_Rect rect)
: renderer(renderer)
, rect(rect)
{

}


void Widget::AlignInside(const SDL_Rect parent, int x, int y)
{
	if (x==0) //center x
	{
		x = (parent.w - rect.w) / 2;
	}
	else if (x<0)
	{
		x = parent.w - rect.w;
	}


	if (y == 0) // center y
	{
		y = (parent.h - rect.h) / 2;
	}
	else if (y < 0)
	{
		y = parent.h - rect.h;
	}

	rect.x = x;
	rect.y = y;
}


void Widget::AlignWith(const Widget &sibling, int x, int y)
{
	const SDL_Rect & other = sibling.GetRect();
	if (x==0) //center x
	{
		x = (other.w - rect.w) / 2 + other.x;
	}
	else if (x<0)
	{
		x = other.x - rect.w - x;
	}
	else if(x>0)
	{
		x = other.x + other.w + x;
	}


	if (y == 0) // center y
	{
		y = (other.h - rect.h) / 2 + other.y;
	}
	else if (y < 0)
	{
		y = other.y - rect.h - y;
	}
	else if (y > 0)
	{
		y = other.y + other.h + y;
	}

	rect.x = x;
	rect.y = y;
}


bool Widget::PointInRect(int x, int y) const
{
	SDL_Point pp{x, y};
	SDL_Point *p = &pp;
	const SDL_Rect *r = &rect;

	// Adapted from the future SDL2.0.4
	return ( (p->x >= r->x) && (p->x < (r->x + r->w)) &&
			 (p->y >= r->y) && (p->y < (r->y + r->h)) );
}

////////////////////////////////////////////////////////////////////////////////


Border::Border(Renderer &renderer, SDL_Rect rect, Colour colour, int width)
:Widget(renderer, rect)
, colour(colour)
, line_width(width)
{

}


void Border::Render()
{
	renderer.SetDrawColour(colour);

	SDL_RenderDrawRect(renderer.Get(), &rect);
}


////////////////////////////////////////////////////////////////////////////////



Label::Label(Renderer &renderer, Font &font, const std::string &label_text, Colour colour, int x, int y)
: Widget(renderer, {x, y, 0, 0})
, text(renderer, font, label_text, colour)
{
	rect.w = text.GetRect().w;
	rect.h = text.GetRect().h;
}


void Label::Render()
{
	text.Render(rect.x, rect.y);
}


////////////////////////////////////////////////////////////////////////////////


Button::Button(Renderer &renderer, SDL_Rect rect, Font &font, const std::string &text, Colour border_colour, Colour text_colour)
:Widget(renderer, rect)
, border(renderer, rect, border_colour, 1)
, label(renderer, font, text, text_colour, rect.x, rect.y)
{

}

void Button::Render()
{

	border.Render();
	label.Render();
}


////////////////////////////////////////////////////////////////////////////////


GUI::GUI()
{

}


void GUI::AddWidget(Widget &widget)
{
	widget_list.push_back(&widget);
}


void GUI::Update(float dt)
{
	//nothing to update?
}


void GUI::Render()
{
	for(Widget * w : widget_list)
	{
		w->Render();
	}
}

