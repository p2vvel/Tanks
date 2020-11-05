#include "engine.h"
#include<iostream>



Engine::Engine()
{
	//pass
};


Engine::Engine(sf::RenderWindow& win)
{
	window = &win;
}


Engine::~Engine()
{
	//pass
};


const sf::Vector2f& Engine::calculate_vector(const float& distance_, const short& angle_)
{
	float rad_angle = (3.1415926536 / 180) * (angle_);	//kat w radianach - w takiej postaci funkcje z cmath je przyjmuja

	float y = distance_ * -cos(rad_angle);
	float x = distance_ * sin(rad_angle);

	return sf::Vector2f(x, y);
}



void Engine::test()
{

	sf::IntRect a = GET_SPRITE_HQ(tracksSmall);
	a.height = 6;



	Tank* tank = new Tank(
		sf::Sprite(storage.texture_hq, GET_SPRITE_HQ(tankBody_blue_outline)), new Tank_barrel(sf::Sprite(storage.texture_hq, GET_SPRITE_HQ(tankBlue_barrel2_outline)),sf::seconds(0.8)));


	tank->set_position(sf::Vector2f(100, 100));




	sf::Event ev;
	while (window->isOpen())
	{
		while (window->pollEvent(ev))
		{
			if (ev.type == sf::Event::Closed || (ev.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)))
				window->close();
		}







		control_tank(*tank);

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			if (tank->barrel->shot())
				std::cout << "SHOT";

		tank->update();


		window->clear(sf::Color(13, 23, 36));

		
		tank->draw(*window);




		window->display();
	}

}


short Engine::mouse_aim_angle(const Tank_barrel& barrel)
{
	sf::Vector2i mouse_position = sf::Vector2i(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y);
	sf::Vector2f barrel_center = barrel.barrel_body->getPosition();

	short barrel_angle = (short)((atan2(-mouse_position.y + barrel_center.y, -mouse_position.x + barrel_center.x) * 180 / 3.14) + 270) % 360;

	return barrel_angle;
}


void Engine::control_tank(Tank& tank)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		tank.accelerate();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		tank.decelerate();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		tank.turn_left();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		tank.turn_right();

	tank.barrel->set_angle(Engine::mouse_aim_angle(*tank.barrel));

	/*if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		tank.barrel->shot();//*/
}


