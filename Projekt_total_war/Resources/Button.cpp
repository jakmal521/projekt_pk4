#include "..\Headers\MainMenu.h"
//Kontruktory i destruktory
Button::Button(float x, float y, float width, float height, Font* _font, string _text, Color _color)
{
	this->button.setPosition(x, y);
	this->button.setSize(Vector2f(width, height));
	this->font = _font;
	this->text.setFont(*this->font);
	this->text.setString(_text);
	this->text.setFillColor(Color::White);
	this->text.setCharacterSize(18);
	this->text.setPosition(this->button.getPosition().x + (this->button.getGlobalBounds().width / 2) - this->text.getGlobalBounds().width / 2, this->button.getPosition().y + (this->button.getGlobalBounds().height / 2) - this->text.getGlobalBounds().height / 2);
	this->color = _color;
	this->button.setFillColor(this->color);
	this->button.setOutlineThickness(2);
	this->button.setOutlineColor(this->color);
	this->pressed = false;
}

Button::~Button()
{
}
//wyswietlanie na ekranie
void Button::render(RenderTarget* target)
{
	target->draw(this->button);
	target->draw(this->text);
}
//Aktualizowanie przycisku
void Button::update(Vector2f mpos)
{	//Przy najezdzie czarna ramka
	
	this->button.setOutlineColor(this->color);
	this->pressed = false;
	if (this->button.getGlobalBounds().contains(mpos))
	{
		this->button.setOutlineColor(Color::Black);
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			this->pressed = true;
		}
	}
}

bool Button::press()
{
	if (this->pressed == true)
		return true;
	return false;
}
//Akcesory
float Button::getPosX()
{
	return this->button.getGlobalBounds().left;
}

float Button::getPosY()
{
	return this->button.getGlobalBounds().top;
}

float Button::getHeight()
{
	return this->button.getGlobalBounds().height;
}

float Button::getWidth()
{
	return this->button.getGlobalBounds().width;
}

void Button::setText()
{
	this->text.setPosition(this->button.getPosition().x + (this->button.getGlobalBounds().width / 2) - this->text.getGlobalBounds().width / 2, this->button.getPosition().y + (this->button.getGlobalBounds().height / 2) - this->text.getGlobalBounds().height / 2);
}
