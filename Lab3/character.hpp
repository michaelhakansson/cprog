#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include "environment.hpp"
#include "item.hpp"
#include <iostream>

// Base class for all characters, and NPCs
class Character {
private:
	std::string type_;
	std::string name_;
	int health_;
	int strength_;
	std::string name_of_attack_;
	Environment * current_environment_;
public:
	Character();

	Character(std::string type, std::string name, int health, int strength, std::string name_of_attack, Environment * current_environment);

	// Returns what type the character is eg Ogre
	std::string type() const;

	// Returns the name of the character eg Gandalf
	std::string name() const;

	// Returns the HP of the character
	int health() const;

	// Returns the strength of the 
	int strength() const;

	// Returns the name of the attack that this character has
	std::string name_of_attack() const;

	void action();
	void go(int);
	Environment * get_environment();
	void enter(Environment *);
	void fight(Character);
	void pick_up(Item);
	void drop(Item);
	void talk_to(Character);
};

#endif // CHARACTER_H
