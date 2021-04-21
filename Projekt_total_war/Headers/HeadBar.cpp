#include "..\Headers\HeadBar.h"
//Konstruktor i destruktor
HeadBar::HeadBar(float x, float y)
{
	this->barShape.setSize(Vector2f(x , y* 0.1));
	this->barShape.setFillColor(Color::Magenta);
	this->barShape.setPosition(0, 0);
}

HeadBar::~HeadBar()
{
}
//updatowanie i wyœwietlanie na ekranie
void HeadBar::update()
{
}
void HeadBar::render(RenderTarget* target)
{
	target->draw(this->barShape);
}
