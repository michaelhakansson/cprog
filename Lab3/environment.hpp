#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <vector>
#include <string>
#include <sstream>

#include "item.hpp"

namespace jonsson_league {

	// Contains one single tile of the map
	class Environment{
	private:
		std::vector<Item*> * items_;
		std::vector<Environment *> * neighbours_;
		std::string description_;
		std::string type_;
	public:
	    Environment();
		Environment(std::string, std::string);
	    Environment(std::vector<Item*> * items, std::vector<Environment*> * neighbours, std::string description, std::string type);
		std::vector<Item*> * get_items() const;
		void set_item(Item *);
		std::string item_string() const;
		std::string type() const;
		std::string description() const;
		std::vector<Environment *> * get_neighbours() const;
		Environment * get_neighbour(int) const;
		bool set_neighbour(int, Environment *);
	};

}

#endif // ENVIRONMENT_H
