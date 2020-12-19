#include "Shape.h"
#include <cstdarg>


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
