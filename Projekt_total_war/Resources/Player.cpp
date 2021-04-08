#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include <iostream>
#include "..\Headers\Player.h"
#include "..\Headers\District.h"

Player::Player()
{
}

Player::~Player()
{
}

void Player::initPla(sf::Color color, sf::Vector2f vec)
{
	this->playerShape.setFillColor(color);
	this->playerShape.setSize(vec);
}

void Player::update()
{
}

void Player::render(sf::RenderTarget* target)
{
	target->draw(this->playerShape);
}