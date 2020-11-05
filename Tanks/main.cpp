#include<SFML/Graphics.hpp>
#include "engine.h"



int main()
{
	sf::RenderWindow win(sf::VideoMode(1280, 720), "Tanks");
	win.setFramerateLimit(60);

	Engine engine(win);

	engine.test();



	return 0;
}