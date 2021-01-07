#pragma once
#include <SFML/Graphics.hpp>
#include<sstream>
#include<iostream>
#include<string>



class Info : public sf::Text{
public:
	enum class screen_side{ left, right};
private:
	Info::screen_side my_side;
public:
	std::ostringstream buffer;
	Info(const Info::screen_side& side = Info::screen_side::left) {
		my_side = side;
		if (my_side == Info::screen_side::right)
			this->setOrigin(this->getGlobalBounds().width, 0);
		else this->setOrigin(0, 0);
	};

	void setSide(const Info::screen_side& side = Info::screen_side::left) { my_side = side; }

	template <typename T>
	friend Info& operator<<(Info& info,  T t);
	
	const std::string get_buffer() const {
		return this->buffer.str();
	}

	void clear_buffer() {
		this->buffer.str("");
		this->buffer.clear();
	}

	void draw(sf::RenderWindow& win) {
		if (my_side == Info::screen_side::right)
			this->setOrigin(this->getGlobalBounds().width, 0);
		else this->setOrigin(0, 0);

		win.draw(*this);
	}
};

template <typename T>
Info& operator<<(Info& info, T t) {
	(info.buffer) << t;
	info.setString(info.buffer.str());
	return info;
}