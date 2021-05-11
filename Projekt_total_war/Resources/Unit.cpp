#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include <iostream>
#include "..\Headers\Unit.h"

Unit::Unit()
{
}

//Inicjalizacja jednostki
Unit::Unit(Color color, vector<int> amountOfTroops, sf::Vector2f position)
{
	this->colorOfOwner = color;
	if (amountOfTroops.size() == 0)
	{
		this->knights = 1;
		this->archers = 1;
		this->horses = 1;
	}
	else if (amountOfTroops.size() == 3)
	{
		this->knights = amountOfTroops[0];
		this->archers = amountOfTroops[1];
		this->horses = amountOfTroops[2];
	}
	else
	{
		std::cout << "Error with vector amountOfTroops";
	}
	this->to_delete = false;
	this->distance = 700.f;
	//Atrybuty gracza
	this->moveSpeed = 600;

	this->newUnit = false;

	this->mouseRightHeld = false;
	this->mouseLeftHeld = false;
	this->clicked = false;

	//Obrazek gracza
	this->UnitTexture.loadFromFile("JPG/knight.png");
	this->UnitShape.setTexture(&this->UnitTexture);
	this->UnitShape.setSize(Vector2f(100.f, 100.f));
	this->UnitShape.setOrigin(0.5 * this->UnitShape.getSize().x, 1 * this->UnitShape.getSize().y);
	if (position.x == 0)
	{
		this->UnitShape.setPosition(sf::Vector2f(550.f, 350.f));
	}
	else
	{
		this->UnitShape.setPosition(position);
	}
	this->UnitShapeColor = this->UnitShape.getFillColor();

	//Obrazek poruszania siê
	this->moveTexture.loadFromFile("JPG/x.png");
	this->moveShape.setTexture(&this->moveTexture);
	this->moveShapeColor = this->moveShape.getFillColor();	//Pobranie koloru X-sa
	this->moveShape.setFillColor(sf::Color::Transparent);	//Zabranie mu koloru
	this->moveShape.setPosition(sf::Vector2f(-1000.f, -1000.f));	//Pozycja pocz¹tkowa poza map¹
	this->moveShape.setSize(sf::Vector2f(50.f, 50.f));
	this->moveShape.setOrigin(sf::Vector2f(25.f, 25.f));

	//Przyciski
	this->buttonsFont.loadFromFile("Fonts/RomanSD.ttf");
	this->buttonBackground.setSize(sf::Vector2f(100.f, 100.f));
	this->buttonBackground.setFillColor(sf::Color::Transparent);
	this->buttonBackground.setPosition(-1000.f, -1000.f);
	this->buttonBackground.setOutlineColor(sf::Color::Black);
	this->buttonBackground.setOrigin(0, this->buttonBackground.getSize().y);
	this->buttonSplit.setSize(sf::Vector2f(40.f, 20.f));
	this->buttonSplit.setFillColor(sf::Color::Transparent);
	this->buttonSplit.setPosition(-1000.f, -1000.f);
	this->buttonCancel.setSize(sf::Vector2f(40.f, 20.f));
	this->buttonCancel.setFillColor(sf::Color::Transparent);
	this->buttonCancel.setPosition(-1000.f, -1000.f);
	this->font.loadFromFile("Fonts/RomanSD.ttf");

	{//To trzeba jeszcze dodaæ
		this->buttonBackgroundText.setFont(this->font);
		this->buttonBackgroundText.setFillColor(Color::White);
		this->buttonBackgroundText.setCharacterSize(8);
	}
}

