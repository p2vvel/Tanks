#pragma once
#include<math.h>


#include<SFML/Graphics.hpp>




class Tank;

class Tank_barrel
{
	friend class Tank;
	friend class Engine;

	short angle;
	sf::Vector2f position;
	sf::Sprite* barrel_body;


	sf::Clock timer;
	sf::Time shot_interval;	//czas pomiedzy koelnymi strzalami
public:
	Tank_barrel(const sf::Sprite& barrel_sprite, const sf::Time& time_between_shots);
	~Tank_barrel();


	void set_angle(const short& new_angle) { angle = new_angle % 360; }
	void add_angle(const short& new_angle) { angle = (angle + new_angle) % 360; }


	void set_position(const sf::Vector2f& new_position) { position = new_position; }
	void move(const sf::Vector2f& new_position) { position += new_position; }

	void update();

	void draw(sf::RenderWindow& window);

	bool shot();
};