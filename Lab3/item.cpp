#include "item.hpp"

namespace jonsson_league {

	Item::Item() {
		name_ = "unknown",
		weight_ = 0;
		value_ = 0;
	}

	Item::Item(std::string name, int weight, int value) {
		name_ = name;
		weight_ = weight;
		value_ = value; 
	}


	std::string Item::name() const {
		return name_;
	}

	int Item::weight() const {
		return weight_;
	}

	int Item::value() const {
		return value_;
	}

}
