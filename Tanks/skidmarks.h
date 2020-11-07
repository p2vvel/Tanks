#pragma once


#include <SFML/Graphics.hpp>
#include<cmath>

#define DISTANCE_BETWEEN_VECTORS(a, b) (sqrtf(((a.x - b.x)*(a.x - b.x)) + ((a.y - b.y)* (a.y - b.y))))


//To samo co sf::Sprite, ale z przelacznikiem ktory pozwala okreslic, czy ma byc wyswietlany
class SwitchablSprite : public sf::Sprite
{
	bool visibility;
public:
	SwitchablSprite() : Sprite() {}
	SwitchablSprite(const sf::Texture& texture, const sf::IntRect& rectangle) : Sprite(texture, rectangle) { visibility = false; }
	SwitchablSprite(const sf::Sprite& sprite) : Sprite(sprite) { visibility = false; }
	void draw(sf::RenderWindow& window) { if (visibility) window.draw(*this); }
	void set_visible(const bool& val) { visibility = val; }
	const bool& get_visible() const { return visibility; }
};





class Skidmarks
{
	sf::Sprite* pattern;	//wzor spriteu wykorzystywanego do rysowania sladow
	unsigned short size;	//ilosc sladow ktore moga byc pozostawione
	unsigned short current_index;
	unsigned short distance;	//odleglosc pomiedzy sladami;

	SwitchablSprite* tab;
public:
	Skidmarks(sf::Sprite* new_pattern, const unsigned short& new_size, const unsigned short& new_distance)
	{
		pattern = new_pattern;
		size = new_size;
		distance = new_distance;

		pattern->setOrigin(pattern->getGlobalBounds().width / 2, pattern->getGlobalBounds().height / 2);

		tab = new SwitchablSprite[size];
		for (int i = 0; i < size; i++)
		{
			tab[i] = SwitchablSprite(*pattern);
		}
	}


	~Skidmarks()
	{
		delete[] tab;
		delete pattern;
	}


	void update(sf::Vector2f& skidmark_pos, const short& skidmark_angle)	//zamienia ostatni slad za czolgiem na nowy slad znajdujacy sie zaraz pod czolgiem
	{

		short i = current_index;
		do
		{
			i = (i - 1 + size) % size;
		} while (!tab[i].get_visible() && i != current_index);


		if (DISTANCE_BETWEEN_VECTORS(skidmark_pos, tab[i].getPosition()) >= distance)
		{
			tab[current_index].set_visible(true);
			tab[current_index].setRotation(skidmark_angle);
			tab[current_index].setPosition(skidmark_pos);
			tab[current_index].setScale(1, 1);	//resetuje skale, ktora wczesniej byla zmieniona zeby stworzyc efekt zanikania sladow
		}
		else
		{
			tab[current_index].set_visible(false);//*/
		}

		current_index = (current_index + 1) % size;	//przechodzi po wszystkich sladach w kolko



		for (int i = 1; i < (size / 4); i++)	//ostatnie slady staja sie coraz wezsze stwarzajac wrazenie zanikania
		{
			tab[(current_index + i) % size].setScale(1, i / 10.0);
		}
	}


	void draw(sf::RenderWindow& win)
	{
		for (int i = 0; i < size; i++)
			tab[i].draw(win);//win.draw(tab[i]);
	}
};