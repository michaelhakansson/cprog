#include <string>

//Base class for all characters, and NPCs
class Character {
private:
	std::String type_;
	std::String name_;
	std::String health_;
public:
	std::String type() const;
	std::String name() const;
	std::String health() const;

	void action();
	void go(direction);
	void fight(Character);
	void pick_up(Object);
	void drop(Object);
	void talk_to(Character)
};

//Returns what type the character is eg Ogre
std::String type() const {
	return type_;
}

//Returns the name of the character eg Gandalf
std::String name() const {
	return name_;
}

//Returns the HP of the character
std::String health() const {
	return health_;
}

//The character takes an action
void action() {}

//The chararacter goes a step in a direction
void go(direction) {}

//The character enters a fight with another character
void fight(Character) {}

//The character picks up an object
void pick_up(Object) {}

//The character drops an object
void drop(Object) {}

//The character talks to another character
void talk_to(Character) {}