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
	//Atrybuty jednostki
	this->colorOfOwner = color;
	this->distance = 200.f;
	if (amountOfTroops.size() == 0)
	{
		this->knights = 1;
		this->archers = 1;
		this->horses = 1;
	}
	else if (amountOfTroops.size() == 3)
	{
		this->knights = amountOfTroops[0];
		this->archers = amountOfTroops[2];
		this->horses = amountOfTroops[1];
	}
	else
	{
		std::cout << "Error with vector amountOfTroops";
	}

	//Mechanika gry dla jednostki
	this->to_delete = false;
	this->newUnit = false;
	this->clicked = false;
	this->mouseRightHeld = false;
	this->mouseLeftHeld = false;

	//Obrazek jednostki
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

	//Przyciski dla info o jednostce
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

	//Tekst dla info o jednostce, w tym zamknij i podziel
	this->buttonBackgroundText.setFont(this->font);
	this->buttonBackgroundText.setFillColor(Color::White);
	this->buttonBackgroundText.setCharacterSize(8);

	this->cancel.setFont(this->font);
	this->cancel.setFillColor(Color::Transparent);
	this->cancel.setCharacterSize(8);
	this->cancel.setString("Zamknij");

	this->split.setFont(this->font);
	this->split.setFillColor(Color::Transparent);
	this->split.setCharacterSize(8);
	this->split.setString("Dziel");
}

