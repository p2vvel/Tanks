#include<SFML/Graphics.hpp>
#include "engine.h"

#include "info.h"
#include "storage.h"
#include<cstdlib>

#define ADDRESS "127.0.0.1"
#define PORT 3003


int main(int argc, char* argv[])
{
	sf::RenderWindow win(sf::VideoMode(1280, 720), "Tanks");
	win.setFramerateLimit(60);

	const int port = (argc >= 2 ? atoi(argv[1]) : 3003);
	const char* address = (argc >= 3 ? argv[2] : "127.0.0.1");

	std::cout << "Trying to connect to server at " << address << ":" << port << std::endl;

	Engine *engine = new Engine(win, (argc >= 2 ?  atoi(argv[1]) : 3003), (argc >= 3 ? argv[2] : "127.0.0.1"));
	engine->game();
	delete engine;




	return 0;
}