#pragma once
#include<SFML/Graphics.hpp>

#include "engine.h"
#include "data_serializers.h"
#include "names.h"


//class storing bullet pattern that is later used to create new bullets when players trigger shot, 
class Bullet_base {
protected:
	short shooter_id;
	sf::Sprite* bullet_body;	//sprite
	short power;	//HP that tank that wwas hit lost
	float speed;	//bullets speed
	Names::barrel_size my_size;
	Names::tank_color my_color;
public:
	Bullet_base(const sf::Sprite& bullet_sprite, const Names::barrel_size& size, const Names::tank_color& color, const short& bullet_power, const float& bullet_speed) {
		bullet_body = new sf::Sprite(bullet_sprite);
		power = bullet_power;
		speed = bullet_speed;
		my_size = size;
		my_color = color;
		shooter_id = -1;	//tank id is undefined until player connects to server, -1 is default value
	}

	//copying constructor
	Bullet_base(const Bullet_base& src) {
		this->bullet_body = new sf::Sprite(*src.bullet_body);
		this->speed = src.speed;
		this->power = src.power;
		this->my_color = src.my_color;
		this->my_size = src.my_size;
		this->shooter_id = src.shooter_id;
	}

	~Bullet_base() {
		delete bullet_body;
	}

	void set_shooter_ID(const short& new_id) { shooter_id = new_id; }
};


//Wlasciwa klasa odpowiadajaca za pociski wystrzeliwane przez czolgi
class Bullet : public Bullet_base {
	friend void to_json(nlohmann::json& j, const Bullet& bullet);
	friend void from_json(const nlohmann::json& j, Bullet& bullet);
	friend class Engine;

	short angle;	
public:
	Bullet(const Bullet_base& pattern, const sf::Vector2f& new_pos, const short& new_angle);
	~Bullet();

	virtual void update();
	virtual void draw(sf::RenderWindow& win);
};