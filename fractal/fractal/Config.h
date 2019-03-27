#pragma once
#include <string>

class Config {
public:
	double distanceLimit = 5;
	int numerLimit = 1000000;
	int iterations = 4;
	int width = 600;
	int height = 600;
	Config();
	~Config();
	void load(std::string path);
};

