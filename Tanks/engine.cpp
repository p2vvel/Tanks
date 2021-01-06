#include "engine.h"
#include<iostream>

#include<nlohmann/json.hpp>

Engine::Engine()
{
	//pass
	//my_id = ' ';
}


Engine::Engine(sf::RenderWindow& win)
{
	window = &win;
	net_client = new NetClient(PORT, ADDRESS);
}


Engine::~Engine()
{
	delete net_client;
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
	if (!net_client->succesfullConnection())
		return;


	sf::IntRect a = GET_SPRITE_HQ(tracksSmall);
	a.height = 6;

	Tank* tank = generate_random_Tank();//generate_Tank(tank_color::green, barrel_size::big);

	tank->barrel->bullet_pattern->set_shooter_ID(net_client->my_id);	//sets default id for newly created bullets

	tank->set_position(sf::Vector2f(100, 100));
	tank->set_ID(net_client->my_id);

	std::vector<Tank*> enemies;

	std::vector<Bullet*> bullets;





	sf::Event ev;
	while (window->isOpen())
	{
		while (window->pollEvent(ev))
		{
			if (ev.type == sf::Event::Closed || (ev.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)))
			{
				window->close();
				for (int i = 0; i < enemies.size(); i++)
					delete enemies[i];
				return;
			}
		}





		//Control
		control_tank(*tank);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			if (tank->health > 0 && tank->barrel->shot()) 
				bullets.push_back(tank->barrel->generate_bullet());
			

		tank->update();



		//Send
		nlohmann::json j = *tank;
		if (tank->barrel->shot_recently)
			to_json(j["shot"], (*bullets[bullets.size() - 1]));
		net_client->sendDataTCP(j.dump().c_str(), j.dump().size());



		//Receive data
		net_client->readDataTCP();

		//update data
		nlohmann::json* game_data = (net_client->json_buffer);
		nlohmann::json* game_data_old = (net_client->json_buffer_old);



		//##############
		//Players update:
		//##############

		//Reaction for new player joining or enemy disconnect
		if ((*game_data)["players"] - 1 != enemies.size()) {
			if ((*game_data)["players"] - 1 < enemies.size()) {
				//Delete player
				std::cout << "\nPlayer joined";// << std::endl << game_data->dump(3);
				do {
					delete enemies[enemies.size() - 1];	//delete object
					enemies.pop_back();	//pop pointer
				} while ((*game_data)["players"] - 1 != enemies.size());
			}
			else {
				//Add new player
				std::cout << "\nPlayer left";// << std::endl << game_data->dump(3);
				do
				{
					enemies.push_back(generate_Tank(Names::tank_color::green, Names::barrel_size::big));
				} while ((*game_data)["players"] - 1 != enemies.size());
			}
		}

		bool mine_updated = false;
		for (int i = 0; i < (*game_data)["players"]; i++)
		{
			if ((*game_data)["tanks"][i]["id"] == net_client->my_id) {
				from_json((*game_data)["tanks"][i], *tank);
				mine_updated = true;
			}
			else {
				from_json((*game_data)["tanks"][i], *enemies[(mine_updated ? i - 1 : i)]);
				enemies[(mine_updated ? i - 1 : i)]->update();
			}
		}



		//##############
		//Bullets update:
		//##############


		if ((*game_data)["bullets"].size() != bullets.size()) {
			if ((*game_data)["bullets"].size() < bullets.size()) {
				do {
					delete bullets[bullets.size() - 1];	//delete object
					bullets.pop_back();	//pop pointer
				} while ((*game_data)["bullets"].size() != bullets.size());
			}
			else {
				do
				{
					bullets.push_back(tank->barrel->generate_bullet());
				} while ((*game_data)["bullets"].size() != bullets.size());
			}
		}

		for (int i = 0; i < (*game_data)["bullets"].size(); i++)
			from_json((*game_data)["bullets"][i], *bullets[i]);


		//SEND
		//LISTEN
		//UPDATE



		tank->update();


		window->clear(sf::Color(13, 23, 36));
		for (auto a : bullets)
			a->draw(*window);

		for (auto t : enemies)
			t->draw_skidmarks(*window);
		tank->draw_skidmarks(*window);

		for (auto t : enemies)
			t->draw(*window);


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
}


