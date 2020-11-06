#include "engine.h"



Tank_barrel* Engine::generate_Barrel(const Engine::tank_color& color, const Engine::barrel_size& size) const
{
	sf::IntRect texture_rect;

	if (color == Engine::tank_color::blue)
	{
		switch (size)
		{
		case Engine::barrel_size::small:
			texture_rect = GET_SPRITE_HQ(tankBlue_barrel2_outline);
			break;
		case Engine::barrel_size::medium:
			texture_rect = GET_SPRITE_HQ(tankBlue_barrel3_outline);
			break;
		default:	//case big
			texture_rect = GET_SPRITE_HQ(tankBlue_barrel1_outline);
			break;
		}
	}
	else if (color == Engine::tank_color::green)
	{
		switch (size)
		{
		case Engine::barrel_size::small:
			texture_rect = GET_SPRITE_HQ(tankGreen_barrel2_outline);
			break;
		case Engine::barrel_size::medium:
			texture_rect = GET_SPRITE_HQ(tankGreen_barrel3_outline);
			break;
		default:	//case big
			texture_rect = GET_SPRITE_HQ(tankGreen_barrel1_outline);
			break;
		}
	}
	else if (color == Engine::tank_color::red)
	{
		switch (size)
		{
		case Engine::barrel_size::small:
			texture_rect = GET_SPRITE_HQ(tankRed_barrel2_outline);
			break;
		case Engine::barrel_size::medium:
			texture_rect = GET_SPRITE_HQ(tankRed_barrel3_outline);
			break;
		default:	//case big
			texture_rect = GET_SPRITE_HQ(tankRed_barrel1_outline);
			break;
		}
	}
	else if (color == Engine::tank_color::sand)
	{
		switch (size)
		{
		case Engine::barrel_size::small:
			texture_rect = GET_SPRITE_HQ(tankSand_barrel2_outline);
			break;
		case Engine::barrel_size::medium:
			texture_rect = GET_SPRITE_HQ(tankSand_barrel3_outline);
			break;
		default:	//case big
			texture_rect = GET_SPRITE_HQ(tankSand_barrel1_outline);
			break;
		}
	}
	else	//color == dark
	{
		switch (size)
		{
		case Engine::barrel_size::small:
			texture_rect = GET_SPRITE_HQ(tankDark_barrel2_outline);
			break;
		case Engine::barrel_size::medium:
			texture_rect = GET_SPRITE_HQ(tankDark_barrel3_outline);
			break;
		default:	//case big
			texture_rect = GET_SPRITE_HQ(tankDark_barrel1_outline);
			break;
		}
	}

	sf::Sprite barrel_sprite(storage.texture_hq, texture_rect);
	sf::Time shot_period;

	if (size == Engine::barrel_size::small)
	{
		shot_period = sf::seconds(0.4);
	}
	else if (size == Engine::barrel_size::medium)
	{
		shot_period = sf::seconds(0.8);
	}
	else	//barrel_size == big
	{
		shot_period = sf::seconds(1.2);
	}

	return new Tank_barrel(sf::Sprite(storage.texture_hq, texture_rect), (generate_Bullet_base(color, size)), shot_period);
}


Bullet_base* Engine::generate_Bullet_base(const Engine::tank_color& color, const Engine::barrel_size& size) const
{
	sf::IntRect texture_rect;

	if (color == Engine::tank_color::blue)
	{
		switch (size)
		{
		case Engine::barrel_size::small:
			texture_rect = GET_SPRITE_HQ(bulletBlue1_outline);
			break;
		case Engine::barrel_size::medium:
			texture_rect = GET_SPRITE_HQ(bulletBlue3_outline);
			break;
		default:	//case big
			texture_rect = GET_SPRITE_HQ(bulletBlue2_outline);
			break;
		}
	}
	else if (color == Engine::tank_color::green)
	{
		switch (size)
		{
		case Engine::barrel_size::small:
			texture_rect = GET_SPRITE_HQ(bulletGreen1_outline);
			break;
		case Engine::barrel_size::medium:
			texture_rect = GET_SPRITE_HQ(bulletGreen3_outline);
			break;
		default:	//case big
			texture_rect = GET_SPRITE_HQ(bulletGreen2_outline);
			break;
		}
	}
	else if (color == Engine::tank_color::red)
	{
		switch (size)
		{
		case Engine::barrel_size::small:
			texture_rect = GET_SPRITE_HQ(bulletRed1_outline);
			break;
		case Engine::barrel_size::medium:
			texture_rect = GET_SPRITE_HQ(bulletRed3_outline);
			break;
		default:	//case big
			texture_rect = GET_SPRITE_HQ(bulletRed2_outline);
			break;
		}
	}
	else if (color == Engine::tank_color::sand)
	{
		switch (size)
		{
		case Engine::barrel_size::small:
			texture_rect = GET_SPRITE_HQ(bulletSand1_outline);
			break;
		case Engine::barrel_size::medium:
			texture_rect = GET_SPRITE_HQ(bulletSand3_outline);
			break;
		default:	//case big
			texture_rect = GET_SPRITE_HQ(bulletSand2_outline);
			break;
		}
	}
	else	//color == dark
	{
		switch (size)
		{
		case Engine::barrel_size::small:
			texture_rect = GET_SPRITE_HQ(bulletDark1_outline);
			break;
		case Engine::barrel_size::medium:
			texture_rect = GET_SPRITE_HQ(bulletDark3_outline);
			break;
		default:	//case big
			texture_rect = GET_SPRITE_HQ(bulletDark2_outline);
			break;
		}
	}


	short power;
	float speed;

	if (size == Engine::barrel_size::small)
	{
		speed = 40;
		power = 15;
	}
	else if (size == Engine::barrel_size::medium)
	{
		speed = 30;
		power = 20;
	}
	else	//barrel_size == big
	{
		speed = 25;
		power = 40;
	}



	return new Bullet_base(sf::Sprite(storage.texture_hq, texture_rect), power, speed);
}


Tank* Engine::generate_Tank(const Engine::tank_color& color, const Engine::barrel_size& size) const
{
	sf::IntRect texture_rect;
	if (color == Engine::tank_color::blue)
	{
		texture_rect = GET_SPRITE_HQ(tankBody_blue_outline);
	}
	else if (color == Engine::tank_color::green)
	{
		texture_rect = GET_SPRITE_HQ(tankBody_green_outline);
	}
	else if (color == Engine::tank_color::red)
	{
		texture_rect = GET_SPRITE_HQ(tankBody_red_outline);
	}
	else if (color == Engine::tank_color::sand)
	{
		texture_rect = GET_SPRITE_HQ(tankBody_sand_outline);
	}
	else	//color == dark
	{
		texture_rect = GET_SPRITE_HQ(tankBody_dark_outline);
	}


	return new Tank(sf::Sprite(storage.texture_hq, texture_rect), generate_Barrel(color, size));
}
