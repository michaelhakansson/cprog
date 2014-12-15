#include "inventory.hpp"

namespace jonsson_league {

	Inventory::Inventory() {
		slot_limit_ = 1;
		weight_limit_ = 1;
		items_ = new std::vector<Item*>;
	}

	Inventory::Inventory(int num_slots, int max_weight) {
		slot_limit_ = num_slots;
		weight_limit_ = max_weight;
		items_ = new std::vector<Item*>;
	}

	int Inventory::get_slot_limit() const {
		return slot_limit_;
	}

	int Inventory::get_weight_limit() const {
		return weight_limit_;
	}

	int Inventory::get_weight() const {
		int total_weight = 0;
		for (Item const* item : *get_items()) {
			total_weight += item->get_weight();
		}
		return total_weight;
	}

	bool Inventory::add_item(Item* item) {
		if (get_number_of_items() < get_slot_limit() && get_weight_limit() >= get_weight()+item->get_weight()) {
			items_->push_back(item);			
			return true;
		}
		return false;
	}

	bool Inventory::remove_item(Item* item) {
		std::vector<Item*>::iterator it = std::find(items_->begin(), items_->end(), item);
		if ( it != items_->end() ) {
			items_->erase(it);
			return true;
		}
		// items_->erase(std::find(items_->begin(), items_->end(), item));
		return false;
	}

	std::vector<Item*> * Inventory::get_items() const { 
		return items_;
	}

	int Inventory::get_number_of_items() const {
		return get_items()->size();
	}

}
