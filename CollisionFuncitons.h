#pragma once
#include "olcPixelGameEngine.h"
#include "Collider.h"
#include "Manifold.h"
typedef olc::vf2d v2;

using std::cout;
using std::endl;


v2 GetSupport(Collider* C,v2 edgeone, v2 dirNorm, float& dist)
{
	int s = C->points.size();

	float smallest = INFINITY;
	v2 support(0,0);
	for (int i = 0; i < s; i++)
	{

		v2 p = C->points[i]- edgeone;


		float proj = p.dot(dirNorm);

		if (proj < smallest)
		{
			smallest = proj;
			support = C->points[i];
			
		}
	}

	dist = smallest;

	return support;
}




bool SAT(Particle* A, Particle* B, Manifold& out)
{
    //find minimum penetration axis
	vector<v2> contacts;
	float minPenetration = -INFINITY;

	Collider* one = &A->collider;
	Collider* two = &B->collider;


	for (int i = 0; i < 2; i++)
	{


		if (i == 1)
		{
			one = &B->collider;
			two = &A->collider;
		}

		int nVerts_One = one->points.size();
		int nVerts_two = two->points.size();



		vector<v2> PenPoints;
		for (int j = 0; j < nVerts_One; j++)
		{

			v2 one_A = one->points[j];
			v2 one_B = one->points[(j+1)% nVerts_One];

			v2 edge = one_B - one_A;

			v2 normal = -edge.perp().norm();


			float dist;
			v2 support = GetSupport(two, one_A, normal, dist);
			if (dist > 0)// seperation axis exists
			{

				return false;
			}
			if (dist < 0)//test penetrating
			{
				if (dist > minPenetration)//test if it's better than current min
				{
					minPenetration = dist;
					out.normal = normal;
					out.depth = dist;
					if (i == 0)
					{
						out.twoPoint = support;
						out.onePoint = out.twoPoint - normal * dist;
						out.one = A;
						out.two = B;
					}
					else
					{
						out.twoPoint = support;
						out.onePoint = out.twoPoint - normal * dist;
						out.one = B;
						out.two = A;
					}
				}
			}

				
		}
		
	}
	
	
	return true;
}