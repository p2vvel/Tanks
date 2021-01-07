#pragma once

#include <SFML/Graphics.hpp>

#include "storage.h"
#include "tank_barrel.h"
#include "tank.h"
#include "skidmarks.h"
#include "muzzle_flash.h"
#include "bullet.h"


#include<vector>
#include <cmath>

#include "data_serializers.h"

#include "net_client.h"

#include <stdlib.h>
#include <time.h>

#include "info.h"


#define GET_SPRITE_HQ(NAME) (storage.sprite_rects_hq[Storage::sprite_index::NAME])





#include "names.h"

class Engine
{
	Storage storage;
	sf::RenderWindow* window;

	NetClient* net_client;

	short mouse_aim_angle(const Tank_barrel& barrel);
	void control_tank(Tank& tank);

public:
	Engine();
	Engine(sf::RenderWindow& win, const unsigned short& server_port, const std::string& server_address);
	~Engine();

	static const sf::Vector2f& calculate_vector(const float& distance_, const short& angle_);


	void test();




	Tank_barrel* generate_Barrel(const Names::tank_color& color, const Names::barrel_size& size) const;
	Bullet_base* generate_Bullet_base(const Names::tank_color& color, const Names::barrel_size& size) const;
	Tank* generate_Tank(const Names::tank_color& color, const Names::barrel_size& size) const;
	Tank* generate_random_Tank() const;



};