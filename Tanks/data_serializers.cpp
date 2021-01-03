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
		{"size", Names::size_to_string(barrel.my_size)},
	};
};


void from_json(const json& j, Tank_barrel& barrel) {
	barrel.position = sf::Vector2f(j["pos"]["x"], j["pos"]["y"]);
	barrel.angle = j["angle"];
	barrel.my_size = Names::size_to_enum(j["size"]);
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
	};
};

void from_json(const nlohmann::json& j, Tank& tank) {
	tank.tank_id = j["id"];
	tank.speed = j["speed"];
	//tank.angle = j["angle"];
	tank.set_position(sf::Vector2f(j["pos"]["x"], j["pos"]["y"]));
	tank.set_angle(j["angle"]);
	//tank.position = sf::Vector2f(j["pos"]["x"], j["pos"]["y"]);
	tank.my_color = Names::color_to_enum(j["color"]);
	from_json(j["barrel"], *(tank.barrel));
};