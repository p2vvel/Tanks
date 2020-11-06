#pragma once

#include<SFML/Graphics.hpp>


#include "engine.h"

/*Klasa sluzaca jedynie do przechowywania informacji o typie pocisku jaku wystrzeliwuje czolg.
Nie pozwala na wyswietlanie, ruch, ani zadne dzialania zwiazane z pociskiem - jest tylko szablonem z podstawowymi informacjami*/
class Bullet_base
{
protected:
	sf::Sprite* bullet_body;	//sprite
	short power;	//zadawane obrazenia
	float speed;	//predkosc z jaka leci pocisk
public:
	Bullet_base(const sf::Sprite& bullet_sprite, const short& bullet_power, const float& bullet_speed)
	{
		bullet_body = new sf::Sprite(bullet_sprite);
		power = bullet_power;
		speed = bullet_speed;
	}

	Bullet_base(const Bullet_base& src)	//konstruktor kopiujacy
	{
		this->bullet_body = new sf::Sprite(*src.bullet_body);
		this->speed = src.speed;
		this->power = src.power;
	}

	~Bullet_base()
	{
		delete bullet_body;
	}
};


//Wlasciwa klasa odpowiadajaca za pociski wystrzeliwane przez czolgi
class Bullet : public Bullet_base
{
	friend class Engine;

	short angle;	//kat lotu
public:
	Bullet(const Bullet_base& pattern, const sf::Vector2f& new_pos, const short& new_angle);
	~Bullet();

	virtual void update();
	virtual void draw(sf::RenderWindow& win);
};