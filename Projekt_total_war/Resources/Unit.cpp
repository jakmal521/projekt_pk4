#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include <iostream>
#include "..\Headers\Unit.h"

Unit::Unit()
{
}

Unit::~Unit()
{
}

//Inicjalizacja gracza
void Unit::initUnit(map<string, District*> districts)
{
	this->newUnit = false;

	this->mouseRightHeld = false;
	this->mouseLeftHeld = false;

	//Obrazek gracza
	this->UnitTexture.loadFromFile("JPG/knight.png");
	this->UnitShape.setTexture(&this->UnitTexture);
	this->UnitShape.setSize(Vector2f(100.f, 100.f));
	this->UnitShape.setOrigin(0.5 * this->UnitShape.getSize().x, 1 * this->UnitShape.getSize().y);
	this->UnitShape.setPosition(districts["Calabria"]->returnPosition());

	//Obrazek poruszania siê
	this->moveTexture.loadFromFile("JPG/x.png");
	this->moveShape.setTexture(&this->moveTexture);
	this->moveShapeColor = this->moveShape.getFillColor();	//Pobranie koloru X-sa
	this->moveShape.setFillColor(sf::Color::Transparent);	//Zabranie mu koloru
	this->moveShape.setPosition(sf::Vector2f(-100.f, -100.f));	//Pozycja pocz¹tkowa poza map¹
	this->moveShape.setSize(sf::Vector2f(50.f, 50.f));
	this->moveShape.setOrigin(sf::Vector2f(25.f, 25.f));

	//Atrybuty gracza
	this->moveSpeed = 600;
}

/// <summary>Wykorzystuje funkcje z district.h ¿eby sprawdziæ czy kursor znajduje siê nad dystryktem, po klikniêciu prawym przyciskiem myszy pojawia siê X, po czym klikaj¹c w niego pojawia siê tekstura gracza.</summary>
/// <param name="">Pozycja kursora | WskaŸnik na dystrykt</param>
/// <returns>Void</returns>
void Unit::update(sf::Vector2f mpos, District* districts)
{
	//Event po klikniêciu na dystrykt prawym przyciskiem
	if (districts->returnIsCursorOnDistrict())
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			if (this->mouseRightHeld == false)
			{
				this->mouseRightHeld = true;
				if (this->moveShape.getGlobalBounds().contains(mpos))
				{
					std::cout << "Kurwy dotarly na " << districts->name << "\n";
					this->UnitShape.setPosition(mpos);	//mpos czy pozycja moveShape???
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
			this->mouseRightHeld = false;
		}
	}

	//Event po klikniêciu jednostki lewym przyciskiem
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (this->mouseLeftHeld == false)
		{
			this->mouseLeftHeld = true;
			if (this->UnitShape.getGlobalBounds().contains(mpos))
			{
				std::cout << "Kliknales go lewym mordo\n";
				newUnit = true;
			}
		}
	}
	else
	{
		this->mouseLeftHeld = false;
	}
}

void Unit::render(sf::RenderTarget* target)
{
	target->draw(this->UnitShape);
	target->draw(this->moveShape);
}

bool Unit::ifNewUnit()
{
	if (this->newUnit)
	{
		this->newUnit = false;
		return true;
	}
}