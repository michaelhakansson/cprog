#include "character.h"

std::String type() const {
	return type_;
}

std::String name() const {
	return name_;
}

int health() const {
	return health_;
}

int strength() const {
	return strength_;
}

std::String name_of_attack() const {
	return name_of_attack_;
}

// The character takes an action
void action() {}

// The chararacter goes a step in a direction
void go(direction) {}

// The character enters a fight with another character
void fight(Character) {}

// The character picks up an object
void pick_up(Object) {}

// The character drops an object
void drop(Object) {}

// The character talks to another character
void talk_to(Character) {}
