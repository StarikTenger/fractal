#include "Fragment.h"
#include <iostream>

Fragment::Fragment() {
}


Fragment::~Fragment() {
}

Fragment turn(Fragment f, Vector2d a, Vector2d b) {
	Fragment result = f;
	//scale
	double k = geom::distance(a, b) / geom::distance(f.points.front(), f.points.back());
	for (auto& p : result.points) {
		p = f.points.front() - (f.points.front() - p)*k;
	}
	//rotate
	double angle = geom::angle(b - a) - geom::angle(f.points.back() - f.points.front());
	for (auto& p : result.points) {
		p = f.points.front() + geom::rotate(p - f.points.front(), angle);
	}
	//move
	Vector2d movement = a - f.points.front();
	for (auto& p : result.points) {
		p += movement;
	}
	return result;
}

std::vector<Vector2d> fractal(Fragment f, int n, const Config& config) {
	if (n == 1) {
		return f.points;
	}
	std::cout << f.points.size() << "\n";
	int counter = 0;
	std::vector<Vector2d> result;
	for (int i = 0; i < f.points.size() - 1; i++) {
		if (geom::distance(f.points[i], f.points[i + 1]) > config.distanceLimit) {
			std::vector<Vector2d> fragment = turn(f, f.points[i], f.points[i + 1]).points;
			for (int j = 0; j < fragment.size() - 1; j++) {
				result.push_back(fragment[j]);
				counter++;
				if (counter >= config.numerLimit) {
					return result;
				}
			}
		}
		else {
			result.push_back(f.points[i]);
		}
	}
	result.push_back(f.points.back());
	
	{
		f.points = result;
		return fractal(f, n-1, config);
	}
}
