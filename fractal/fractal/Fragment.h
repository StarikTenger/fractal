#pragma once
#include "geometry.h"
#include "Config.h"
#include <vector>

class Fragment {
public:
	std::vector<Vector2d> points;
	std::vector<int> types;
	Fragment();
	~Fragment();
};

Fragment turn(Fragment f, Vector2d a, Vector2d b);
Fragment turnBackward(Fragment f, Vector2d a, Vector2d b);
std::vector<Vector2d> fractal(const Fragment& initial, Fragment f, int n, const Config& config);
std::vector<Vector2d> fractal(Fragment f, int n, const Config& config);