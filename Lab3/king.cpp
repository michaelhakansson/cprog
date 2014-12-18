#include "king.hpp"

namespace jonsson_league {

	King::King() : Character() {}

	King::King(std::string type, std::string name, int health, int strength, std::string name_of_attack, Environment * current_environment)
		: Character(type, name, health, strength, name_of_attack, current_environment) {}

	void King::say() const {
		std::cout << get_name() << ": ";
		std::cout << "Well, thief! I smell you, I hear your breath, I feel your air. Where are you?" << std::endl;
	}

}
