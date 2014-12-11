#ifndef INVENTORY_H
#define INVENTORY_H

#include <vector>
#include <string>
#include <algorithm>
#include "item.hpp"

namespace jonsson_league {

	// Contains one single tile of the map
	class Inventory{
	private:
		int slot_limit_;
		int weight_limit_;
		std::vector<Item*> * items_;
	public:
		Inventory();
		Inventory(int num_slots, int max_weight);
		int get_slot_limit() const;
		int get_weight_limit() const;
		bool add_item(Item* item);
		std::vector<Item*> * get_items() const;
		void remove_item(Item* item);
		int get_weight() const;
		int get_number_of_items() const;
	};

}

#endif // INVENTORY_H
