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
	}
}
