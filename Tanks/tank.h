#pragma once

#include<SFML/Graphics.hpp>

#include<cmath>


class Engine;
class Tank_barrel;

#define MAX_SPEED (handling * 10.0)
#define MAX_REVERSE_SPEED (handling * 7.0)
#define ACCELERATION_SPEED (handling / 3.0)
#define DECELERATION_SPEED (handling * (2.0 / 3))
#define TURN_ANGLE (handling * 5.0)
#define IDLE_SPEED_LOSS (handling / 8.0)


class Tank
{
	friend class Engine;

	unsigned char max_speed;
	float speed;

	float handling;

	sf::Vector2f movement_vector;

	short angle;
	sf::Vector2f position;
	Tank_barrel* barrel;

	sf::Sprite* tank_body;


public:
	Tank(const sf::Sprite& tank_sprite, Tank_barrel* new_barrel);
	~Tank();

	void set_position(const sf::Vector2f& new_pos);

	void change_speed(const float& new_speed);
	void add_speed(const float& new_speed);
	void set_angle(const short& new_angle);
	void add_angle(const short& new_angle);

	void update();
	void draw(sf::RenderWindow& win);


	void accelerate();
	void decelerate();
	void turn_left();
	void turn_right();
	bool shot();
};