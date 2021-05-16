#include "..\Headers\District.h"
#include "..\Headers\Unit.h"
//konstruktor i destruktor
District::District(string _name)
{
	this->name = _name;
}

District::~District()
{
}



/// <summary>Zwraca isCursor.</summary>
/// <returns>Bool</returns>
bool District::returnIsCursorOnDistrict()
{
	return this->isCursor;
}
//Wyœwietlanie i updatowanie
void District::update(Vector2f mpos)
{
	if (!this->cities.empty())
		for (auto& i : this->cities)
			i->update(mpos);

	if (this->shape.getGlobalBounds().contains(mpos)) 
	{
		this->isCursor = true;	//Jeœli nad dystryktem to true

		//SprawdŸ czy zosta³ klikniêty
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (this->mouseHeld == false) {
				this->mouseHeld = true;
				
			}
		}
		else
		{
			this->mouseHeld = false;
		}
	}
	else
	{
		this->isCursor = false;
	}
}

//Rysowanie dystryktów
void District::render(RenderTarget* target)
{
	if (this->cities.back()->colorOfOwner != this->shape.getFillColor())
				this->shape.setFillColor(this->cities.back()->colorOfOwner);
	target->draw(this->shape);
	if (!this->cities.empty())
	{
		for (auto& i : this->cities)
		{
			i->render(target);
			
		}
	}
	
}

sf::Vector2f District::returnPosition()
{
	return sf::Vector2f(this->shape.getPoint(1));
}

//Inicjowanie miasta
void District::initCity(string line)
{
	stringstream stream(line);
	string city_name;
	int pointA, pointB;
	stream >> city_name >> pointA >> pointB;
	if (city_name == "Rzym")
		this->sizeOfCity = 1;
	else
	{
		this->sizeOfCity = rand() % 3 + 1;
	}
	switch (this->sizeOfCity)
	{
	case 1:	this->cities.push_back(new Settlement(city_name, Vector2f(pointA, pointB), this->shape.getFillColor())); break;
	case 2:	this->cities.push_back(new Village(city_name, Vector2f(pointA, pointB), this->shape.getFillColor())); break;
	case 3:	this->cities.push_back(new Town(city_name, Vector2f(pointA, pointB), this->shape.getFillColor())); break;
	}

	this->cities.back()->initCity(sf::Vector2f(pointA, pointB));
}

