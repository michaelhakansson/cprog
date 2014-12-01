#ifndef ITEM_H
#define ITEM_H

#include <string>

// Base class for all items
class Item {
private:
	std::string name_;
	int weight_;
	int value_;
public:
	std::string name() const;
	int weight() const;
	int value() const;
};


std::string Item::name() const {
	return name_;
}

int Item::weight() const {
	return weight_;
}

int Item::value() const {
	return value_;
}

#endif // ITEM_H