#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include <iostream>
#include "..\Headers\Player.h"

Player::Player()
{
}

Player::~Player()
{
}

//Inicjalizacja gracza
void Player::initPla(map<string, District*> districts)
{
	this->mouseHeld = false;
	//Obrazek gracza
	//this->playerShape.setFillColor(sf::Color::Red);
	this->playerTexture.loadFromFile("JPG/knight.png");
	this->playerShape.setTexture(&this->playerTexture);
	this->playerShape.setSize(Vector2f(100.f, 100.f));
	this->playerShape.setOrigin(0.5 * this->playerShape.getSize().x, 1 * this->playerShape.getSize().y);
	this->playerShape.setPosition(districts["Calabria"]->returnPosition());
	//Obrazek poruszania siê
	this->moveTexture.loadFromFile("JPG/x.png");
	this->moveShape.setTexture(&this->moveTexture);
	this->moveShape.setPosition(sf::Vector2f(-100.f, -100.f));
	this->moveShape.setSize(sf::Vector2f(50.f, 50.f));
	this->moveShape.setOrigin(sf::Vector2f(25.f, 25.f));
	//Atrybuty gracza
	this->moveSpeed = 600;
}

// TODO:

/// <summary>Wykorzystuje funkcje z district.h ¿eby sprawdziæ czy kursor znajduje siê nad dystryktem, po klikniêciu prawym przyciskiem myszy pojawia siê X, po czym klikaj¹c w niego pojawia siê tekstura gracza.</summary>
/// <param name="">Pozycja kursora | WskaŸnik na dystrykt</param>
/// <returns>Void</returns>
void Player::update(sf::Vector2f mpos, District* districts)
{
	if (districts->returnIsPlayer())
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			if (this->mouseHeld == false)
			{
				this->mouseHeld = true;
				std::cout << "Ruszam z kurwami na " << districts->name << "\n";
				if (this->moveShape.getGlobalBounds().contains(mpos))
				{
					this->playerShape.setPosition(mpos);	//mpos czy pozycja moveShape???
					this->moveShape.setPosition(sf::Vector2f(-100.f, -100.f)); //Wyrzucenie go poza mapê
				}
				else
				{
					this->moveShape.setPosition(mpos);
				}
			}
		}
		else
		{
			this->mouseHeld = false;
		}
	}
}

void Player::render(sf::RenderTarget* target)
{
	target->draw(this->playerShape);
	target->draw(this->moveShape);
}