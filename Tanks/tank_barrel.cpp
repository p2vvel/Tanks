#include "tank_barrel.h"
#include "muzzle_flash.h"

#include "tank.h"
#include "engine.h"
#include "bullet.h"


Tank_barrel::Tank_barrel(const sf::Sprite& barrel_sprite, const Names::barrel_size& size, const Names::tank_color& color, Bullet_base* pattern, const sf::Time& time_between_shots, Muzzle_flash* flash_pattern)
{
	barrel_body = new sf::Sprite(barrel_sprite);
	barrel_body->setOrigin(barrel_body->getGlobalBounds().width / 2, barrel_body->getGlobalBounds().height * 0.30);
	angle = 0;

	barrel_body->setScale(1, -1);	//bez tego lufa by³lby odwrócona w przeciwnym kierunku ni¿ myszka

	muzzle_flash = flash_pattern;
	shot_interval = time_between_shots;
	timer.restart();

	bullet_pattern = pattern;

	my_size = size;
	my_color = color;

	shot_recently = false;
}

Tank_barrel::~Tank_barrel()
{
	delete barrel_body;
}

void Tank_barrel::update()
{
	if (muzzle_flash != nullptr && muzzle_flash->get_visibility())
	{
		float distance_from_barrel_center = abs(barrel_body->getOrigin().y - barrel_body->getLocalBounds().height);
		sf::Vector2f flash_position = barrel_body->getPosition() + Engine::calculate_vector(distance_from_barrel_center, angle);

		muzzle_flash->update(flash_position, angle);
	}

	barrel_body->setRotation(angle);
	barrel_body->setPosition(position);
}

void Tank_barrel::draw(sf::RenderWindow& window)
{
	shot_recently = false;	//end of frame so shot indicator can be resetted

	if (muzzle_flash != nullptr)
		muzzle_flash->draw(window);

	window.draw(*barrel_body);
	barrel_body->setScale(1, -1);	//restore sprite after being shot animation
}

bool Tank_barrel::shot()
{
	if (timer.getElapsedTime() >= shot_interval)
	{
		timer.restart();

		if (muzzle_flash != nullptr)
			muzzle_flash->set_visibility(true);

		shot_recently = true;	//indicates that player has shot a bullet

		return true;
	}
	else
		return false;
}

Bullet* Tank_barrel::generate_bullet() const
{
	float distance_from_barrel_center = abs(barrel_body->getOrigin().y - barrel_body->getLocalBounds().height);
	sf::Vector2f bullet_position = barrel_body->getPosition() + Engine::calculate_vector(distance_from_barrel_center, angle);



	return new Bullet(*bullet_pattern, bullet_position, angle);
}