Unit::~Unit()
{
}
/// <summary>Wykorzystuje funkcje z district.h ¿eby sprawdziæ czy kursor znajduje siê nad dystryktem, po klikniêciu prawym przyciskiem myszy pojawia siê X, po czym klikaj¹c w niego pojawia siê tekstura gracza, klikaj¹c dwa razy lewym przyciskiem pojawia siê okno split umo¿liwiaj¹ce rozdzelenie jednostki na dwie.</summary>
/// <param name="">Pozycja kursora | bool Czy kursor nad dystryktem</param>
/// <returns>Void</returns>
void Unit::updateChoosen(sf::Vector2f mpos, bool iCOD, vector <Unit*>& units, vector<City*>& cities)
{
	//Event po klikniêciu na dystrykt prawym przyciskiem
	if (iCOD)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			this->clicked = false;

			if (this->mouseRightHeld == false)
			{
				this->mouseRightHeld = true;
				this->hideButtons();
				if (this->moveShape.getGlobalBounds().contains(mpos))
				{
					int thisone = -1;
					int tojoin = -1;

					if (
						(this->distance -
							sqrt(
								(this->UnitShape.getPosition().x - mpos.x) * (this->UnitShape.getPosition().x - mpos.x)
								+ (this->UnitShape.getPosition().y - mpos.y) * (this->UnitShape.getPosition().y - mpos.y)
							)) > 0
						)
					{
						this->distance -=
							sqrt(
								(this->UnitShape.getPosition().x - mpos.x) * (this->UnitShape.getPosition().x - mpos.x)
								+ (this->UnitShape.getPosition().y - mpos.y) * (this->UnitShape.getPosition().y - mpos.y)
							);

						for (int i = 0; i < units.size(); i++)
						{
							//dodawanie jednostek tylko gdy s¹ tego samego gracza w innym przypadku walka
							if (units[i]->UnitShape.getGlobalBounds().contains(mpos) && units[i]->UnitShape.getGlobalBounds().contains(mpos) != this->UnitShape.getGlobalBounds().contains(mpos) && this->colorOfOwner == units[i]->colorOfOwner)
							{
								units[i]->archers += this->archers;
								units[i]->knights += this->knights;
								units[i]->horses += this->horses;
								this->to_delete = true;
								this->nextUnit = i;
							}
							else if (units[i]->UnitShape.getGlobalBounds().contains(mpos) && units[i]->UnitShape.getGlobalBounds().contains(mpos) != this->UnitShape.getGlobalBounds().contains(mpos) && this->colorOfOwner != units[i]->colorOfOwner)
							{
								cout << "walka!!!";
								this->fight(units[i]);
							}
						}
						for (int i = 0; i < cities.size(); i++)
						{	//Dodawanie z jednostki do miasta bior¹c pod uwagê limity, w innym przypadku atak miasta
							if (cities[i]->cityIcon.getGlobalBounds().contains(mpos) && this->colorOfOwner == cities[i]->colorOfOwner)

							{
								if (cities[i]->archers < cities[i]->archersMax)
								{
									while (cities[i]->archers != cities[i]->archersMax && this->archers != 0)
									{
										cities[i]->archers++;
										this->archers--;
									}
								}

								if (cities[i]->knights < cities[i]->knightsMax)
								{
									while (cities[i]->knights != cities[i]->knightsMax && this->knights != 0)
									{
										cities[i]->knights++;
										this->knights--;
									}
								}

								if (cities[i]->horses < cities[i]->horsesMax)
								{
									while (cities[i]->horses != cities[i]->horsesMax && this->horses != 0)
									{
										cities[i]->horses++;
										this->horses--;
									}
								}

								if (this->archers == 0 && this->knights == 0 && this->horses == 0)//je¿eli oddzia³ jest pusty to go usuwamy
								{
									this->to_delete = true;
								}
							}
							else if (cities[i]->cityIcon.getGlobalBounds().contains(mpos) && this->colorOfOwner != cities[i]->colorOfOwner)
							{
								this->cityAttack(cities[i]);
							}
						}

						this->UnitShape.setPosition(mpos);	//mpos czy pozycja moveShape???
					}
					this->moveShape.setFillColor(sf::Color::Transparent); //X znika
					this->moveShape.setPosition(sf::Vector2f(-100.f, -100.f)); //Wyrzucenie X-sa poza mapê aby nie da³o siê go klikn¹æ ponownie
					this->clicked = false;
				}
				else
				{
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
				if (this->clickClock.getElapsedTime() <= sf::milliseconds(600.f))
				{
					std::cout << "Kliknales go lewym mordo\n";

					this->clicked = true;
					this->UnitShape.setFillColor(sf::Color::Red);
					this->showButtons();
				}
				else
				{
					clickClock.restart();
				}
			}

			if (this->drawButton)
			{
				if (this->buttonCancel.getGlobalBounds().contains(mpos))
				{
					this->hideButtons();
					this->clicked = false;
				}
				else if (this->buttonSplit.getGlobalBounds().contains(mpos))
				{
					this->hideButtons();
					this->newUnit = true;
					this->clicked = false;
				}
				else if (!this->buttonBackground.getGlobalBounds().contains(mpos) && !this->UnitShape.getGlobalBounds().contains(mpos))
				{
					this->hideButtons();
					this->clicked = false;
				}
			}
		}
	}
	else
	{
		this->mouseLeftHeld = false;
	}
}

