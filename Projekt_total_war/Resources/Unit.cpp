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

	//Obrazek poruszania si�
	this->moveTexture.loadFromFile("JPG/x.png");
	this->moveShape.setTexture(&this->moveTexture);
	this->moveShapeColor = this->moveShape.getFillColor();	//Pobranie koloru X-sa
	this->moveShape.setFillColor(sf::Color::Transparent);	//Zabranie mu koloru
	this->moveShape.setPosition(sf::Vector2f(-100.f, -100.f));	//Pozycja pocz�tkowa poza map�
	this->moveShape.setSize(sf::Vector2f(50.f, 50.f));
	this->moveShape.setOrigin(sf::Vector2f(25.f, 25.f));

	//Atrybuty gracza
	this->moveSpeed = 600;
}

/// <summary>Wykorzystuje funkcje z district.h �eby sprawdzi� czy kursor znajduje si� nad dystryktem, po klikni�ciu prawym przyciskiem myszy pojawia si� X, po czym klikaj�c w niego pojawia si� tekstura gracza.</summary>
/// <param name="">Pozycja kursora | Wska�nik na dystrykt</param>
/// <returns>Void</returns>
void Unit::update(sf::Vector2f mpos, District* districts)
{
	//Event po klikni�ciu na dystrykt prawym przyciskiem
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
					this->moveShape.setPosition(sf::Vector2f(-100.f, -100.f)); //Wyrzucenie X-sa poza map� aby nie da�o si� go klikn�� ponownie
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

	//Event po klikni�ciu jednostki lewym przyciskiem
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