Unit::~Unit()
{
}
/// <summary>Wykorzystuje funkcje z district.h ¿eby sprawdziæ czy kursor znajduje siê nad dystryktem, po klikniêciu prawym przyciskiem myszy pojawia siê X, po czym klikaj¹c w niego pojawia siê tekstura gracza, klikaj¹c dwa razy lewym przyciskiem pojawia siê okno split umo¿liwiaj¹ce rozdzelenie jednostki na dwie.</summary>
/// <param name="">Pozycja kursora | bool Czy kursor nad dystryktem</param>
/// <returns>Void</returns>
void Unit::updateChoosen(sf::Vector2f mpos, bool iCOD, vector <Unit*>& units, vector<City*>& cities, vector<pair<Enemy*, vector<Unit*>>> enemies)
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
						}
						for (int j = 0; j < enemies.size(); j++)
						{
							for (int k = 0; k < enemies[j].second.size(); k++)
							{
								if (enemies[j].second[k]->UnitShape.getGlobalBounds().contains(mpos) && enemies[j].first->playerColor() != this->colorOfOwner)
								{
									this->fight(*enemies[j].second[k]);
								}
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
								this->cityAttack(*cities[i]);
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
		target->draw(this->cancel);
		target->draw(this->split);
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

	this->cancel.setFillColor(sf::Color::White);
	this->cancel.setPosition(this->buttonCancel.getPosition().x + (this->buttonCancel.getGlobalBounds().width / 2) - this->cancel.getGlobalBounds().width / 2, this->buttonCancel.getPosition().y + (this->buttonCancel.getGlobalBounds().height / 2) - this->cancel.getGlobalBounds().height / 2);

	this->split.setFillColor(sf::Color::White);
	this->split.setPosition(this->buttonSplit.getPosition().x + (this->buttonSplit.getGlobalBounds().width / 2) - this->split.getGlobalBounds().width / 2, this->buttonSplit.getPosition().y + (this->buttonSplit.getGlobalBounds().height / 2) - this->split.getGlobalBounds().height / 2);
}

void Unit::hideButtons()
{
	this->drawButton = false;
	this->buttonBackground.setFillColor(sf::Color::Transparent);
	this->buttonBackground.setPosition(sf::Vector2f(-1000.f, -1000.f));

	this->buttonCancel.setFillColor(sf::Color::Transparent);
	this->buttonCancel.setPosition(sf::Vector2f(-1000.f, -1000.f));

	this->buttonSplit.setFillColor(sf::Color::Transparent);
	this->buttonSplit.setPosition(sf::Vector2f(-1000.f, -1000.f));

	this->split.setFillColor(sf::Color::Transparent);
	this->split.setPosition(sf::Vector2f(-1000.f, -1000.f));

	this->cancel.setFillColor(sf::Color::Transparent);
	this->split.setPosition(sf::Vector2f(-1000.f, -1000.f));

	if (!this->mouseRightHeld) {
		this->moveShape.setFillColor(sf::Color::Transparent);
		this->moveShape.setPosition(sf::Vector2f(-1000.f, -1000.f));
	}
}

//Ustawianie mo¿liwoœci do przejœcia
void Unit::setDistance()
{
	this->distance = 200.f;
}
//Walka dwóch oddzia³ów
void Unit::fight(Unit& enemyUnit)
{
	float attackChance = 3 * this->archers + 5 * this->knights + 10 * this->horses;
	float defenceChance = 3 * enemyUnit.archers + 5 * enemyUnit.knights + 10 * enemyUnit.horses;
	float chanceToDefend = (defenceChance / attackChance) * 100;

	if (chanceToDefend > 500)
	{
		this->to_delete = true;
	}
	else
	{
		if (rand() % 500 + 1 > chanceToDefend)
		{
			if (this->knights)
			{
				this->knights -= rand() % this->knights;
			}
			if (this->archers)
			{
				this->archers -= rand() % this->archers;
			}
			if (this->horses)
			{
				this->horses -= rand() % this->horses;
			}
			enemyUnit.to_delete = true;
		}
		else
		{
			if (enemyUnit.knights)
			{
				enemyUnit.knights -= rand() % enemyUnit.knights;
			}
			if (enemyUnit.archers)
			{
				enemyUnit.archers -= rand() % enemyUnit.archers;
			}
			if (enemyUnit.horses)
			{
				enemyUnit.horses -= rand() % enemyUnit.horses;
			}
			this->to_delete = true;
		}
	}
}

//atakowanie miasta
void Unit::cityAttack(City& city)
{
	if (!city.archers && !city.knights && !city.horses)
	{
		city.colorOfOwner = this->colorOfOwner;
		return;
	}
	float cityChance = 10 * city.archers + 5 * city.knights + 5 * city.horses;
	float unitChance = 8 * this->archers + 4 * this->knights + 2 * this->horses;

	float chanceToSaveCity = (cityChance / unitChance) * 100;

	if (chanceToSaveCity > 500)
	{
		this->to_delete = true;
	}
	else
	{
		if (rand() % 500 + 1 > chanceToSaveCity)
		{
			city.colorOfOwner = this->colorOfOwner;
			city.archers = 0;
			city.knights = 0;
			city.horses = 0;
			if (this->knights)
			{
				this->knights -= rand() % this->knights;
			}
			if (this->archers)
			{
				this->archers -= rand() % this->archers;
			}
			if (this->horses)
			{
				this->horses -= rand() % this->horses;
			}
		}
		else
		{
			if (city.knights)
			{
				city.knights -= rand() % city.knights;
			}
			if (city.archers)
			{
				city.archers -= rand() % city.archers;
			}
			if (city.horses)
			{
				city.horses -= rand() % city.horses;
			}
			this->to_delete = true;
		}
	}
}

//Poruszanie jednostkami Ai
void Unit::updateAiUnits(int turn, vector <Unit*>* units, map<string, District*>* districts, vector<pair<Enemy*, vector<Unit*>>>* enemies, int whichEnemyIsChoosen, int once)
{
	for (auto& i : *districts)
	{
		if (i.second->cities.back()->colorOfOwner == enemies->at(whichEnemyIsChoosen).first->playerColor())
		{
			if (turn)
			{
				int ran = rand() % 100 + 1;
				if (ran > 85 && i.second->sizeOfCity == 1 && enemies->at(whichEnemyIsChoosen).first->getGold() > 25000)
				{
					//cout << "Ulepszylem miasto " << i.second->cities.back()->cityName << " rozmiar: " << i.second->sizeOfCity << "\n";
					enemies->at(whichEnemyIsChoosen).first->setGold(enemies->at(whichEnemyIsChoosen).first->getGold() - 25000);
					i.second->cities.back()->toUpdate = 1;
				}
				else if (ran > 99 && i.second->sizeOfCity == 2 && enemies->at(whichEnemyIsChoosen).first->getGold() > 100000)
				{
					//cout << "Ulepszylem miasto " << i.second->cities.back()->cityName << " rozmiar: " << i.second->sizeOfCity << "\n";
					enemies->at(whichEnemyIsChoosen).first->setGold(enemies->at(whichEnemyIsChoosen).first->getGold() - 100000);
					i.second->cities.back()->toUpdate = 1;
				}
				else if (ran)
				{
					int a = i.second->cities.back()->knightsMax - i.second->cities.back()->knights;
					if (a)
					{
						int ran = rand() % 5 + 1;
						if (enemies->at(whichEnemyIsChoosen).first->getGold() > 20000 && ran <= a)
						{
							//cout << "Dodalem " << ran << " rycerzy do miasta " << i.second->cities.back()->cityName << "\n";
							i.second->cities.back()->cityIcon.setFillColor(Color::Blue);
							switch (ran)
							{
							case 1:
								enemies->at(whichEnemyIsChoosen).first->setGold(enemies->at(whichEnemyIsChoosen).first->getGold() - ran * 400);
								i.second->cities.back()->setTroops(1, 0, 0);
								break;
							case 2:
								enemies->at(whichEnemyIsChoosen).first->setGold(enemies->at(whichEnemyIsChoosen).first->getGold() - ran * 400);
								i.second->cities.back()->setTroops(2, 0, 0);
								break;
							case 3:
								enemies->at(whichEnemyIsChoosen).first->setGold(enemies->at(whichEnemyIsChoosen).first->getGold() - ran * 400);
								i.second->cities.back()->setTroops(3, 0, 0);
								break;
							case 4:
								enemies->at(whichEnemyIsChoosen).first->setGold(enemies->at(whichEnemyIsChoosen).first->getGold() - ran * 400);
								i.second->cities.back()->setTroops(4, 0, 0);
								break;
							case 5:
								enemies->at(whichEnemyIsChoosen).first->setGold(enemies->at(whichEnemyIsChoosen).first->getGold() - ran * 400);
								i.second->cities.back()->setTroops(5, 0, 0);
								break;

							default:
								break;
							}
						}
					}
					a = i.second->cities.back()->horsesMax - i.second->cities.back()->horses;
					if (a)
					{
						int ran = rand() % 5 + 1;
						if (enemies->at(whichEnemyIsChoosen).first->getGold() > 20000 && ran <= a)
						{
							switch (ran)
							{
							case 1:
								enemies->at(whichEnemyIsChoosen).first->setGold(enemies->at(whichEnemyIsChoosen).first->getGold() - ran * 500);
								i.second->cities.back()->setTroops(0, 1, 0);
								break;
							case 2:
								enemies->at(whichEnemyIsChoosen).first->setGold(enemies->at(whichEnemyIsChoosen).first->getGold() - ran * 500);
								i.second->cities.back()->setTroops(0, 2, 0);
								break;
							case 3:
								enemies->at(whichEnemyIsChoosen).first->setGold(enemies->at(whichEnemyIsChoosen).first->getGold() - ran * 500);
								i.second->cities.back()->setTroops(0, 3, 0);
								break;
							case 4:
								enemies->at(whichEnemyIsChoosen).first->setGold(enemies->at(whichEnemyIsChoosen).first->getGold() - ran * 500);
								i.second->cities.back()->setTroops(0, 4, 0);
								break;
							case 5:
								enemies->at(whichEnemyIsChoosen).first->setGold(enemies->at(whichEnemyIsChoosen).first->getGold() - ran * 500);
								i.second->cities.back()->setTroops(0, 5, 0);
								break;

							default:
								break;
							}
						}
					}
					a = i.second->cities.back()->archersMax - i.second->cities.back()->archers;
					if (a)
					{
						int ran = rand() % 5 + 1;
						if (enemies->at(whichEnemyIsChoosen).first->getGold() > 20000 && ran <= a)
						{
							switch (ran)
							{
							case 1:
								enemies->at(whichEnemyIsChoosen).first->setGold(enemies->at(whichEnemyIsChoosen).first->getGold() - ran * 300);
								i.second->cities.back()->setTroops(0, 0, 1);
								break;
							case 2:
								enemies->at(whichEnemyIsChoosen).first->setGold(enemies->at(whichEnemyIsChoosen).first->getGold() - ran * 300);
								i.second->cities.back()->setTroops(0, 0, 2);
								break;
							case 3:
								enemies->at(whichEnemyIsChoosen).first->setGold(enemies->at(whichEnemyIsChoosen).first->getGold() - ran * 300);
								i.second->cities.back()->setTroops(0, 0, 3);
								break;
							case 4:
								enemies->at(whichEnemyIsChoosen).first->setGold(enemies->at(whichEnemyIsChoosen).first->getGold() - ran * 300);
								i.second->cities.back()->setTroops(0, 0, 4);
								break;
							case 5:
								enemies->at(whichEnemyIsChoosen).first->setGold(enemies->at(whichEnemyIsChoosen).first->getGold() - ran * 300);
								i.second->cities.back()->setTroops(0, 0, 5);
								break;

							default:
								break;
							}
						}
					}
				}
			}
			if (turn > 5)
			{
				if (i.second->cities.back()->knights > 20)
				{
					i.second->cities.back()->deployUnits = true;
				}
			}
		}
	}
	if (turn)
	{
		for (int i = enemies->at(whichEnemyIsChoosen).second.size() - 1; i > 0; i--)
		{
			float a1 = enemies->at(whichEnemyIsChoosen).second[i]->UnitShape.getPosition().x;
			float a2 = enemies->at(whichEnemyIsChoosen).second[i - 1]->UnitShape.getPosition().x;
			float x = -(a1 - a2);

			a1 = enemies->at(whichEnemyIsChoosen).second[i]->UnitShape.getPosition().y;
			a2 = enemies->at(whichEnemyIsChoosen).second[i - 1]->UnitShape.getPosition().y;
			float y = -(a1 - a2);

			this->distance = sqrt((x * x) + (y * y));

			float dad = this->distance;

			if (dad > 19.7)
			{
				if (x >= 14 && y >= 14)
				{
					enemies->at(whichEnemyIsChoosen).second[i]->UnitShape.move(14, 14);
				}
				else if (x <= -14 && y <= -14)
				{
					enemies->at(whichEnemyIsChoosen).second[i]->UnitShape.move(-14, -14);
				}
				else if (x >= 14 && y <= -14)
				{
					enemies->at(whichEnemyIsChoosen).second[i]->UnitShape.move(14, -14);
				}
				else if (x <= -14 && y >= 14)
				{
					enemies->at(whichEnemyIsChoosen).second[i]->UnitShape.move(-14, 14);
				}
				else if (x >= 14 && ((y >= 0 && y <= 14) || (y <= 0 && y >= -14)))
				{
					enemies->at(whichEnemyIsChoosen).second[i]->UnitShape.move(14, y);
				}
				else if (x <= -14 && ((y >= 0 && y <= 14) || (y <= 0 && y >= -14)))
				{
					enemies->at(whichEnemyIsChoosen).second[i]->UnitShape.move(-14, y);
				}
				else if (y >= 14 && ((x >= 0 && x <= 14) || (x <= 0 && x >= -14)))
				{
					enemies->at(whichEnemyIsChoosen).second[i]->UnitShape.move(x, 14);
				}
				else if (y <= -14 && ((x >= 0 && x <= 14) || (x <= 0 && x >= -14)))
				{
					enemies->at(whichEnemyIsChoosen).second[i]->UnitShape.move(x, -14);
				}
				else
				{
					cout << "Cos nie tak w przemieszczaniu sie AI-I po mapie (Unit.cpp -> updateAiUnits())\n";
				}
			}
			else
			{
				enemies->at(whichEnemyIsChoosen).second[i - 1]->archers += enemies->at(whichEnemyIsChoosen).second[i]->archers;
				enemies->at(whichEnemyIsChoosen).second[i - 1]->knights += enemies->at(whichEnemyIsChoosen).second[i]->knights;
				enemies->at(whichEnemyIsChoosen).second[i - 1]->horses += enemies->at(whichEnemyIsChoosen).second[i]->horses;
				enemies->at(whichEnemyIsChoosen).second.erase(enemies->at(whichEnemyIsChoosen).second.begin() + i);
			}
		}
		if (turn > 7 && once == 0)
		{
			bool enemyOnMap = false;
			bool enemyCloser = false;

			float xEnemy, yEnemy;
			float distanceEnemy = numeric_limits<float>::max();

			//Sprawdzenie czy s¹ wrogie jednostki na mapie (aby nie powsta³ b³¹d przy szukaniu pozycji nabli¿szej wrogiej jednostki)
			for (auto& i : *units)
			{
				if (i->colorOfOwner != this->colorOfOwner)
				{
					enemyOnMap = true;
					break;
				}
			}

			//Liczenie X-sa
			float a1 = enemies->at(whichEnemyIsChoosen).second[0]->UnitShape.getPosition().x;
			if (enemyOnMap)
			{
				float a2 = closestEnemyUnit(enemies->at(whichEnemyIsChoosen).second[0], *units, *enemies)->UnitShape.getPosition().x;
				xEnemy = -(a1 - a2);
			}
			float a3 = closestEnemyCity(*districts, enemies->at(whichEnemyIsChoosen).second[0])->cities.back()->getPosition().x;
			float xCity = -(a1 - a3);

			//Liczenie Y-ka
			a1 = enemies->at(whichEnemyIsChoosen).second[0]->UnitShape.getPosition().y;
			if (enemyOnMap)
			{
				float a2 = closestEnemyUnit(enemies->at(whichEnemyIsChoosen).second[0], *units, *enemies)->UnitShape.getPosition().y;
				yEnemy = -(a1 - a2);
			}
			a3 = closestEnemyCity(*districts, enemies->at(whichEnemyIsChoosen).second[0])->cities.back()->getPosition().y;
			float yCity = -(a1 - a3);

			if (enemyOnMap)
			{
				distanceEnemy = sqrt((xEnemy * xEnemy) + (yEnemy * yEnemy));
			}
			float distanceCity = sqrt((xCity * xCity) + (yCity * yCity));

			this->distance = min(distanceCity, distanceEnemy);
			float x = xCity;
			float y = yCity;

			if (this->distance == distanceEnemy)
			{
				enemyCloser = true;
				x = xEnemy;
				y = yEnemy;
			}

			float d = this->distance;

			if (d > 19.7)
			{
				if (x >= 14 && y >= 14)
				{
					enemies->at(whichEnemyIsChoosen).second[0]->UnitShape.move(14, 14);
				}
				else if (x <= -14 && y <= -14)
				{
					enemies->at(whichEnemyIsChoosen).second[0]->UnitShape.move(-14, -14);
				}
				else if (x >= 14 && y <= -14)
				{
					enemies->at(whichEnemyIsChoosen).second[0]->UnitShape.move(14, -14);
				}
				else if (x <= -14 && y >= 14)
				{
					enemies->at(whichEnemyIsChoosen).second[0]->UnitShape.move(-14, 14);
				}
				else if (x >= 14 && ((y >= 0 && y <= 14) || (y <= 0 && y >= -14)))
				{
					enemies->at(whichEnemyIsChoosen).second[0]->UnitShape.move(14, y);
				}
				else if (x <= -14 && ((y >= 0 && y <= 14) || (y <= 0 && y >= -14)))
				{
					enemies->at(whichEnemyIsChoosen).second[0]->UnitShape.move(-14, y);
				}
				else if (y >= 14 && ((x >= 0 && x <= 14) || (x <= 0 && x >= -14)))
				{
					enemies->at(whichEnemyIsChoosen).second[0]->UnitShape.move(x, 14);
				}
				else if (y <= -14 && ((x >= 0 && x <= 14) || (x <= 0 && x >= -14)))
				{
					enemies->at(whichEnemyIsChoosen).second[0]->UnitShape.move(x, -14);
				}
				else
				{
					cout << "Cos nie tak w przemieszczaniu sie AI-0 po mapie (Unit.cpp -> updateAiUnits())\n";
				}
			}
			else if (enemyCloser)
			{
				this->fight(*closestEnemyUnit(enemies->at(whichEnemyIsChoosen).second[0], *units, *enemies));
			}
			else
			{
				this->cityAttack(*closestEnemyCity(*districts, enemies->at(whichEnemyIsChoosen).second[0])->cities.back());
			}
		}
	}
}

District* Unit::closestEnemyCity(map<string, District*> districts, Unit* unit)
{
	District* closestDistrict = nullptr;
	float distance = numeric_limits<float>::max();
	float distanceTemp;
	for (map<string, District*>::iterator it = districts.begin(); it != districts.end(); it++)
	{
		if (unit->colorOfOwner != (*it).second->cities.back()->colorOfOwner)
		{
			distanceTemp = sqrt(
				pow((*it).second->cities.back()->getPosition().x - unit->UnitShape.getPosition().x, 2) +
				pow((*it).second->cities.back()->getPosition().y - unit->UnitShape.getPosition().y, 2)
			);
			if (distanceTemp < distance)
			{
				distance = distanceTemp;
				closestDistrict = (*it).second;
			}
		}
	}
	return closestDistrict;
}

Unit* Unit::closestEnemyUnit(Unit* unit, vector <Unit*> playerUnit, vector<pair<Enemy*, vector<Unit*>>> enemies)
{
	Unit* closestUnit = nullptr;
	float distance = numeric_limits<float>::max();
	float distanceTemp = 0;
	for (vector<pair<Enemy*, vector<Unit*>>>::iterator it = enemies.begin(); it != enemies.end(); it++)
	{
		for (auto& i : (*it).second)
		{
			if (i->colorOfOwner != this->colorOfOwner)
			{
				distanceTemp = sqrt(
					pow(i->UnitShape.getPosition().x - this->UnitShape.getPosition().x, 2) +
					pow(i->UnitShape.getPosition().y - this->UnitShape.getPosition().y, 2)
				);
				if (distanceTemp < distance)
				{
					{
						distance = distanceTemp;
						closestUnit = i;
					}
				}
			}
		}
	}
	for (vector <Unit*>::iterator it = playerUnit.begin(); it != playerUnit.end(); it++)
	{
		distanceTemp = sqrt(
			pow((*it)->UnitShape.getPosition().x - this->UnitShape.getPosition().x, 2) +
			pow((*it)->UnitShape.getPosition().y - this->UnitShape.getPosition().y, 2)
		);
		if (distanceTemp < distance)
		{
			{
				distance = distanceTemp;
				closestUnit = (*it);
			}
		}
	}

	return closestUnit;
}