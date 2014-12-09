#ifndef INVENTORY_H
#define INVENTORY_H

#include <vector>
#include <string>
#include "item.hpp"

namespace jonsson_league {

	// Contains one single tile of the map
	class Inventory{
	private:
		// TODO: Shared pointers instead
		std::vector<Item*> * items_;
	public:
		void add_item();
		void remove_item();
	};

}

#endif // INVENTORY_H
