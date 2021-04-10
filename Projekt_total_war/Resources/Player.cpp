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
void Player::initPla(sf::Color color, sf::Vector2f vec, map<string, District*> districts)
{
	this->playerShape.setFillColor(color);
	this->playerShape.setSize(vec);
	this->playerShape.setOrigin(0.5 * vec.x, 0.5 * vec.y);
	this->playerShape.setPosition(districts["Calabria"]->returnPosition());
	this->mouseHeld = false;
	this->moveShape.setSize(sf::Vector2f(50.f, 50.f));
	this->moveShape.setOrigin(sf::Vector2f(25.f, 25.f));
	this->moveShape.setFillColor(sf::Color::Blue);
}

// TODO:

/// <summary>Wykorzystuje funkcje z district.h �eby sprawdzi� czy kursor znajduje si� nad dystryktem, po klikni�ciu prawym przyciskiem myszy pojawia si� niebieski kwadrat a po klikni�ciu w ten kwadrat pojawia si� czerwony kwadrat(gracz).</summary>
/// <param name="">Pozycja kursora | Wska�nik na dystrykt</param>
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
					this->playerShape.setPosition(mpos);	//mpos czy pozycja moveShpae???
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