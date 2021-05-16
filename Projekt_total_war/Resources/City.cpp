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
	this->colorOfOwner = color;
	this->deployUnits = false;
	this->toUpdate = 0;
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
	this->cityIcon.setOrigin(0.5 * this->cityIcon.getSize().x, 0.5 * this->cityIcon.getSize().y);	 //ustawianie wglêdem jakiego punktu kszta³tu ma byæ ustawiana pozycja
	this->cityIcon.setPosition(cityPos);

	this->mouseHeld = false;
	this->doubleClicked = false;
}

//Zwraca czy klikniêto dwa razy w miasto
bool City::isInCity()
{
	return this->doubleClicked;
}

//Zmienia stan na nie w mieœcie
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

bool City::isToUpdate()
{
	if (this->toUpdate) {
		this->toUpdate = false;
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

void City::setTroops(int k, int h, int a)
{
	this->knights += k;
	this->horses += h;
	this->archers += a;
}

void City::deleteTroops()
{
	this->knights = 0;
	this->archers = 0;
	this->horses = 0;
}

/// <summary>Wykorzystuje funkcje z district.h ¿eby sprawdziæ czy kursor znajduje siê nad miastem, po najechaniu zmienia siê kolor miasta na czerwony, a po podwójnym klikniêciu TODO: ma pojawiaæ siê menu miasta</summary>
/// <param name="">Pozycja kursora</param>
/// <returns>Void</returns>
void City::update(Vector2f mpos)
{
	this->cityIcon.setFillColor(cityIconColor);

	if (this->cityIcon.getGlobalBounds().contains(mpos) /*&& this->colorOfOwner == sf::Color::Red*/)
	{

		this->cityIcon.setFillColor(sf::Color::Red);

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (this->mouseHeld == false)
			{
				this->mouseHeld = true;

				//Sprawdzenie czy nie minê³o za du¿o czasu od 1 klikniêcia na miasto
				if (this->clickClock.getElapsedTime() <= sf::milliseconds(600.f))
				{
				

					this->doubleClicked = true;
				}
				else
				{
					
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