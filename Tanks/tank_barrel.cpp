#include "tank_barrel.h"


#include "tank.h"
#include "engine.h"


Tank_barrel::Tank_barrel(const sf::Sprite& barrel_sprite, const sf::Time& time_between_shots)
{
	barrel_body = new sf::Sprite(barrel_sprite);
	barrel_body->setOrigin(barrel_body->getGlobalBounds().width / 2, barrel_body->getGlobalBounds().height * 0.30);
	angle = 0;

	barrel_body->setScale(1, -1);	//bez tego lufa by³aby odwrócona w przeciwnym kierunku ni¿ myszka

	shot_interval = time_between_shots;
	timer.restart();

}

Tank_barrel::~Tank_barrel()
{
	delete barrel_body;
}

void Tank_barrel::update()
{

	barrel_body->setRotation(angle);
	barrel_body->setPosition(position);
}

void Tank_barrel::draw(sf::RenderWindow& window)
{

	window.draw(*barrel_body);
}

bool Tank_barrel::shot()
{
	if (timer.getElapsedTime() >= shot_interval)
	{
		timer.restart();


		return true;
	}
	else
		return false;
}
