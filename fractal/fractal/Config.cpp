#include "Config.h"
#include <fstream>

Config::Config(){
}

Config::~Config(){
}

void Config::load(std::string path) {
	std::ifstream file(path);
	while (file) {
		std::string param;
		file >> param;
		if (param == "DISTANCE_LIMIT") {
			file >> distanceLimit;
		}
		if (param == "NUMBER_LIMIT") {
			file >> numerLimit;
		}
		if (param == "ITERATIONS") {
			file >> iterations;
		}
		if (param == "HEIGHT") {
			file >> height;
		}
		if (param == "WIDTH") {
			file >> width;
		}
		if (param == "GRID_SIZE") {
			file >> gridSize;
		}
		if (param == "GRID") {
			file >> gridType;
		}
		if (param == "GRID_STICK_RADIUS") {
			file >> stickRadius;
		}
	}
}
