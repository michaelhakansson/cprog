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
	Item();
	Item(std::string name, int weight, int value);
	std::string name() const;
	int weight() const;
	int value() const;
};

#endif // ITEM_H