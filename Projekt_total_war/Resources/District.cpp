#include "..\Headers\District.h"
#include "..\Headers\Player.h"
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
//Wyœwietlanie i updatowanie
void District::update(Vector2f mpos)
{
	if (!this->cities.empty())
		for (auto& i : this->cities)
			i->update();
	this->shape.setOutlineColor(Color(1, 2, 3, 0));
	this->shape.setOutlineThickness(0);
	if (this->shape.getGlobalBounds().contains(mpos)) // Trzeba potem to zmieniæ - convex nie wspiera GlobalBounds i trzeba u¿yæ coœ innego albo jakoœ sprawdzaæ inaczej
	{
		this->shape.setOutlineThickness(1);
		this->shape.setOutlineColor(Color::White);

		this->isCursor = true;	//Jeœli nad dystryktem to true

		//SprawdŸ czy zosta³ klikniêty
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (this->mouseHeld == false) {
				this->mouseHeld = true;
				std::cout << "Elo";
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
	target->draw(this->shape);
	/**if (!this->cities.empty())
		for (auto& i : this->cities)
			i->render();*/
}

/*
	@return Vector2f

	Zwraca po³o¿enie dystryktu - na razie nie dzia³a i zwraca po³o¿enie 1 punktu tego dystryktu

*/
sf::Vector2f District::returnPosition()
{
	return sf::Vector2f(this->shape.getPoint(1));
}

//Inicjowanie miasta
void District::initCity(string name, int popMax)
{
	City* temp = new City();
	this->cities.push_back(temp);
	this->cities.back()->initCity(name, popMax);
}

//Inicjowanie kszta³tu