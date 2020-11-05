#pragma once

#include <SFML/Graphics.hpp>

#include "storage.h"
#include "tank_barrel.h"
#include "tank.h"


#include<vector>
#include <cmath>



#define GET_SPRITE_HQ(NAME) (storage.sprite_rects_hq[Storage::sprite_index::NAME])



class Engine
{
	Storage storage;
	sf::RenderWindow* window;


	short mouse_aim_angle(const Tank_barrel& barrel);
	void control_tank(Tank& tank);
public:
	Engine();
	Engine(sf::RenderWindow& win);
	~Engine();

	static const sf::Vector2f& calculate_vector(const float& distance_, const short& angle_);


	void test();
};