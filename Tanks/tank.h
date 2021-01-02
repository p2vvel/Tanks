#pragma once


#include<nlohmann/json.hpp>
#include "data_serializers.h"

#include<SFML/Graphics.hpp>
#include<cmath>

#include "skidmarks.h"

#include "names.h"


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
	friend void to_json(nlohmann::json& j, const Tank& tank);
	friend void from_json(const nlohmann::json& j, Tank& tank);

	friend class Engine;

	unsigned char max_speed;
	float speed;

	float handling;

	sf::Vector2f movement_vector;

	short angle;
	sf::Vector2f position;
	Tank_barrel* barrel;

	sf::Sprite* tank_body;

	Skidmarks* skidmarks;	//slad po gasienicach - sa opcjonalne

	short tank_id;

	Names::tank_color my_color;

public:
	Tank(const sf::Sprite& tank_sprite, const Names::tank_color &color, Tank_barrel* new_barrel, Skidmarks* marks = nullptr);
	~Tank();


	void set_ID(const short& ID) { this->tank_id = ID;  }
	void set_position(const sf::Vector2f& new_pos);

	void change_speed(const float& new_speed);
	void add_speed(const float& new_speed);
	void set_angle(const short& new_angle);
	void add_angle(const short& new_angle);

	void update();
	void draw(sf::RenderWindow& win, const bool &draw_skidmarks = false);

	void draw_skidmarks(sf::RenderWindow& win);

	void accelerate();
	void decelerate();
	void turn_left();
	void turn_right();
	bool shot();
};