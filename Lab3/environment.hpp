#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <vector>
#include "item.hpp"

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

#endif // ENVIRONMENT_H