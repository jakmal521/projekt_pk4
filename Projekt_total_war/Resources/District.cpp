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

int District::returnIsPlayer()
{
	return this->isPlayer;
}
//Wyœwietlanie i updatowanie
void District::update(Vector2f mpos)
{
	if (!this->cities.empty())
		for (auto& i : this->cities)
			i->update();
	this->shape.setOutlineColor(Color(1, 2, 3, 0));
	this->shape.setOutlineThickness(0);
	if (this->shape.getGlobalBounds().contains(mpos))
	{
		this->shape.setOutlineThickness(1);
		this->shape.setOutlineColor(Color::White);

		//SprawdŸ czy zosta³ klikniêty
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (this->mouseHeld == false) {
				this->mouseHeld = true;
				this->isPlayer = 1;
				std::cout << "Elo";
				//this->pressed = true;
			}
		}
		else
		{
			this->mouseHeld = false;
		}
	}

	/*if (this->isPlayer) {
		this->
	}*/
	//this->playerShape.setPosition();
}
void District::render(RenderTarget* target)
{
	target->draw(this->shape);
	if (!this->cities.empty())
		for (auto& i : this->cities)
			i->render();
}
//Inicjowanie kszta³tu