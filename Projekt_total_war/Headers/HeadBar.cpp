#include "..\Headers\HeadBar.h"
//Konstruktor i destruktor
HeadBar::HeadBar(float x, float y, Font* font, Player* player)
{
	this->nextTurn = 0;
	this->mouseHeld = false;
	this->barShape.setSize(Vector2f(x, y * 0.1));
	this->barShape.setFillColor(Color(128, 128, 128, 200));
	this->text.setFont(*font);
	this->text.setFillColor(Color::Black);
	this->text.setCharacterSize(8);
	this->player = player;

	this->nextTurnShape.setSize(Vector2f(x * 0.15, y * 0.1));
	this->nextTurnShape.setFillColor(Color(128, 128, 128, 230));
	this->nextTurnShape.setOutlineThickness(1);
	this->nextTurnShape.setOutlineColor(Color::Black);
	this->nextTurnText.setFont(*font);
	this->nextTurnText.setFillColor(Color::Black);
	this->nextTurnText.setCharacterSize(10);
}

HeadBar::~HeadBar()
{
}
//updatowanie i wyœwietlanie na ekranie
void HeadBar::update(int amountOfDistricts, Vector2f mpos)
{
	stringstream ss;
	ss << "Ilosc zlota: " << this->player->gold << " Ilosc posiadanych regionow: " << amountOfDistricts;
	this->text.setString(ss.str());
	this->text.setPosition(this->barShape.getPosition().x + (this->barShape.getGlobalBounds().width / 2) - this->text.getGlobalBounds().width / 2, this->barShape.getPosition().y + (this->barShape.getGlobalBounds().height / 2) - this->text.getGlobalBounds().height / 2);

	this->nextTurnText.setString("Nastepna runda");
	this->nextTurnText.setPosition(this->nextTurnShape.getPosition().x + this->nextTurnShape.getSize().x * 0.085, this->nextTurnShape.getPosition().y + this->nextTurnShape.getSize().y * 0.4);

	this->nextTurnShape.setFillColor(Color(128, 128, 128, 230));
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		if (this->nextTurnShape.getGlobalBounds().contains(mpos))
		{
			if (this->mouseHeld == false)
			{
				this->mouseHeld = true;
				this->nextTurn = 1;
				this->nextTurnShape.setFillColor(Color::Green);
			}
		}
	}
	else
	{
		this->mouseHeld = false;
	}
}

void HeadBar::render(sf::RenderTarget* window)
{
	window->draw(this->barShape);
	window->draw(this->text);
	window->draw(this->nextTurnShape);
	window->draw(this->nextTurnText);
}

void HeadBar::setPos(sf::Vector2f viewPos, sf::Vector2f viewOrigin)
{
	viewPos -= viewOrigin;
	this->barShape.setPosition(viewPos);
	this->nextTurnShape.setPosition(viewPos.x + 0.85 * this->barShape.getSize().x, viewPos.y);
}