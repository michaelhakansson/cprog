#include "item.hpp"

namespace jonsson_league {

	Item::Item() {
		name_ = "Unknown";
		description_ = "An unknown item";
		weight_ = 0;
		value_ = 0;
	}

	Item::Item(std::string name, std::string description, int weight, int value) {
		name_ = name;
		description_ = description;
		weight_ = weight;
		value_ = value; 
	}


	std::string Item::get_name() const {
		return name_;
	}

	std::string Item::get_description() const {
		return description_;
	}

	int Item::weight() const {
		return weight_;
	}

	int Item::value() const {
		return value_;
	}

}
