#pragma once
#include <SFML/Graphics.hpp>
#include "geometry.h"
#include "Color.h"
#include "Fragment.h"
#include "Config.h"

class Draw {
public:

	sf::RenderWindow* window;
	std::vector<Vector2d> points;
	std::vector<bool> types;
	bool state = 0;
	bool type = 1;
	Config config;
	Draw();
	~Draw();
	void step();
	void line(Vector2d a, Vector2d b, Color c);
	void line(std::vector<Vector2d> f, Color c);
	void draw(Fragment fragment);
	void draw();
};

