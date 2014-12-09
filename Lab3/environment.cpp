#include "environment.hpp"

namespace jonsson_league {

    Environment::Environment() {
        description_ = "unknown";
        type_ = "unknown";
		neighbours_ = new std::vector<Environment * >(4, NULL);
		items_ = new std::vector<Item*>;
    }

	Environment::Environment(std::string description, std::string type){
		description_ = description;
		type_ = type;
		neighbours_ = new std::vector<Environment * >(4, NULL);
		items_ = new std::vector<Item*>;
	}

    Environment::Environment(std::vector<Item*> * items, std::vector<Environment*> * neighbours, std::string description, std::string type){

        //OBS! Shared pointers?
        items_ = items;
        neighbours_ = neighbours;
        description_ = description;
        type_ = type;
    }

    std::vector<Item*> * Environment::get_items() const {
    	return items_;
    }

	void Environment::set_item(Item * item){
		items_->push_back(item);
	}
    
	std::string Environment::type() const {
    	return type_;
    }

    // Returns a description of the environment
    std::string Environment::description() const {
    	return description_;
    }

	//Returns a vector of environment pointers which are the neighbours at specified directions
    std::vector<Environment *> * Environment::get_neighbours() const {
    	return neighbours_;
    }

	Environment * Environment::get_neighbour(int index) const {
		if(index < 0 || index >= (int) get_neighbours()->size()){
			return NULL;
		} else {
			return (*neighbours_)[index];
		} 
	}

	//Sets the neighbour for the specified direction
	bool Environment::set_neighbour(int index, Environment * nb) {

		if(index < 0 || index >= (int) get_neighbours()->size()){
			return false;
		}

		(*neighbours_)[index] = nb;

		return true;
	}
}
