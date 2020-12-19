#pragma once
#include "olcPixelGameEngine.h"

typedef olc::vf2d v2;

struct Particle;
struct Manifold
{
	Particle* one = nullptr;
	Particle* two = nullptr;


	v2 onePoint;
	v2 twoPoint;

	v2 normal;
	float depth;




};

