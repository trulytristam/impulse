#pragma once

#include "olcPixelGameEngine.h"
#include "Shape.h"
#include "Collider.h"

using olc::vf2d;
using std::shared_ptr;

typedef vf2d v2;

struct Manifold;
struct Collider;
struct Particle
{
	
	v2 p = {0,0};
	v2 v = {0,0};
	v2 a = {0,0};

	float ang = 0;
	float angVel = 0;

	Shape* shape;
	Collider collider;
	
	float size = 1;
	float M = 100;
	float I = 100;
	float iM = 1/100;
	float iI = 1 / 100;

	bool bStatic = false;


	v2 appliedForces = { 0,0 };
	v2 contraintForces = { 0,0 };

	Particle(v2, Shape*, float, bool);
	bool toDelete = false;


public:
	void Integrate(float, v2);
	void AddForce(v2);
	void ClearForces();
	void AddImpulse(v2,v2);
	void ConstrainToCircle(v2, float);
	bool isCollidingWith(shared_ptr<Particle>, Manifold&);
	void CalculateMasses();

	void UpdateCollider();
	void Draw(olc::PixelGameEngine*);


	bool PointIn(v2 );


	v2 getPointVelocity(v2);
	
	
	v2 LocalToGlobal(v2);
	v2 GlobalToLocal(v2);


};

