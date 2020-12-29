#include "engine.h"
#include<iostream>



Engine::Engine()
{
	//pass
	//my_id = ' ';
};


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





	Tank* tank = generate_Tank(tank_color::green, barrel_size::big);

	tank->set_position(sf::Vector2f(100, 100));
	tank->set_ID(net_client->my_id);



	std::vector<Tank*> enemies;
	enemies.push_back(generate_Tank(tank_color::green, barrel_size::big));
	enemies.push_back(generate_Tank(tank_color::green, barrel_size::big));
	enemies.push_back(generate_Tank(tank_color::green, barrel_size::big));



	std::vector<Bullet*> bullets;


	std::thread net_thread_tcp(&NetClient::listenTCP, net_client);
	std::thread net_thread_udp(&NetClient::listenUDP, net_client);

	sf::Event ev;
	while (window->isOpen())
	{

		////DEBUG
		//{
		//	json jtemp = net_client->json_buffer;
		//	if (net_client->json_buffer["players"].is_null()) {
		//		std::cout << std::endl << jtemp.dump(3);
		//	}
		//	else {
		//		bool temp = false;
		//		for (int i = 0; i < jtemp["players"]; i++)
		//			if (jtemp["tanks"][i]["id"].is_null())
		//				temp = true;
		//			else
		//				//std::cout << "\nPlayer: " << jtemp["tanks"][i]["id"];
		//				;

		//		if (temp)
		//			std::cout << std::endl << jtemp.dump(3);

		//	}
		//}
		////ENDDEBUG



		//ONLINE UPDATES
		{
			json jtemp = net_client->json_buffer;
			std::cout << "odbieram: \n" << jtemp.dump(3)<<std::endl;
			bool mine_updated = false;

			if (!jtemp["tanks"].is_null())
			{
				for (int i = 0; i < jtemp["players"]; i++)
				{
					if (jtemp["tanks"][i]["id"] == this->net_client->my_id) {
						from_json(jtemp["tanks"][i], *tank);
						mine_updated = true;
					}
					else
					{
						std::cout << jtemp["tanks"].dump(3);
						if (mine_updated)
							from_json(jtemp["tanks"][i], *enemies[i - 1]);
						else
							from_json(jtemp["tanks"][i], *enemies[i]);


					}
				}
			}

		}

		net_client->setListeningMode(true);




		while (window->pollEvent(ev))
		{
			if (ev.type == sf::Event::Closed || (ev.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)))
			{
				window->close();
				net_client->setListeningMode(false);
				net_thread_tcp.detach();
				net_thread_udp.detach();
				return;
			}
		}







		control_tank(*tank);

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			if (tank->barrel->shot())
				bullets.push_back(tank->barrel->generate_bullet());


		tank->update();


		window->clear(sf::Color(13, 23, 36));

		for (auto a : bullets)
		{
			a->update();
			a->draw(*window);
		}
		tank->draw(*window);


		/*for (int i = 0; i < this->net_client->json_buffer["players"] - 1; i++)
			enemies[i]->draw(*window);*/

		window->display();




		nlohmann::json j = *tank;
		j["id"] = net_client->getID();

		std::cout << "wysylam: \n" << j.dump(3)<<std::endl;

		net_client->setListeningMode(false);
		net_client->sendDataTCP(j.dump().c_str(), j.dump().size());

		//std::cout << std::endl<< net_client->json_buffer.dump(3);
	}


	for (int i = 0; i < enemies.size(); i++) {
		delete enemies[i];
	}

	net_thread_tcp.join();
	net_thread_udp.join();

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


