#ifndef WORLD_H
#define WORLD_H

#include <iostream>
#include <algorithm>
#include "environment.hpp"
#include "character.hpp"
#include "directions.hpp"

namespace jonsson_league {

	class World {
	private:
	    std::vector<Environment *> environments_;
	    Environment * starting_environment_;
	    std::vector<Character *> enemies_;
	    std::vector<Character *> local_enemies_;
	    Character * main_character_;
	    Character * current_character_;
	    bool in_combat_;
	public:
		void init();
		void describe_room();
	    bool description(std::string);
	    bool move_character(std::string);
	    bool directions(std::string args);
	    bool attack(std::string args);
	    void check_status() const;
	    Character* get_target(std::string target);
	    bool in_combat();
	    bool set_combat_flag(bool);
	    bool resolve_combat(bool aggressive);
	    void get_local_enemies(std::vector<Character *> *);

	    std::string get_string_from_enum(int num);

		Character* get_main_character() const;
		void set_main_character(Character * character);

		Character* get_current_character() const;
		void set_current_character(Character * character);

		std::vector<Character *> get_local_enemies() const;
	};

}

#endif // WORLD_H