//Podœwietla jednostkê po najechaniu
void Unit::updateAll(sf::Vector2f mpos, bool iCOD)
{
	//Podœwietlenie jednostki po najechaniu lub podwójnym klikniêciu
	if (!this->clicked)
		this->UnitShape.setFillColor(this->UnitShapeColor);
	if (this->UnitShape.getGlobalBounds().contains(mpos))
	{
		//this->UnitShape.setFillColor(this->colorOfOwner); podœwietlanie aby sprawdziæ czy ten oddzia³ nale¿y do gracza
		this->UnitShape.setFillColor(Color::Red);
	}
}

void Unit::render(sf::RenderTarget* target)
{
	target->draw(this->UnitShape);
	target->draw(this->moveShape);
	if (this->drawButton)
	{
		target->draw(this->buttonBackground);
		target->draw(this->buttonBackgroundText);
		target->draw(this->buttonSplit);
		target->draw(this->buttonCancel);
	}
}

bool Unit::ifNewUnit()
{
	if (this->newUnit)
	{
		this->newUnit = false;
		this->drawButton = false;
		return true;
	}
	else return false;
}

void Unit::showButtons()
{
	this->drawButton = true;
	this->buttonBackground.setFillColor(sf::Color(127, 127, 127, 127));
	this->buttonBackground.setPosition(sf::Vector2f(this->UnitShape.getPosition().x + (this->UnitShape.getSize().x / 2), this->UnitShape.getPosition().y));

	this->buttonCancel.setFillColor(sf::Color::Black);
	this->buttonCancel.setPosition(sf::Vector2f(this->buttonBackground.getPosition().x + 5, this->buttonBackground.getPosition().y - 25));

	this->buttonSplit.setFillColor(sf::Color::Black);
	this->buttonSplit.setPosition(sf::Vector2f(this->buttonBackground.getPosition().x + 55, this->buttonBackground.getPosition().y - 25));
	stringstream ss;
	ss << "Licznosc jednostki\n\n" << "Rycerze: " << this->knights << "\nKonni: " << this->horses << "\nLucznicy: " << this->archers;
	this->buttonBackgroundText.setString(ss.str());
	this->buttonBackgroundText.setPosition(this->buttonBackground.getPosition().x + (this->buttonBackground.getGlobalBounds().width / 2) - this->buttonBackgroundText.getGlobalBounds().width / 2, this->buttonBackground.getPosition().y - 100);
}

void Unit::hideButtons()
{
	this->drawButton = false;
	this->buttonBackground.setFillColor(sf::Color::Transparent);
	this->buttonBackground.setPosition(sf::Vector2f(-100.f, -100.f));

	this->buttonCancel.setFillColor(sf::Color::Transparent);
	this->buttonCancel.setPosition(sf::Vector2f(-100.f, -100.f));

	this->buttonSplit.setFillColor(sf::Color::Transparent);
	this->buttonSplit.setPosition(sf::Vector2f(-100.f, -100.f));

	if (!this->mouseRightHeld) {
		this->moveShape.setFillColor(sf::Color::Transparent);
		this->moveShape.setPosition(sf::Vector2f(-100.f, -100.f));
	}
}

//Ustawianie mo¿liwoœci do przejœcia
void Unit::setDistance()
{
	this->distance = 600.f;
}
//Walka dwóch oddzia³ów
void Unit::fight(Unit* enemyUnit)
{
}
//atakowanie miasta
void Unit::cityAttack(City* city)
{
}

//Poruszanie jednostkami Ai
void Unit::updateAiUnits()
{
	this->UnitShape.move(100.f, 100.f);
}