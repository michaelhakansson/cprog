#include "character.hpp"

namespace jonsson_league {

    Character::Character() {
        type_ = "unknown";
        name_ = "unknown";
        name_of_attack_ = "attacks";
        weight_ = 1;
        health_ = 1;
		max_health_ = 1;
        strength_ = 1;
        aggression_ = false;
        current_environment_ = NULL;
    }

    Character::Character(std::string type, std::string name, int weight, int health, int strength, std::string name_of_attack, Environment * current_environment) {
        type_ = type;
        name_ = name;
        weight_ = weight;
        name_of_attack_ = name_of_attack;
        health_ = health;
		max_health_ = health;
        strength_ = strength;
        aggression_ = false; //TODO NOT AN ARGUMENT
        current_environment_ = current_environment;
    }

    std::string Character::get_type() const {
    	return type_;
    }

    std::string Character::get_name() const {
    	return name_;
    }

    int Character::get_weight() const {
        return weight_ + inventory_.get_weight();
    }

    int Character::get_health() const {
    	return health_;
    }

    void Character::set_health(int new_health) {

		if(new_health <= max_health_){
	        health_ = new_health;
		} else {
			health_ = max_health_;
		}
    }

    int Character::get_max_health() const {
    	return max_health_;
    }

    void Character::set_max_health(int new_max_health) {
        health_ = new_max_health;
    }
    int Character::get_strength() const {
        //Count item strength
        //Count buff/debuff strength
    	return strength_;
    }

    std::string Character::get_name_of_attack() const {
    	return name_of_attack_;
    }

    // The character takes an action
    void Character::action() {}

    // The chararacter goes a step in a direction (see Enum)
    void Character::go(int direction) {
    	current_environment_ = get_environment()->get_neighbour(direction);
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

    bool Character::get_aggression(){
        return aggression_;
    }

    void Character::set_aggression(bool aggression){
        aggression_ = aggression;
    }

    bool Character::is_dead() const {
        return health_ <= 0;
    }

    Inventory* Character::get_inventory() {
        return &inventory_;
    }
}
