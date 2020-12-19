#pragma once

#include "olcPixelGameEngine.h"

using olc::vf2d;
using std::vector;
typedef vf2d v2;

struct Shape
{
	vector<v2> points;


	Shape() {}
	Shape(int, v2...);

	int CountVerts();


};




