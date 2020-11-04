#include<iostream>
#include<SFML/Graphics.hpp>


int main() {
	sf::RenderWindow win(sf::VideoMode(1280, 720), "Tanks LPG");
	win.setFramerateLimit(60);

	while (win.isOpen()) {
		sf::Event ev;
		if (win.pollEvent(ev)) {
			if (ev.type == sf::Event::Closed)
				win.close();
		}

		win.clear(sf::Color(13, 23, 36));
		win.display();
	}

	return 0;
}