#include "..\Headers\Position.h"

/*
	@param Position
	Konstruktor kwadratu, jako widok dla uzytkownika
	-setSize	-rozmiar kwadratu
	-setPosition	-ustawienie pozycji kwadratu
*/
Position::Position()
{
	this->shape.setSize(sf::Vector2f(400.0f, 300.0f));
	this->shape.setOrigin(shape.getSize() / 2.0f); //Ustawienie miejsca w kwadracie dla którego bedzie relatywny (srodek kwadratu)
	this->shape.setPosition(400.0f, 300.0f);
	this->shape.setFillColor(sf::Color(255, 255, 255, 255));
}

Position::Position(sf::Vector2f viewSize)
{
	this->shape.setSize(viewSize);
	this->shape.setOrigin(shape.getSize() / 2.0f); //Ustawienie miejsca w kwadracie dla którego bedzie relatywny (srodek kwadratu)
	this->shape.setPosition(400.0f, 300.0f);
	this->shape.setFillColor(sf::Color(255, 255, 255, 255));
}

Position::~Position()
{
	delete this->headBar;
}

void Position::update(int amountOfDistricts, Vector2f mpos)
{
	
	float speed = 4.f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		this->shape.move(-speed, 0);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		this->shape.move(speed, 0);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		this->shape.move(0, -speed);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		this->shape.move(0, speed);

	this->headBar->setPos(this->shape.getPosition(), this->shape.getOrigin());
	this->headBar->update(amountOfDistricts, mpos);
}

void Position::render(sf::RenderTarget* window)
{
	this->headBar->render(window);
	
}

void Position::initHeadBar(Font* font, Player* player)
{
	this->headBar = new HeadBar(this->shape.getSize().x, this->shape.getSize().y, font, player);
}

bool Position::isNextTurn()
{
	if (this->headBar->nextTurn == 1)
	{
		this->headBar->nextTurn = 0;
		return true;
	}
	return false;
}