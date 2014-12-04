#include "character.hpp"

std::string Character::type() const {
	return type_;
}

std::string Character::name() const {
	return name_;
}

int Character::health() const {
	return health_;
}

int Character::strength() const {
	return strength_;
}

std::string Character::name_of_attack() const {
	return name_of_attack_;
}

// The character takes an action
void Character::action() {}

// The chararacter goes a step in a direction (see Enum)
void Character::go(int) {}

// The character enters a fight with another character
void Character::fight(Character) {}

// The character picks up an Item
void Character::pick_up(Item) {}

// The character drops an Item
void Character::drop(Item) {}

// The character talks to another character
void Character::talk_to(Character) {}
