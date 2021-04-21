#include "..\Headers\HeadBar.h"
//Konstruktor i destruktor
HeadBar::HeadBar(float x, float y)
{
	this->barShape.setSize(Vector2f(x, y * 0.04));
	this->barShape.setFillColor(Color(128, 128, 128, 200));
}

HeadBar::~HeadBar()
{
}
//updatowanie i wyœwietlanie na ekranie
void HeadBar::update()
{
}

void HeadBar::render(sf::RenderWindow* window)
{
	window->draw(barShape);
}

void HeadBar::setPos(sf::Vector2f viewPos, sf::Vector2f viewOrigin)
{
	viewPos -= viewOrigin;
	this->barShape.setPosition(viewPos);
}