#include "bullet.h"

Bullet::Bullet(const Bullet_base& pattern, const sf::Vector2f& new_pos, const short& new_angle) : Bullet_base(pattern)
{
	angle = new_angle;
	bullet_body->setOrigin(bullet_body->getGlobalBounds().width / 2, 0);
	bullet_body->setRotation(new_angle);
	bullet_body->setPosition(new_pos);
}

Bullet::~Bullet()
{
}

void Bullet::update()
{
	bullet_body->move(Engine::calculate_vector(speed, angle));
}

void Bullet::draw(sf::RenderWindow& win)
{
	win.draw(*bullet_body);
}
