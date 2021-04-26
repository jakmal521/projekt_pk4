#include "..\Headers\HeadBar.h"
//Konstruktor i destruktor
HeadBar::HeadBar(float x, float y, Font* font, Player* player)
{
	this->barShape.setSize(Vector2f(x, y * 0.1));
	this->barShape.setFillColor(Color(128, 128, 128, 200));
	this->barShape.setPosition(0, 0);
	this->text.setFont(*font);
	this->text.setFillColor(Color::Black);
	this->text.setCharacterSize(8);
	this->text.setPosition(this->barShape.getSize().x + (this->barShape.getGlobalBounds().width / 2) - this->text.getGlobalBounds().width / 2, this->barShape.getPosition().y + (this->barShape.getGlobalBounds().height / 2) - this->text.getGlobalBounds().height / 2);
	this->player = player;
}

HeadBar::~HeadBar()
{
}
//updatowanie i wyœwietlanie na ekranie
void HeadBar::update()
{
	stringstream ss;
	ss << "Ilosc zlota: " << this->player->gold << " Ilosc zolnierzy: TODO" << " Ilosc posiadanych regionow TODO";
	this->text.setString(ss.str());
	this->text.setPosition(this->barShape.getPosition().x + (this->barShape.getGlobalBounds().width / 2) - this->text.getGlobalBounds().width / 2, this->barShape.getPosition().y + (this->barShape.getGlobalBounds().height / 2) - this->text.getGlobalBounds().height / 2);
}

void HeadBar::render(sf::RenderTarget* window)
{
	window->draw(this->barShape);
	window->draw(this->text);
}

void HeadBar::setPos(sf::Vector2f viewPos, sf::Vector2f viewOrigin)
{
	viewPos -= viewOrigin;
	this->barShape.setPosition(viewPos);
}