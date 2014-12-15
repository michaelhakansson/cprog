#include "container.hpp"

namespace jonsson_league {

	Container::Container() {
		slot_limit_ = 1;
		weight_limit_ = 1;
		items_ = new std::vector<Item*>;
	}

	Container::Container(int num_slots, int max_weight) {
		slot_limit_ = num_slots;
		weight_limit_ = max_weight;
		items_ = new std::vector<Item*>;
	}

	bool Container::contains(Item* item) {
		if ( std::find(items_->begin(), items_->end(), item)  != items_->end() ) {
			return true;
		}
		return false;
	}

	int Container::get_slot_limit() const {
		return slot_limit_;
	}

	int Container::get_weight_limit() const {
		return weight_limit_;
	}

	int Container::get_weight() const {
		int total_weight = 0;
		for (Item const* item : *get_items()) {
			total_weight += item->get_weight();
		}
		return total_weight;
	}

	bool Container::add_item(Item* item) {
		if (get_number_of_items() < get_slot_limit() && get_weight_limit() >= get_weight()+item->get_weight()) {
			items_->push_back(item);			
			return true;
		}
		return false;
	}

	// TODO: Only removes the item from the container item list. Does NOT destroy
	// the item itself. Maybe implement functionality to move item to other container
	// or something for characters to be able to drop items in an environment.
	bool Container::remove_item(Item* item) {
		if ( contains(item) ) {
			items_->erase(std::find(items_->begin(), items_->end(), item));
			return true;
		}
		return false;
	}

	std::vector<Item*> * Container::get_items() const { 
		return items_;
	}

	int Container::get_number_of_items() const {
		return get_items()->size();
	}

}
