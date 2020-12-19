#include "Particle.h"
#include <iostream>
#include "CollisionFuncitons.h"
#include "Rotate.h"

#include "Shape.h"




using std::cout;
using std::endl;


void Particle::Integrate(float ft, v2 G)
{
	
	if (!bStatic)
	{	
		a += (appliedForces + contraintForces);
		v += a * ft;
		p += v * ft;
		
		
		
		ang += angVel * ft;
	}
	
	a = { 0,0 };
	ClearForces();
}



void Particle::AddForce(v2 f)
{
	appliedForces += f;
}


void Particle::ClearForces()
{
	appliedForces = v2{ 0,0 };
	contraintForces = v2{ 0,0 };
}


void Particle::AddImpulse(v2 point, v2 J)
{
	if (!bStatic)
	{
		
		v += J * iM;
		v2 r = point - p;
		v2 t = r.perp().norm();

		angVel += t.dot(J) * iI;
	}
	

}


void Particle::CalculateMasses() {


	M = 70.0;
	I = 1500.0;

	if (!bStatic)
	{
		iM = 1.0 / M;
		iI = 1.0 / I;
	}
	else
	{
		M = INFINITY;
		I = INFINITY;
		iM = 0;
		iI = 0;
	}



}


bool Particle::PointIn(v2 point)
{
	return (p - point).mag() < size;

}

v2 Particle::getPointVelocity(v2 point)
{

	v2 r = point - p;
	v2 t = r.perp();
	v2 tangent = t.norm();
	return v + t * angVel;
}


Particle::Particle(v2 pos, Shape* inshape, float s, bool stat = false) {

	this->p = pos;
	this->shape = inshape;
	bStatic = stat;
	if (bStatic)
	{
		p += {0, 150};
		ang = 0.00;
	}
	CalculateMasses();
	if (inshape)
	{
		this->size = s;

		
		for (int i = 0; i < shape->CountVerts(); i++)
		{
			collider.points.push_back(v2(0, 0));
		}
		
		collider.points.reserve(shape->CountVerts());
	}

}

void Particle::Draw(olc::PixelGameEngine* scr)
{

	if (shape)
	{
		
		for (int i = 0; i < collider.points.size(); i++)
		{
			v2 a = collider.points[i];
			v2 b = collider.points[(i+1) % collider.points.size()];


			scr->FillTriangle(a, b, p);
			

			scr->DrawLine(a, b, olc::RED);
			v2 vel = getPointVelocity(a);

			//scr->DrawLine(a, a + vel, olc::CYAN);

		}



	}
	else
	{
		scr->FillCircle(p, 3);
	}


}



void Particle::UpdateCollider() 
{
	if (shape)
	{
		for (int i = 0; i < shape->CountVerts(); i++)
		{

			v2 point = LocalToGlobal(shape->points[i]);
			collider.points[i] = point;


		}
	}
	
}

v2 Particle::LocalToGlobal(v2 point)
{

	v2 temp = Rotate(point, ang);
	temp = temp * size;

	temp += p;

	return temp;
}

v2 Particle::GlobalToLocal(v2 point)
{
	return { 0,0 };
}

void Particle::ConstrainToCircle(v2 c, float rad)
{
	


	v2 P = p - c;



	float C = 0.5 * (P.dot(P) - rad * rad);
	float Cdot = P.dot(v);


	
	v2 fext = appliedForces*-1;

		

	float Top = fext.dot(P) - ((v* M).dot(v));
	float Bot = P.dot(P);

	float Y = Top / Bot;



	
	contraintForces += P * Y ;
	

	
	//AddForce(P.norm() * -20 * x);


	float x = (P.mag() - rad);
	p -= x * P.norm()* 0.0001;
	//

	//AddForce(P.norm() * v.dot(P.norm()*-1)*0.8);
}



bool Particle::isCollidingWith(shared_ptr<Particle> other, Manifold& out)
{

	//SAT 

	if (SAT(this, &*other, out))
	{

		return true;
	}

	return false;
}

