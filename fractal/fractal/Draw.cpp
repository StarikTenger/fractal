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
				draw(f);
				break;
			}
			case sf::Keyboard::BackSpace:
				if (state)
					break;
				if (points.size() > 0) {
					points.pop_back();
				}
				draw();
				break;
			}
		case sf::Event::MouseButtonPressed:
			if (state)
				break;
			if (event.mouseButton.button == sf::Mouse::Left) {
				points.push_back({ (double)event.mouseButton.x , (double)event.mouseButton.y});
				draw();
			}
			break;
		case sf::Event::MouseMoved:
			if (state)
				break;
			points.push_back({ (double)event.mouseMove.x , (double)event.mouseMove.y });
			draw();
			points.pop_back();
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
	line(points, Color(0, 255, 0));
	window->display();
}

void Draw::draw(Fragment fragment) {
	config.load("config.conf");

	window->clear();
	//for (int i = 1; i <= 4; i++) {
		auto r = fractal(fragment, config.iterations, config);
		std::cout << "--->" << r.size();
		line(r, Color(0, 255, 0, 255));
	//}
	window->display();
}
