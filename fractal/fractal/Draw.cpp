#include "Draw.h"
#include <iostream>

Draw::Draw() {
	
	window = new sf::RenderWindow(sf::VideoMode(600, 600), "Fractal");
}

Draw::~Draw() {
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
			}
		case sf::Event::MouseButtonPressed:
			if (state)
				break;
			if (event.mouseButton.button == sf::Mouse::Left) {
				points.push_back({ (double)event.mouseButton.x , (double)event.mouseButton.y});
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
			points.push_back({ (double)event.mouseMove.x , (double)event.mouseMove.y });
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
