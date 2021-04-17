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
//Wy�wietlanie i updatowanie
void District::update(Vector2f mpos)
{
	if (!this->cities.empty())
		for (auto& i : this->cities)
			i->update();
	this->shape.setOutlineColor(Color(1, 2, 3, 0));
	this->shape.setOutlineThickness(0);
	if (this->shape.getGlobalBounds().contains(mpos)) // Trzeba potem to zmieni� - convex nie wspiera GlobalBounds i trzeba u�y� co� innego albo jako� sprawdza� inaczej
	{
		this->shape.setOutlineThickness(1);
		this->shape.setOutlineColor(Color::White);

		this->isCursor = true;	//Je�li nad dystryktem to true

		//Sprawd� czy zosta� klikni�ty
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

//Rysowanie dystrykt�w
void District::render(RenderTarget* target)
{
	target->draw(this->shape);
	/**if (!this->cities.empty())
		for (auto& i : this->cities)
			i->render();*/
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
void District::initCity(string name, int popMax)
{
	City* temp = new City();
	this->cities.push_back(temp);
	this->cities.back()->initCity(name, popMax);
}

//Inicjowanie kszta�tu