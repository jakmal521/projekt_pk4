#include "..\Headers\District.h"
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
//Wyœwietlanie i updatowanie
void District::update(Vector2f mpos)
{
	if (!this->cities.empty())
		for (auto& i : this->cities)
			i->update();
	this->shape.setOutlineColor(Color(1,2,3,0));
	this->shape.setOutlineThickness(0);
	if (this->shape.getGlobalBounds().contains(mpos))

	{
		this->shape.setOutlineThickness(1);

		this->shape.setOutlineColor(Color::White);
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			//this->pressed = true;
		}
	}
}
void District::render(RenderTarget* target)
{
	target->draw(this->shape);
	if (!this->cities.empty())
		for (auto& i : this->cities)
			i->render();
}
//Inicjowanie kszta³tu