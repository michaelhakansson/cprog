#include "item.hpp"

std::string Item::name() const {
	return name_;
}

int Item::weight() const {
	return weight_;
}

int Item::value() const {
	return value_;
}