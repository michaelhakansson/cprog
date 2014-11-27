//The number of tiles for each environment
static final int ENV_WIDTH = 10;
static final int ENV_HEIGHT = 10;

//Contains one single tile of the map
class Environment{
public:
	std::String type();
	std::String description();
	int exits();
};

//Returns the type of environment, etc desert or indoors
std::String type() {
	return type;
}

//Returns a description of the environment
std::String description() {
	return description;
}

//Returns what available exits exist for this environment
int exits() {
	return exits;
}

//TODO egenskap
