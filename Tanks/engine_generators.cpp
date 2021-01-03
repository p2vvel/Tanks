#include "engine.h"



Tank_barrel* Engine::generate_Barrel(const Names::tank_color& color, const Names::barrel_size& size) const
{
	sf::Time shot_period;
	Muzzle_flash* flash;// = new Muzzle_flash()

	if (size == Names::barrel_size::small){
		shot_period = sf::seconds(0.4);
		flash = new Muzzle_flash(storage.texture_hq, GET_SPRITE_HQ(shotThin), 8);
	}
	else if (size == Names::barrel_size::medium)	{
		shot_period = sf::seconds(0.8);
		flash = new Muzzle_flash(storage.texture_hq, GET_SPRITE_HQ(shotLarge), 8);
	}
	else{	//barrel_size == big

		shot_period = sf::seconds(1.2);
		flash = new Muzzle_flash(storage.texture_hq, GET_SPRITE_HQ(shotLarge), 8);
	}

	return new Tank_barrel(sf::Sprite(storage.texture_hq, Storage::get_BarrelRect(color, size)), size, color, (generate_Bullet_base(color, size)), shot_period, flash);
}


Bullet_base* Engine::generate_Bullet_base(const Names::tank_color& color, const Names::barrel_size& size) const
{
	short power;
	float speed;

	if (size == Names::barrel_size::small) {
		speed = 40;
		power = 15;
	}
	else if (size == Names::barrel_size::medium) {
		speed = 30;
		power = 20;
	}
	else {	//barrel_size == big{
		speed = 25;
		power = 40;
	}

	return new Bullet_base(sf::Sprite(storage.texture_hq, Storage::get_BulletRect(color, size)), power, speed);
}


Tank* Engine::generate_Tank(const Names::tank_color& color, const Names::barrel_size& size) const
{
	sf::IntRect skidmarks_rect = GET_SPRITE_HQ(tracksLarge);
	skidmarks_rect.height = 6;

	return new Tank(sf::Sprite(storage.texture_hq, Storage::get_TankRect(color)), color, generate_Barrel(color, size), new Skidmarks(new sf::Sprite(storage.texture_hq, skidmarks_rect), 40, 8));
}


Tank* Engine::generate_random_Tank() const
{
	srand(time(NULL));
	Names::tank_color color;
	Names::barrel_size size;

	short temp = rand() % 5;

	switch (temp) {
	case 0:
		color = Names::tank_color::blue;
		break;
	case 1:
		color = Names::tank_color::dark;
		break;
	case 2:
		color = Names::tank_color::red;
		break;
	case 3:
		color = Names::tank_color::sand;
		break;
	default:
		color = Names::tank_color::green;
	}

	temp = rand() % 3;

	switch (temp) {
	case 0:
		size = Names::barrel_size::small;
		break;
	case 1:
		size = Names::barrel_size::medium;
		break;
	default:
		size = Names::barrel_size::big;
	}

	return generate_Tank(color, size);
}