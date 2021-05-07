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

//settery
void District::setColor()
{
	//this->shape.setFillColor(Color());
}

/// <summary>Zwraca isCursor.</summary>
/// <returns>Bool</returns>
bool District::returnIsCursorOnDistrict()
{
	return this->isCursor;
}
//Wy�wietlanie i updatowanie
void District::update(Vector2f mpos)
{
	if (!this->cities.empty())
		for (auto& i : this->cities)
			i->update(mpos);
	
	if (this->shape.getGlobalBounds().contains(mpos)) // Trzeba potem to zmieni� - convex nie wspiera GlobalBounds i trzeba u�y� co� innego albo jako� sprawdza� inaczej
	{
		

		this->isCursor = true;	//Je�li nad dystryktem to true

		//Sprawd� czy zosta� klikni�ty
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (this->mouseHeld == false) {
				this->mouseHeld = true;
				//std::cout << "Elo\n";
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

//Rysowanie dystrykt�w
void District::render(RenderTarget* target)
{
	target->draw(this->shape);
	if (!this->cities.empty())
		for (auto& i : this->cities)
			i->render(target);
}

/*
	@return Vector2f

	Zwraca po�o�enie dystryktu - na razie nie dzia�a i zwraca po�o�enie 1 punktu tego dystryktu

*/
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
	int sizeOfCity;
	if (city_name == "Rzym")
		sizeOfCity = 3;
	else
	{
		sizeOfCity = rand() % 3 + 1;
	}
	switch (sizeOfCity)
	{
	case 1:	this->cities.push_back(new Settlement(city_name ,Vector2f(pointA, pointB), this->shape.getFillColor())); break;
	case 2:	this->cities.push_back(new Village(city_name ,Vector2f(pointA, pointB), this->shape.getFillColor())); break;
	case 3:	this->cities.push_back(new Town(city_name ,Vector2f(pointA, pointB), this->shape.getFillColor())); break;
	}
	
	this->cities.back()->initCity(sf::Vector2f(pointA, pointB));
}

//Inicjowanie kszta�tu