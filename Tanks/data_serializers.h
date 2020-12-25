#pragma once
#include <nlohmann/json.hpp>
#include "tank_barrel.h"

using nlohmann::json;

class Tank_barrel;
class Tank;


void to_json(nlohmann::json& j, const Tank_barrel& barrel);
void from_json(const nlohmann::json& j, Tank_barrel& barrel);


void to_json(nlohmann::json& j, const Tank& tank);
void from_json(const nlohmann::json& j, Tank& tank);