#pragma once
#include "olcPixelGameEngine.h"

typedef olc::vf2d v2;



v2 Rotate(v2 p, float a)
{


	float s = sin(a);
	float c = cos(a);

	v2 temp;

	temp.x = c * p.x - s * p.y;
	temp.y = s * p.x + c * p.y;

	return temp;

}

