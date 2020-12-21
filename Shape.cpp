#include "Shape.h"
#include <cstdarg>
#include "Utility Functions.h"

Shape::Shape(int num, v2 lis...)
{
	va_list va;


	va_start(va, num);
	for (int i = 0; i < num; i++)
	{
		points.push_back(va_arg(va, v2));
	}

	va_end(va);

}

int Shape::CountVerts()
{
	return points.size();
}


float Shape::GetMass(float size)
{
	float tot = 0;
	for (int i = 0; i < points.size(); i++)
	{
		
		tot += GetTriangleArea(v2(0,0), points[i], points[(i+1)% points.size()]);
	}
	return tot;
}

void Shape::AdjustCenterOfMass() {

	float tot = 0;
	float totalMass = GetMass(1);

	v2 center = v2(0, 0);
	for (int i = 0; i < points.size(); i++)
	{
		v2 pointA = points[i];
		v2 pointB = points[(i + 1) % points.size()];

		v2 centroid = GetTriangleCentroid(v2(0, 0), pointA, pointB);

		float area = GetTriangleArea(v2(0, 0), pointA, pointB);


		float massratio = area / totalMass;


		center += centroid * massratio;


	}

	//v2 offset = 


		for (int i = 0; i < points.size(); i++)
		{
		}


}
