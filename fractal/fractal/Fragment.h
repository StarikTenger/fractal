#pragma once
#include "geometry.h"
#include "Config.h"
#include <vector>

class Fragment {
public:
	std::vector<Vector2d> points;
	Fragment();
	~Fragment();
};

Fragment turn(Fragment f, Vector2d a, Vector2d b);
std::vector<Vector2d> fractal(Fragment f, int n, const Config& config);