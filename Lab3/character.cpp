#include "character.hpp"
#include "directions.hpp"

Character::Character() {
    type_ = "unknown";
    name_ = "unknown";
    health_ = 1;
    strength_ = 1;
    name_of_attack_ = "attacks";
    current_environment_ = NULL;
}

Character::Character(std::string type, std::string name, int health, int strength, std::string name_of_attack, Environment * current_environment) {
    type_ = type;
    name_ = name;
    health_ = health;
    strength_ = strength;
    name_of_attack_ = name_of_attack;
    current_environment_ = current_environment;
}

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
void Character::go(int direction) {
	// TODO: Make move action
	std::cout << "Character " << name() << " goes " << direction << std::endl;
}

Environment * Character::get_environment() {
    return current_environment_;
}

void Character::enter(Environment * new_environment) {
	current_environment_ = new_environment;
}

// The character enters a fight with another character
void Character::fight(Character) {}

// The character picks up an Item
void Character::pick_up(Item) {}

// The character drops an Item
void Character::drop(Item) {}

// The character talks to another character
void Character::talk_to(Character) {}
