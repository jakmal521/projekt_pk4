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
	this->moveShapeColor = this->moveShape.getFillColor(); //Pobranie koloru X-sa
	this->moveShape.setPosition(sf::Vector2f(-100.f, -100.f));
	this->moveShape.setSize(sf::Vector2f(50.f, 50.f));
	this->moveShape.setOrigin(sf::Vector2f(25.f, 25.f));
	//Atrybuty gracza
	this->moveSpeed = 600;
}

/// <summary>Wykorzystuje funkcje z district.h ¿eby sprawdziæ czy kursor znajduje siê nad dystryktem, po klikniêciu prawym przyciskiem myszy pojawia siê X, po czym klikaj¹c w niego pojawia siê tekstura gracza.</summary>
/// <param name="">Pozycja kursora | WskaŸnik na dystrykt</param>
/// <returns>Void</returns>
void Player::update(sf::Vector2f mpos, District* districts)
{
	if (districts->returnIsCursorOnDistrict())
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			if (this->mouseHeld == false)
			{
				this->mouseHeld = true;
				if (this->moveShape.getGlobalBounds().contains(mpos))
				{
					std::cout << "Kurwy dotarly na " << districts->name << "\n";
					this->playerShape.setPosition(mpos);	//mpos czy pozycja moveShape???
					this->moveShape.setFillColor(sf::Color::Transparent); //X znika
					this->moveShape.setPosition(sf::Vector2f(-100.f, -100.f)); //Wyrzucenie X-sa poza mapê aby nie da³o siê go klikn¹æ ponownie
				}
				else
				{
					std::cout << "Ruszam z kurwami na " << districts->name << "\n";
					this->moveShape.setPosition(mpos);
					this->moveShape.setFillColor(moveShapeColor);
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