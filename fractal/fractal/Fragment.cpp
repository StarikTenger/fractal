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
	result.types = f.types;
	return result;
}

Fragment turnBackward(Fragment f, Vector2d a, Vector2d b) {
	Fragment result = f;
	for (auto& p : result.points) {
		p.y = -p.y;
	}
	result = turn(result, a, b);
	for (auto& t : result.types) {
		if (t == 2) {
			t = 1;
		}else if (t == 1) {
			t = 2;
		}
	}
	return result;
}

std::vector<Vector2d> fractal(Fragment f, int n, const Config& config) {
	return fractal(f, f, n, config);
}

std::vector<Vector2d> fractal(const Fragment& initial, Fragment f, int n, const Config& config) {
	//std::cout << f.points.size() << "\n";
	if (f.points.size() >= config.numerLimit) {
		std::cout << "line limit reached\n";
		return f.points;
	}
	if (n == 1) {
		return f.points;
	}
	//std::cout << f.points.size() << ", " << f.types.size() << "\n";
	int counter = 0;
	std::vector<Vector2d> result;
	std::vector<int> resultType;
	for (int i = 0; i < f.points.size() - 1; i++) {
		if (geom::distance(f.points[i], f.points[i + 1]) > config.distanceLimit && f.types.size() > i && f.types[i]) {	
			Fragment fragment;
			if(f.types[i]==1)
				fragment = turn(initial, f.points[i], f.points[i + 1]);
			else
				fragment = turnBackward(initial, f.points[i], f.points[i + 1]);
			for (int j = 0; j < fragment.points.size() - 1; j++) {
				result.push_back(fragment.points[j]);
				resultType.push_back(fragment.types[j]);
				counter++;
				if (counter >= config.numerLimit) {
					std::cout << "line limit reached\n";
					return result;
				}
			}
		} 
		else {
			result.push_back(f.points[i]);
			resultType.push_back(f.types[i]);
		}
	}
	result.push_back(f.points.back());
	resultType.push_back(0);
	
	{
		f.points = result;
		f.types = resultType;
		return fractal(initial, f, n-1, config);
	}
}
