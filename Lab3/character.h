#include <string>

// Base class for all characters, and NPCs
class Character {
private:
	std::String type_;
	std::String name_;
	int health_;
	int strength_;
	std::String name_of_attack_;
public:
	// Returns what type the character is eg Ogre
	std::String type() const;

	// Returns the name of the character eg Gandalf
	std::String name() const;

	// Returns the HP of the character
	int health() const;

	// Returns the strength of the 
	int strength() const;

	// Returns the name of the attack that this character has
	std::String name_of_attack() const;

	void action();
	void go(direction);
	void fight(Character);
	void pick_up(Object);
	void drop(Object);
	void talk_to(Character)
};
