#include "tank.h"

#include "tank_barrel.h"

#include <cmath>

#include<iostream>

#include "engine.h"




Tank::Tank(const sf::Sprite& tank_sprite, Tank_barrel* new_barrel)
{
	tank_body = new sf::Sprite(tank_sprite);
	tank_body->setOrigin(tank_body->getGlobalBounds().width / 2, tank_body->getGlobalBounds().height / 2);
	tank_body->setScale(1, -1);	//Ustawienie, ktore powoduje ze korpus czolgu jest zwrocony domyslnie do gornej krawedzi okna (traktuje ta pozycje jako kat 0 stopni - w przypadku lufy tak samo)
	barrel = new_barrel;
	angle = 0;
	speed = 0;

	handling = 0.6;

}


Tank::~Tank()
{
	delete barrel;
	delete tank_body;
}


void Tank::set_position(const sf::Vector2f& new_pos)
{
	position = new_pos;
	barrel->set_position(new_pos);
	tank_body->setPosition(new_pos);
}


void Tank::change_speed(const float& new_speed)
{
	speed = new_speed;
}


void Tank::add_speed(const float& new_speed)
{
	if ((speed + new_speed) <= MAX_SPEED && (speed + new_speed) >= -MAX_REVERSE_SPEED)
		speed += new_speed;
}


void Tank::set_angle(const short& new_angle)
{
	angle = (new_angle % 360) > 0 ? (new_angle % 360) : (360 + (new_angle % 360));
}


void Tank::add_angle(const short& new_angle)
{
	short temp = new_angle - (new_angle > 0 ? abs(handling * (speed / max_speed) * new_angle) : -abs(handling * (speed / max_speed) * new_angle));

	angle = (angle + temp) % 360;
	if (angle < 0)
		angle = 360 + angle;
	angle += new_angle;
}


void Tank::update()
{
	movement_vector = Engine::calculate_vector(speed, angle);
	position += movement_vector;

	tank_body->setPosition(position);
	tank_body->setRotation(angle);

	barrel->set_position(position);
	barrel->update();



	if (speed >= IDLE_SPEED_LOSS || speed <= -IDLE_SPEED_LOSS)
		speed = (speed > 0 ? speed - IDLE_SPEED_LOSS : speed + IDLE_SPEED_LOSS);
	else
		speed = 0;//*/
}


void Tank::draw(sf::RenderWindow& win)
{
	win.draw(*tank_body);
	barrel->draw(win);
}




void Tank::accelerate()
{
	if (speed >= 0 && (speed + ACCELERATION_SPEED) <= MAX_SPEED)	//normalne przyspieszanie od 0
		speed += ACCELERATION_SPEED;
	else if (speed < 0 && (speed + DECELERATION_SPEED) <= MAX_SPEED)  //hamowanie jazdy do tylu
		speed += DECELERATION_SPEED;
}


void Tank::decelerate()	//hamowanie jazdy do przodu i jazda do tylu, czolg przyspiesza 2 razy szybciej do tylu, ale za to osiaga mniejsza predkosc - 80% tego co do przodu
{
	if ((speed - DECELERATION_SPEED) >= -MAX_REVERSE_SPEED)
		speed -= DECELERATION_SPEED;
}


void Tank::turn_left()
{
	this->add_angle(-TURN_ANGLE);
}


void Tank::turn_right()
{
	this->add_angle(TURN_ANGLE);
}

bool Tank::shot()
{
	bool result = barrel->shot();


	return result;
}