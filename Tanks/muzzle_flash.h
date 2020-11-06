#pragma once

#include <SFML/Graphics.hpp>


//klasa odpowiadajaca za sprite rozblysku wyswietlajacy sie po strzale
class Muzzle_flash : public sf::Sprite
{
	unsigned short flash_length;
	bool visibility;	//przelacznik, ktory okresli czy sprite ma byc wyswietlany
	unsigned short counter;	//liczy czas przez jaki bedzie wyswietlany sprite
public:
	Muzzle_flash(const unsigned short& length = 1) : Sprite()
	{
		flash_length = length;
		visibility = false;
		counter = 0;
		this->setScale(1, -1);
		this->setOrigin(this->getGlobalBounds().width / 2, this->getGlobalBounds().top + this->getGlobalBounds().height);
	}
	Muzzle_flash(const sf::Sprite& sprite, const unsigned short& length = 1) : Sprite(sprite)
	{
		flash_length = length;
		visibility = false;
		counter = 0;
		this->setScale(1, -1);
		this->setOrigin(this->getGlobalBounds().width / 2, this->getGlobalBounds().top + this->getGlobalBounds().height);
	}
	Muzzle_flash(const sf::Texture& texture, const sf::IntRect& rectangle, const unsigned short& length = 1) : Sprite(texture, rectangle)
	{
		flash_length = length;
		visibility = false;
		counter = 0;
		this->setScale(1, -1);
		this->setOrigin(this->getGlobalBounds().width / 2, this->getGlobalBounds().top + this->getGlobalBounds().height);
	}

	void set_flash_length(const unsigned short& length) { flash_length = length; }

	void update(const sf::Vector2f& position, const short& angle)
	{
		this->setPosition(position);
		this->setRotation(angle);
	}

	void set_visibility(const bool& visible)
	{
		visibility = visible;
		if (visibility)
			counter = flash_length;
		else
			counter = 0;
	}

	inline const bool& get_visibility() const { return visibility; }

	void draw(sf::RenderWindow& win)
	{
		if (visibility)
		{
			float temp = (float)(flash_length - counter) / flash_length;
			this->setScale((float)counter / flash_length, (float)counter / flash_length);
			this->setScale(temp, -temp);


			counter -= 1;
			if (!counter)
				visibility = false;
			win.draw(*this);
		}
	}
};