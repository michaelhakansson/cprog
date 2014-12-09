#include "environment.hpp"

namespace jonsson_league {

    Environment::Environment() {
        description_ = "unknown";
        type_ = "unknown";
    }

    Environment::Environment(std::vector<Item*> & items, std::vector<Environment> & neighbours, std::string description, std::string type){

        //OBS! Shared pointers?
        items_ = items;
        neighbours_ = neighbours;
        description_ = description;
        type_ = type;
    }

    std::vector<Item*> Environment::items() const {
    	return items_;
    }

    std::string Environment::item_string() const {
        std::stringstream ss;
        for (unsigned int i = 0; i < items().size(); ++i) {
            if (i > 0) {
                 ss << ", ";
            }
            ss << (items().at(i))->name();
        }
        return ss.str();
    }

    // Returns the type of environment, etc desert or indoors
    std::string Environment::type() const {
    	return type_;
    }

    // Returns a description of the environment
    std::string Environment::description() const {
    	return description_;
    }

    std::vector<Environment> Environment::neighbors() const {
    	return neighbours_;
    }

}
