#pragma once
#include <string>

class Config {
public:
	double distanceLimit = 5;
	int numerLimit = 1000000;
	int iterations = 4;
	int width = 600;
	int height = 600;
	int gridType = 4; //4 - square, 3 - triangle
	double gridSize = 50;
	double stickRadius = 5;
	Config();
	~Config();
	void load(std::string path);
};

