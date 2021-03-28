#include "..\Headers\Position.h"

Position::Position(float speed, float pos)
{
	this->speed = speed;
	this->shape.setSize(sf::Vector2f(100.0f, 100.0f));
	this->shape.setOrigin(shape.getSize() / 2.0f);
	this->shape.setPosition(400.0f, 300.0f);
	this->shape.setFillColor(sf::Color(255, 255, 255, 255));
}

Position::~Position()
{
}

/*void Position::update(float pos, float speed)
{
	sf::Vector2f movement(0.0f, 0.0f);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		movement.x -= speed * pos;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		movement.x -= speed * pos;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		movement.x -= speed * pos;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		movement.x -= speed * pos;
}*/

/*void Position::render(sf::RenderWindow& window)
{
	//this->window->draw;
	//window.draw(shape);
}*/