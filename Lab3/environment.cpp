#include "environment.hpp"

std::vector<Item> Environment::items() const {
	return items_;
}

// Returns the type of environment, etc desert or indoors
std::string Environment::type() const {
	return type_;
}

// Returns a description of the environment
std::string Environment::description() const {
	return description_;
}

std::vector<Environment> Environment::neighbors() const {
	return neighbors_;
}