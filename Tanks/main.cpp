#include<SFML/Graphics.hpp>
#include "engine.h"



int main()
{
	sf::RenderWindow win(sf::VideoMode(1280, 720), "Tanks");
	win.setFramerateLimit(60);

	Engine *engine = new Engine(win);

	engine->test();



	delete engine;








	return 0;
}