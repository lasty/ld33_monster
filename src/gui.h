//
// Created by Tristan on 22/08/2015.
//


#pragma once

// Local includes
#include "renderer.h"
#include "font.h"
#include "text.h"
#include "camera.h"


// SDL Includes
#include <SDL_rect.h>


// Standard includes
#include <vector>


////////////////////////////////////////////////////////////////////////////////


class Widget
{
public:
	Widget(Renderer &renderer, SDL_Rect rect);

protected:
	Renderer &renderer;
	SDL_Rect rect;

public:
	virtual void Update(float dt) { }
	virtual void Render() { }

	virtual void AlignInside(const SDL_Rect parent, int x, int y);
	virtual void AlignWith(const Widget &sibling, int x, int y);
	virtual void AlignOutside(const Widget &sibling, int border);



	virtual void MouseEnter() { }
	virtual void MouseLeave() { }

	virtual void Press() { }

	bool PointInRect(int x, int y) const;

	const SDL_Rect & GetRect() const { return rect; }

	void SetPos(int x, int y) { rect.x = x;  rect.y = y; }

};


////////////////////////////////////////////////////////////////////////////////


class Border : public Widget
{
public:
	Border(Renderer &renderer, SDL_Rect rect, Colour colour, Colour fill_colour, bool filled);

private:
	Colour colour;
	Colour fill_colour;
	bool filled;

public:
	void Render() override;
	void Render(Camera &cam);

};


////////////////////////////////////////////////////////////////////////////////


class Label : public Widget
{
public:
	Label(Renderer &renderer, Font &font, const std::string &label_text, Colour colour, int x, int y);

private:
	Text text;

public:
	void Render() override;

};


////////////////////////////////////////////////////////////////////////////////


class Button : public Widget
{
public:
	Button(Renderer &renderer, SDL_Rect rect, Font &font, const std::string &text, Colour border_colour, Colour border_fill, Colour text_colour);

private:
	Border border;
	Label label;

	void SetRects();

public:
	void Render() override;

	void AlignInside(const SDL_Rect parent, int x, int y) override;
	void AlignWith(const Widget &sibling, int x, int y) override;
	void AlignOutside(const Widget &sibling, int border) override;



};


////////////////////////////////////////////////////////////////////////////////


class GUI
{
public:
	GUI();

private:
	std::vector<Widget *> widget_list;

public:

	void AddWidget(Widget &widget);


	void Update(float dt);

	void Render();


};


