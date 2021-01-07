#pragma once
#include <nlohmann/json.hpp>



using nlohmann::json;


class Tank_barrel;
class Tank;
class Bullet;


void to_json(nlohmann::json& j, const Tank_barrel& barrel);
void from_json(const nlohmann::json& j, Tank_barrel& barrel);

void to_json(nlohmann::json& j, const Tank& tank);
void from_json(const nlohmann::json& j, Tank& tank);

void to_json(nlohmann::json& j, const Bullet& bullet);
void from_json(const nlohmann::json& j, Bullet& bullet);
