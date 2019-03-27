#pragma once
#include "geometry.h"

class Line {
public:
	Vector2d start;
	Vector2d end;
	Line();
	Line(Vector2d _start, Vector2d _end);
	~Line();
};

