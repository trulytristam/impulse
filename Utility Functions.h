#pragma once
#include "olcPixelGameEngine.h"

typedef olc::vf2d v2;


v2 GetTriangleCentroid(v2 a, v2 b, v2 c)
{

	return (a + b + c) / 3;

}

float GetTriangleArea(v2 a, v2 b, v2 c)
{	
	v2 vec = c - b;
	v2 ca = c - a;
	v2 n = vec.perp().norm();
	float h = n.dot(ca);
	return (abs(h) * vec.mag())/2;

}