#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include <iostream>
#include "..\Headers\City.h"
//Konstruktor i destruktor
City::City(std::string name, int popMax, sf::Vector2f cityPoints, Color color)
{
	this->cityName = name;
	this->populationMax = popMax;
	this->population = rand() % popMax + 1;
	this->cityPos = cityPoints;
	this->knights = 0;
	this->archers = 0;
	this->horses = 0;
	this->knightsMax = 4;
	this->archersMax = 4;
	this->horsesMax = 0;
	this->colorOfOwner = color;
	this->deployUnits = false;
}

City::~City()
{
}

void City::initCity(sf::Vector2f cityPos)
{
	this->cityIconTexture.loadFromFile("JPG/city.png");
	this->cityIcon.setTexture(&this->cityIconTexture);
	this->cityIconColor = this->cityIcon.getFillColor();
	this->cityIcon.setSize(Vector2f(60.f, 60.f));
	this->cityIcon.setOrigin(0.5 * this->cityIcon.getSize().x, 0.5 * this->cityIcon.getSize().y);	 //ustawianie wgl�dem jakiego punktu kszta�tu ma by� ustawiana pozycja
	this->cityIcon.setPosition(cityPos);

	this->mouseHeld = false;
	this->doubleClicked = false;
}

//Zwraca czy klikni�to dwa razy w miasto
bool City::isInCity()
{
	return this->doubleClicked;
}

//Zmienia stan na nie w mie�cie
void City::setNotInCity()
{
	this->doubleClicked = false;
}

bool City::isUnitsDeployed()
{
	if (this->deployUnits) {
		this->deployUnits = false;
		return true;
	}
	return false;
}

sf::Vector2f City::getPosition()
{
	return this->cityIcon.getPosition();
}

vector<int> City::howManyUnits()
{
	return vector<int> { this->knights, this->archers, this->horses };
}

void City::deleteTroops()
{
	this->knights = 0;
	this->archers = 0;
	this->horses = 0;
}

/// <summary>Wykorzystuje funkcje z district.h �eby sprawdzi� czy kursor znajduje si� nad miastem, po najechaniu zmienia si� kolor miasta na czerwony, a po podw�jnym klikni�ciu TODO: ma pojawia� si� menu miasta</summary>
/// <param name="">Pozycja kursora</param>
/// <returns>Void</returns>
void City::update(Vector2f mpos)
{
	this->cityIcon.setFillColor(cityIconColor);

	if (this->cityIcon.getGlobalBounds().contains(mpos))
	{
		this->cityIcon.setFillColor(sf::Color::Red);

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (this->mouseHeld == false)
			{
				this->mouseHeld = true;

				//Sprawdzenie czy nie min�o za du�o czasu od 1 klikni�cia na miasto
				if (this->clickClock.getElapsedTime() <= sf::milliseconds(600.f))
				{
					std::cout << "Double click \n";

					this->doubleClicked = true;
				}
				else
				{
					std::cout << "Witamy w miescie " << this->cityName << "\n";
					std::cout << "Single click\n";
					this->clickClock.restart();	//Zrestartowanie zegara (start zegara)
				}
			}
		}
		else
		{
			this->mouseHeld = false;
		}
	}
}

void City::render(RenderTarget* target)
{
	target->draw(this->cityIcon);
}

//Zmiany w populacji
void City::updatePopulation()
{
	int randBorn = rand() % 100;
	int randDied = rand() % 100;
	if ((this->population -= randBorn) < 0)
		this->population = 0;
	if ((this->population -= randBorn) >= this->populationMax)
		this->population = this->populationMax;
}