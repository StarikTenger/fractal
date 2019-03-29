#include "Draw.h"
#include <iostream>

Draw::Draw() {
	config.load("config.conf");
	window = new sf::RenderWindow(sf::VideoMode(config.width, config.height), "Fractal", sf::Style::Close);
	switch (config.gridType) {
	case 3:
		triangleGrid(config.gridSize);
		break;
	case 4:
		squareGrid(config.gridSize);
		break;
	}
	draw();
}

Draw::~Draw() {
}

void Draw::squareGrid(double size) {
	grid = {};
	int w = (double(config.width + 1) / size);
	int h = (double(config.height + 1) / size);
	for (int x = 0; x < w; x++) {
		for (int y = 0; y < h; y++) {
			grid.push_back(Vector2d(x*size, y*size));
			//std::cout << (x * size) << " " << (y*size) << "\n";
		}
	}
}

void Draw::triangleGrid(double size) {
	grid = {};
	double k = sqrt(3) / 2;
	double sizeVertical = size * k;
	int w = (config.width + 1) / size;
	int h = (config.height + 1) / sizeVertical;
	for (int x = -1; x < w + 1; x++) {
		for (int y = 0; y < h + 1; y++) {
			if (y % 2)
				grid.push_back(Vector2d(x*size, y*sizeVertical));
			else
				grid.push_back(Vector2d((x + 0.5)*size, y*sizeVertical));
		}
	}
}

Vector2d Draw::applyGrid(Vector2d pos) {
	for (auto p : grid) {
		if (geom::distance(p, pos) < config.stickRadius) {
			return p;
		}
	}
	return pos;
}

void Draw::step() {
	sf::Event event;
	while (window->pollEvent(event))
	{
		switch (event.type) {
		case sf::Event::Closed:
			window->close();
			break;
		case sf::Event::KeyPressed:
			switch (event.key.code) {
			case sf::Keyboard::Space: {
				state = !state;
				if (!state) {
					draw();
				}
				if (points.size() <= 1 || !state)
					break;
				Fragment f;
				f.points = points;
				f.types = types;
				draw(f);
				break;
			}
			case sf::Keyboard::BackSpace:
				if (state)
					break;
				if (points.size() > 0) {
					points.pop_back();
					types.pop_back();
				}
				draw();
				break;
			case sf::Keyboard::R:
				config.load("config.conf");
				delete window;
				window = new sf::RenderWindow(sf::VideoMode(config.width, config.height), "Fractal", sf::Style::Close);
				switch (config.gridType) {
				case 3:
					triangleGrid(config.gridSize);
					break;
				case 4:
					squareGrid(config.gridSize);
					break;
				}
				draw();
				break;
			}
		case sf::Event::MouseButtonPressed:
			if (state)
				break;
			if (event.mouseButton.button == sf::Mouse::Left) {
				Vector2d pos = applyGrid({ (double)event.mouseButton.x , (double)event.mouseButton.y });
				points.push_back(pos);
				types.push_back(type);
				draw();
			}
			if (event.mouseButton.button == sf::Mouse::Right) {
				type = !type;
				if (types.size() > 0) {
					types.back() = !types.back();
				}
				draw();
			}
			break;
		case sf::Event::MouseMoved:
			if (state)
				break;
			Vector2d pos = applyGrid({ (double)event.mouseMove.x , (double)event.mouseMove.y });
			points.push_back(pos);
			types.push_back(type);
			draw();
			points.pop_back();
			types.pop_back();
			break;
		}
	}
}

void Draw::line(Vector2d a, Vector2d b, Color c) {
	sf::Vertex line[] =
	{
		sf::Vertex(sf::Vector2f(a.x, a.y)),
		sf::Vertex(sf::Vector2f(b.x, b.y))
	};
	line[0].color = line[1].color = sf::Color(c.r, c.g, c.b, c.a);
	window->draw(line, 2, sf::Lines);
}

void Draw::line(std::vector<Vector2d> f, Color c) {
	if (f.size() < 1)
		return;
	for (int i = 0; i < f.size() - 1; i++) {
		line(f[i], f[i + 1], c);
	}
}

void Draw::draw() {
	window->clear();
	drawGrid();
	//std::cout << grid.size() << "\n";
	if (points.size() < 1)
		return;
	for (int i = 0; i < points.size() - 1; i++) {
		Color c(0, 255, 0);
		if (!types[i]) {
			c = Color(80, 80, 80);
		}
		line(points[i], points[i + 1], c);
	}
	window->display();
}

void Draw::drawCircle(Vector2d pos, double r, Color c) {
	sf::CircleShape shape(r);
	shape.setOutlineColor(sf::Color(c.r, c.g, c.b, c.a));
	shape.setFillColor(sf::Color(0, 0, 0, 0));
	shape.setPosition(pos.x-r, pos.y-r);
	shape.setOutlineThickness(1);
	window->draw(shape);
}

void Draw::drawGrid() {
	for (auto p : grid) {
		drawCircle(p, config.stickRadius, Color(50, 50, 50));
	}
}

void Draw::draw(Fragment fragment) {
	config.load("config.conf");

	window->clear();
	std::cout << "generating...\n";
	auto r = fractal(fragment, config.iterations, config);
	std::cout << "generated " << r.size() << " lines\n";
	line(r, Color(0, 255, 0, 255));
	std::cout << "displaying...\n";
	window->display();
	std::cout << "done\n\n";
}
