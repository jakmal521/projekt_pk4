#include "..\Headers\HeadBar.h"
//Konstruktor i destruktor
HeadBar::HeadBar(float x, float y)
{
	this->barShape.setSize(Vector2f(x, y * 0.04));
	this->barShape.setFillColor(Color(128, 128, 128, 200));
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

void HeadBar::setPos(sf::Vector2f viewPos, sf::Vector2f viewSize)
{
	viewPos.x -= viewSize.x / 2;
	viewPos.y -= viewSize.y / 2;
	this->barShape.setPosition(viewPos);
}