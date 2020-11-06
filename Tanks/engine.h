#pragma once

#include <SFML/Graphics.hpp>

#include "storage.h"
#include "tank_barrel.h"
#include "tank.h"
#include "muzzle_flash.h"
#include "bullet.h"


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



	enum tank_color { blue, dark, green, red, sand };
	enum barrel_size { big, medium, small };
	Tank_barrel* generate_Barrel(const Engine::tank_color& color, const Engine::barrel_size& size) const;
	Bullet_base* generate_Bullet_base(const Engine::tank_color& color, const Engine::barrel_size& size) const;
	Tank* generate_Tank(const Engine::tank_color& color, const Engine::barrel_size& size) const;
};