#include "data_serializers.h"
#include "tank_barrel.h";
#include "tank.h"
#include "storage.h"
#include "bullet.h"



using nlohmann::json;


void to_json(json& j, const Tank_barrel& barrel) {
	j = {
		{"pos", {
			{"x", barrel.position.x},
			{"y", barrel.position.x}
		}},
		{"angle", barrel.angle},
		{"size", Names::size_to_string(barrel.my_size)},
		{"color", Names::color_to_string(barrel.my_color)},
	};
};


void from_json(const json& j, Tank_barrel& barrel) {
	barrel.position = sf::Vector2f(j["pos"]["x"], j["pos"]["y"]);
	barrel.angle = j["angle"];
	barrel.my_size = Names::size_to_enum(j["size"]);
	barrel.my_color = Names::color_to_enum(j["color"]);
	barrel.barrel_body->setTextureRect(Storage::get_BarrelRect(barrel.my_color, barrel.my_size));
};


void to_json(nlohmann::json& j, const Tank& tank) {
	j = {
		{"id", tank.tank_id},
		{"speed", tank.speed},
		{"angle", tank.angle},
		{"pos", {
			{"x", tank.position.x},
			{"y", tank.position.y},
		}},
		{"barrel", *(tank.barrel)},
		{"color", Names::color_to_string(tank.my_color)},
		{"health", tank.health},
		{"score", tank.score},
		{"cycle", tank.cycle},
	};
};


void from_json(const nlohmann::json& j, Tank& tank) {
	tank.tank_id = j["id"];
	tank.speed = j["speed"];
	tank.set_position(sf::Vector2f(j["pos"]["x"], j["pos"]["y"]));
	tank.angle = j["angle"];
	tank.set_angle(tank.angle);
	tank.my_color = Names::color_to_enum(j["color"]);
	from_json(j["barrel"], *(tank.barrel));
	tank.tank_body->setTextureRect(Storage::get_TankRect(tank.my_color));
	tank.score = j["score"];

	if (tank.health != j["health"] && j["health"] != 0) {
		tank.tank_body->setScale(1.05, -1.1);	//small "animation" that shows player that his tank was hit
		tank.barrel->barrel_body->setScale(1.05, -1.1);		//small "animation" that shows player that his tank was hit
	}

	tank.health = j["health"];
	if (tank.health > 0)
		tank.cycle = 0;
	else
		tank.cycle = j["cycle"];

	if (j["shot"] == true)
		tank.barrel->muzzle_flash->set_visibility(true);
};


void to_json(nlohmann::json& j, const Bullet& bullet) {
	sf::Vector2f pos = bullet.bullet_body->getPosition();
	j = {
		{"shooter", bullet.shooter_id},
		{"power", bullet.power},
		{"speed", bullet.speed},
		{"angle", bullet.angle},
		{"pos", {
			{"x", pos.x},
			{"y", pos.y},
		}},
		{"color", Names::color_to_string(bullet.my_color)},
		{"size", Names::size_to_string(bullet.my_size)}
	};
};


void from_json(const nlohmann::json& j, Bullet& bullet) {
	bullet.shooter_id = j["shooter"];
	bullet.power = j["power"];
	bullet.speed = j["speed"];
	bullet.angle = j["angle"];
	bullet.my_color = Names::color_to_enum(j["color"]);
	bullet.my_size = Names::size_to_enum(j["size"]);
	bullet.bullet_body->setTextureRect(Storage::get_BulletRect(bullet.my_color, bullet.my_size));
	bullet.bullet_body->setPosition(j["pos"]["x"], j["pos"]["y"]);
	bullet.bullet_body->setRotation(bullet.angle);
};