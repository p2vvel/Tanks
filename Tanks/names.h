#pragma once
#include<string>

namespace Names {
	enum class tank_color { blue, dark, green, red, sand };
	enum class barrel_size { big, medium, small };

	inline Names::tank_color color_to_enum(const std::string& str) {
		if (str == "blue")
			return Names::tank_color::blue;
		else if (str == "dark")
			return Names::tank_color::dark;
		else if (str == "red")
			return Names::tank_color::red;
		else if (str == "sand")
			return Names::tank_color::sand;
		else	// if (str == "green")
			return Names::tank_color::green;
	};

	inline std::string color_to_string(const Names::tank_color& color) {
		switch (color) {
		case  Names::tank_color::blue:
			return "blue";
		case  Names::tank_color::dark:
			return "dark";
		case  Names::tank_color::red:
			return "red";
		case  Names::tank_color::sand:
			return "sand";
		default:	//case  Names::tank_color::green:
			return "green";
		};
	}

	inline Names::barrel_size size_to_enum(const std::string& str) {
		if (str == "small")
			return Names::barrel_size::small;
		else if (str == "medium")
			return Names::barrel_size::medium;
		else	// if (str == "big")
			return Names::barrel_size::big;
	}

	inline std::string size_to_string(const Names::barrel_size& size) {
		switch (size) {
		case  Names::barrel_size::small:
			return "small";
		case  Names::barrel_size::medium:
			return "medium";
		default:	//case  Names::barrel_size::big
			return "big";
		};
	}
};
