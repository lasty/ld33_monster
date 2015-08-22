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

	rect.x = x + parent.x;
	rect.y = y + parent.y;
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


void Widget::AlignOutside(const Widget &sibling, int border)
{
	const SDL_Rect &other = sibling.GetRect();

	rect.w = other.w + border * 2;
	rect.h = other.h + border * 2;
	rect.x = other.x - border;
	rect.y = other.y - border;
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


Border::Border(Renderer &renderer, SDL_Rect rect, Colour colour, Colour fill_colour, bool filled)
:Widget(renderer, rect)
, colour(colour)
, fill_colour(fill_colour)
, filled(filled)
{

}

void Border::Render(Camera &cam)
{
	SDL_Rect rect2 = cam.WorldToScreen(rect);

	if (filled)
	{
		renderer.SetDrawColour(fill_colour);

		SDL_RenderFillRect(renderer.Get(), &rect2);
	}

	renderer.SetDrawColour(colour);

	SDL_RenderDrawRect(renderer.Get(), &rect2);
}



void Border::Render()
{
	if (filled)
	{
		renderer.SetDrawColour(fill_colour);

		SDL_RenderFillRect(renderer.Get(), &rect);
	}

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


Button::Button(Renderer &renderer, SDL_Rect rect, Font &font, const std::string &text, Colour border_colour, Colour border_fill, Colour text_colour)
:Widget(renderer, rect)
, border(renderer, rect, border_colour, border_fill, true)
, label(renderer, font, text, text_colour, rect.x, rect.y)
{
	SetRects();
	rect.w =label.GetRect().w;
	rect.h = label.GetRect().h;
}

void Button::Render()
{
	border.Render();
	label.Render();
}

void Button::SetRects()
{
	label.AlignInside(rect, 0, 0);
	border.AlignOutside(label, 1);
}

void Button::AlignInside(const SDL_Rect parent, int x, int y)
{
	Widget::AlignInside(parent, x, y);
	SetRects();
}

void Button::AlignWith(const Widget &sibling, int x, int y)
{
	Widget::AlignWith(sibling, x, y);
	SetRects();
}

void Button::AlignOutside(const Widget &sibling, int border)
{
	Widget::AlignOutside(sibling, border);
	SetRects();
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

