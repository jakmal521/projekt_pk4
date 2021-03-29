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

void Position::update()
{
	sf::Vector2f movement(0.0f, 0.0f);
	float speed = 2.f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		this->shape.move(-speed, 0);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		this->shape.move(speed, 0);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		this->shape.move(0, -speed);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		this->shape.move(0, speed);
}

void Position::render(sf::RenderWindow& window)
{
	//this->window->draw;
	//window.draw(shape);
}