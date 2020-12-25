#pragma once
#include<math.h>


#include<SFML/Graphics.hpp>



#include "data_serializers.h"


class Bullet_base;
class Bullet;
class Tank;
class Muzzle_flash;

class Tank_barrel
{

	friend void to_json(nlohmann::json& j, const Tank_barrel& barrel);
	friend void from_json(const nlohmann::json& j, Tank_barrel& barrel);

	friend class Tank;
	friend class Engine;

	short angle;
	sf::Vector2f position;
	sf::Sprite* barrel_body;

	Muzzle_flash* muzzle_flash;
	Bullet_base* bullet_pattern;

	sf::Clock timer;
	sf::Time shot_interval;	//czas pomiedzy koelnymi strzalami
public:
	Tank_barrel(const sf::Sprite& barrel_sprite, Bullet_base* pattern, const sf::Time& time_between_shots, Muzzle_flash* flash_pattern = nullptr);
	~Tank_barrel();


	void set_angle(const short& new_angle) { angle = new_angle % 360; }
	void add_angle(const short& new_angle) { angle = (angle + new_angle) % 360; }


	void set_position(const sf::Vector2f& new_position) { position = new_position; }
	void move(const sf::Vector2f& new_position) { position += new_position; }

	void update();

	void draw(sf::RenderWindow& window);

	bool shot();

	Bullet* generate_bullet() const;


};