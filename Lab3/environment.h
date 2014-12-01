#include <vector>

// The number of tiles for each environment
static final int ENV_WIDTH = 10;
static final int ENV_HEIGHT = 10;

// Contains one single tile of the map
class Environment{
private:
	std::vector<Item> items_;
	std::vector<Environment&> neighbors_;
	std::String description_;
	std::String type_;
public:
	std::vector<Item>& items() const;
	std::String type() const;
	std::String description() const;
	std::vector<Environment&> & neighbors() const;
};

std::vector<Item>& items() const {
	return items_;
}

// Returns the type of environment, etc desert or indoors
std::String type() const {
	return type_;
}

// Returns a description of the environment
std::String description() const {
	return description_;
}

std::vector<Environment&> & neighbors() const {
	return neighbors_;
}

