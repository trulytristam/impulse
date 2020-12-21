#pragma once
#include "Shape.h"

using std::unique_ptr;

vector<unique_ptr<Shape>> Sphapes;

Shape* Square = new Shape(4,
	v2(-2, -1),
	
	v2(2, -1),
	v2(2, 1),
	v2(-2, 1)


);

