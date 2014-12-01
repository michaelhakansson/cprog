#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <vector>
#include "item.h"

// Contains one single tile of the map
class Environment{
private:
	std::vector<Item> items_;
	std::vector<Environment> neighbors_;
	std::string description_;
	std::string type_;
public:
	std::vector<Item> items() const;
	std::string type() const;
	std::string description() const;
	std::vector<Environment> neighbors() const;
};

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

#endif // ENVIRONMENT_H