#include "data_serializers.h"
#include "tank_barrel.h";
#include "tank.h"

//#include<cmath>

using nlohmann::json;



void to_json(json& j, const Tank_barrel& barrel) {
	j = {
		{"pos", {
			{"x", barrel.position.x},
			{"y", barrel.position.x}
		}},
		{"angle", barrel.angle},
	};
};


void from_json(const json& j, Tank_barrel& barrel) {
	barrel.position = sf::Vector2f(j["pos"]["x"], j["pos"]["y"]);
	barrel.angle = j["angle"];
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
	};
};

void from_json(const nlohmann::json& j, Tank& tank) {
	tank.tank_id = j["id"];
	tank.speed = j["speed"];
	//tank.angle = j["angle"];
	tank.set_position(sf::Vector2f(j["pos"]["x"], j["pos"]["y"]));
	tank.set_angle(j["angle"]);
	//tank.position = sf::Vector2f(j["pos"]["x"], j["pos"]["y"]);
	from_json(j["barrel"], *(tank.barrel));
};