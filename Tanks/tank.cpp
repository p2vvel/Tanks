#include "tank.h"

#include "tank_barrel.h"

#include <cmath>

#include<iostream>

#include "engine.h"


#define DEATH_CYCLE_LENGTH 3

Tank::Tank(const sf::Sprite& tank_sprite, const Names::tank_color& color, Tank_barrel* new_barrel, Skidmarks* marks) {
	tank_body = new sf::Sprite(tank_sprite);
	tank_body->setOrigin(tank_body->getGlobalBounds().width / 2, tank_body->getGlobalBounds().height / 2);
	tank_body->setScale(1, -1);	//Ustawienie, ktore powoduje ze korpus czolgu jest zwrocony domyslnie do gornej krawedzi okna (traktuje ta pozycje jako kat 0 stopni - w przypadku lufy tak samo)
	barrel = new_barrel;
	angle = 0;
	speed = 0;

	my_color = color;

	handling = 0.6;

	skidmarks = marks;

	tank_id = -1;
	score = 0;
	health = 100;

	cycle = 0;
}


Tank::~Tank() {
	delete barrel;
	delete tank_body;
}


void Tank::set_position(const sf::Vector2f& new_pos) {
	position = new_pos;
	barrel->set_position(new_pos);
	tank_body->setPosition(new_pos);
}


void Tank::change_speed(const float& new_speed) {
	speed = new_speed;
}


void Tank::add_speed(const float& new_speed) {
	if ((speed + new_speed) <= MAX_SPEED && (speed + new_speed) >= -MAX_REVERSE_SPEED)
		speed += new_speed;
}

void Tank::set_angle(const short& new_angle) {
	angle = (new_angle % 360) > 0 ? (new_angle % 360) : (360 + (new_angle % 360));
}


void Tank::add_angle(const short& new_angle) {
	short temp = new_angle - (new_angle > 0 ? abs(handling * (speed / max_speed) * new_angle) : -abs(handling * (speed / max_speed) * new_angle));

	angle = (angle + temp) % 360;
	if (angle < 0)
		angle = 360 + angle;
	angle += new_angle;
}


void Tank::update() {
	if (health <= 0)
		return;

	movement_vector = Engine::calculate_vector(speed, angle);
	position += movement_vector;

	tank_body->setPosition(position);
	tank_body->setRotation(angle);

	barrel->set_position(position);
	barrel->update();

	if (skidmarks != nullptr)
		skidmarks->update(this->position, this->angle);	//zostawia slady po gasienicach - opcjonalne


	if (speed >= IDLE_SPEED_LOSS || speed <= -IDLE_SPEED_LOSS)
		speed = (speed > 0 ? speed - IDLE_SPEED_LOSS : speed + IDLE_SPEED_LOSS);
	else
		speed = 0;//*/
}


void Tank::draw_skidmarks(sf::RenderWindow& win) {
	if (health > 0 && skidmarks != nullptr)
		skidmarks->draw(win);
}


void Tank::draw(sf::RenderWindow& win, const bool& draw_skidmarks) {
	if (health <= 0) {
		skidmarks->clear_all_marks();
		control_death_cycles();
		barrel->shot_recently = false;	//have to reset that variable manually because barrels draw function isnt called if player is dead
		if (cycle <= DEATH_CYCLE_LENGTH * 5)
			win.draw(*tank_body);
	}
	else {

		win.draw(*tank_body);
		barrel->draw(win);
		tank_body->setScale(1, -1);	//restore sprite after being shot 
	}
}


void Tank::control_death_cycles() {
	if (health > 0)
		return;

	if (cycle < DEATH_CYCLE_LENGTH * 1) {
		tank_body->setTextureRect(Storage::sprite_rects_hq[Storage::sprite_index::explosion1]);
	}
	else if (cycle < DEATH_CYCLE_LENGTH * 2) {
		tank_body->setTextureRect(Storage::sprite_rects_hq[Storage::sprite_index::explosion2]);
	}
	else if (cycle < DEATH_CYCLE_LENGTH * 3) {
		tank_body->setTextureRect(Storage::sprite_rects_hq[Storage::sprite_index::explosion3]);
	}
	else if (cycle < DEATH_CYCLE_LENGTH * 4) {
		tank_body->setTextureRect(Storage::sprite_rects_hq[Storage::sprite_index::explosion4]);
	}
	else if (cycle < DEATH_CYCLE_LENGTH * 5) {
		tank_body->setTextureRect(Storage::sprite_rects_hq[Storage::sprite_index::explosion5]);
	}

	cycle += 1;
}



void Tank::accelerate() {
	if (speed >= 0 && (speed + ACCELERATION_SPEED) <= MAX_SPEED)	//normalne przyspieszanie od 0
		speed += ACCELERATION_SPEED;
	else if (speed < 0 && (speed + DECELERATION_SPEED) <= MAX_SPEED)  //hamowanie jazdy do tylu
		speed += DECELERATION_SPEED;
}


void Tank::decelerate() {
	//hamowanie jazdy do przodu i jazda do tylu, czolg przyspiesza 2 razy szybciej do tylu, ale za to osiaga mniejsza predkosc - 80% tego co do przodu
	if ((speed - DECELERATION_SPEED) >= -MAX_REVERSE_SPEED)
		speed -= DECELERATION_SPEED;
}


void Tank::turn_left() {
	this->add_angle(-TURN_ANGLE);
}


void Tank::turn_right() {
	this->add_angle(TURN_ANGLE);
}

