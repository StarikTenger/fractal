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
	std::vector<int> types;
	std::vector<Vector2d> grid;
	bool state = 0;
	int stop = 0;
	int type = 1;
	Vector2d mouse;
	Config config;
	Draw();
	~Draw();
	void step();
	void line(Vector2d a, Vector2d b, Color c);
	void line(std::vector<Vector2d> f, Color c);
	void draw(Fragment fragment);
	void draw();
	void squareGrid(double size);
	void triangleGrid(double size);
	Vector2d applyGrid(Vector2d pos);
	void drawCircle(Vector2d pos, double r, Color c);
	void drawGrid();
};

