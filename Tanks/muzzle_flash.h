#pragma once

#include <SFML/Graphics.hpp>


//flash sprite that is visible after shot
class Muzzle_flash : public sf::Sprite {
	unsigned short flash_length;
	bool visibility;	//switch that indicates wheter sprite should be displayed
	unsigned short counter;	//counts frame when sprite should be displayed
public:
	Muzzle_flash(const unsigned short& length = 1) : Sprite() {
		flash_length = length;
		visibility = false;
		counter = 0;
		this->setScale(1, -1);
		this->setOrigin(this->getGlobalBounds().width / 2, this->getGlobalBounds().top + this->getGlobalBounds().height);
	}

	Muzzle_flash(const sf::Sprite& sprite, const unsigned short& length = 1) : Sprite(sprite) {
		flash_length = length;
		visibility = false;
		counter = 0;
		this->setScale(1, -1);
		this->setOrigin(this->getGlobalBounds().width / 2, this->getGlobalBounds().top + this->getGlobalBounds().height);
	}

	Muzzle_flash(const sf::Texture& texture, const sf::IntRect& rectangle, const unsigned short& length = 1) : Sprite(texture, rectangle) {
		flash_length = length;
		visibility = false;
		counter = 0;
		this->setScale(1, -1);
		this->setOrigin(this->getGlobalBounds().width / 2, this->getGlobalBounds().top + this->getGlobalBounds().height);
	}

	void update(const sf::Vector2f& position, const short& angle) {
		this->setPosition(position);
		this->setRotation(angle);
	}

	void draw(sf::RenderWindow& win) {
		if (visibility) {
			float temp = (float)(flash_length - counter) / flash_length;
			this->setScale(temp, -temp);

			counter -= 1;
			visibility = counter;

			win.draw(*this);
		}
	}

	void set_flash_length(const unsigned short& length) { flash_length = length; }

	inline const bool& get_visibility() const { return visibility; }

	void set_visibility(const bool& visible) {
		visibility = visible;
		counter = visibility ? flash_length : 0;
	}
};