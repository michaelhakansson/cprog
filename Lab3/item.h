#include <string>

// Base class for all items
class Item {
private:
	std::String name_;
	int weight_;
	int value_;
public:
	std::String name() const;
	int weight() const;
	int value() const;
};


std::String name() const {
	return name_;
}

int weight() const {
	return weight_;
}

int value() const {
	return value_;
}
