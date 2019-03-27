#include "Draw.h"
#include "Fragment.h"
#include <iostream>

using namespace std;
int main() {
	setlocale(LC_ALL, "Russian");
	Fragment f;
	Vector2d centre = { 300, 300 };
	f.points = {
		Vector2d(-300, 0) + centre,
		Vector2d(-100, -100) + centre,
		Vector2d(100, 100) + centre,
		Vector2d(300, 150) + centre,
	};
	
	Draw draw;
	
	draw.draw(f);
	//auto r = turn(f, { 600, 600 } , { 0, 300 }).points;
	
	while (1)
	{
		draw.step();
		
	}

	return 0;
}