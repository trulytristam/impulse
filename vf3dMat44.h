#pragma once

//#include "olcPixelGameEngine.h"
#include <istream>
#include <ostream>
#include <random>
using namespace std;



random_device rd;
mt19937 mt(rd());
uniform_int_distribution<int> DIST(0, 1001);

struct vf3d {

	float x, y, z;

	float w = 1;

	vf3d() {}

	vf3d(float xx, float yy, float zz)
	{
		x = xx; y = yy; z = zz;
	}

	vf3d operator + (vf3d other) { return { x + other.x, y + other.y, z + other.z }; }
	vf3d operator - (vf3d other) { return { x - other.x, y - other.y, z - other.z }; }
	vf3d operator * (float other) { return { x * other, y * other, z * other }; }
	vf3d operator / (float other) { return { x / other, y / other, z / other }; }

	vf3d operator += (vf3d other) { return { x += other.x, y += other.y, z += other.z }; }
	vf3d operator -= (vf3d other) { return { x -= other.x, y -= other.y, z -= other.z }; }


	float dot(vf3d other) {
		return  x * other.x + y * other.y + z * other.z;
	}

	vf3d cross(vf3d o)
	{
		return {
			y * o.z - z * o.y,
			z * o.x - x * o.z,
			x * o.y - y * o.x
		};
	}

	float mag()
	{

		return { sqrt((x * x) + (y * y) + (z * z)) };
	}

	float dist(vf3d other)
	{
		vf3d t = other - *this;

		return t.mag();
	}

	vf3d multiply(vf3d other)
	{
		return { x * other.x, y * other.y, z * other.z };
	}

	vf3d reflect(vf3d norm)
	{
		return *this - (norm * ((*this).dot(norm))) * 2;
	}
	

	vf3d norm()
	{
		float t = mag();
		return { x / t,y / t,z / t };
	}

	vf3d lerpvf3d(vf3d other, float roughness)
	{
		return (*this) * (1 - roughness) + other * roughness;

	}


	static vf3d randomVf3d()
	{
		float a = (float)(-500 + (DIST(mt))) / 500.0;
		float b = (float)(-500 + (DIST(mt))) / 500.0;
		float c = (float)(-500 + (DIST(mt))) / 500.0;


		vf3d temp = { a,b,c };

		return temp;

	}

	/*static vf3d FromPixel(olc::Pixel p)
	{
		return vf3d((float)p.r / 255.0,(float)p.g / 255.0 ,(float)p.b / 255.0);
	}*/

	static vf3d randomVf3d(vf3d n)
	{
		float a = (float)(-500 + (DIST(mt))) / 500.0;
		float b = (float)(-500 + (DIST(mt))) / 500.0;
		float c = (float)(-500 + (DIST(mt))) / 500.0;

		vf3d temp = { a,b,c };

		if (temp.dot(n) < 0)
		{
			return temp * -1;
		}

		return temp;

	}




};


ostream& operator << (ostream& os, vf3d other)
{
	os << "x: " << other.x << " y: " << other.y << " z: " << other.z;

	return os;
}

struct mat44;
ostream& operator << (ostream& os, mat44 m);
struct mat44 {


	float m[4][4];

	mat44() {


	}


	static mat44 CreateIdentity()
	{
		mat44 temp;

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (i == j) {
					temp.m[i][j] = 1;

				}
				else {
					temp.m[i][j] = 0;
				}
			}
		}
		
		return temp;
	}


	

	vf3d operator * (vf3d o)
	{



		vf3d temp;
		float* a = &temp.x;
		for (int i = 0; i < 4; i++)
		{

			*a = m[i][0] * o.x + m[i][1] * o.y + m[i][2] * o.z + m[i][3] * o.w;

			a++;
		}



		return temp;
	}

	mat44 operator * (mat44 o)
	{
		mat44 out;

		for (int i = 0; i < 4; i++)
		{

			for (int j = 0; j < 4; j++)
			{
				out.m[i][j] = m[i][0] * o.m[0][j] + m[i][1] * o.m[1][j] + m[i][2] * o.m[2][j] + m[i][3] * o.m[3][j];

			}
		}

		return out;
	}

	mat44 operator * (float o)
	{
		mat44 temp;

		float* d = (float*)(void*)temp.m;
		float* t = (float*)(void*)m;

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{

				temp.m[i][j] = m[i][j] *o;


			}

		}
		return temp;
	}

	mat44 operator + (mat44 o)
	{
		mat44 temp;


		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{

				temp.m[i][j] = m[i][j] + o.m[i][j];


			}

		}
			
		return temp;
	}

	mat44 Invert()
	{
		mat44 o;

		o.m[0][0] = m[0][0];       o.m[0][1] = m[1][0];     o.m[0][2] = m[2][0];       o.m[0][3] = m[0][3];
		o.m[1][0] = m[0][1];       o.m[1][1] = m[1][1];     o.m[1][2] = m[2][1];      o.m[1][3] = m[1][3];
		o.m[2][0] = m[0][2];       o.m[2][1] = m[1][2];     o.m[2][2] = m[2][2];       o.m[2][3] = m[2][3];
		o.m[3][0] = m[3][0];       o.m[3][1] = m[3][1];     o.m[3][2] = m[3][2];       o.m[3][3] = m[3][3];
		return o;
	}


	static mat44 CreateXRot(float a)
	{
		mat44 o;

		o.m[0][0] = 1; o.m[0][1] = 0; o.m[0][2] = 0; o.m[0][3] = 0;
		o.m[1][0] = 0; o.m[1][1] = cos(a); o.m[1][2] = -sin(a); o.m[1][3] = 0;
		o.m[2][0] = 0; o.m[2][1] = sin(a); o.m[2][2] = cos(a); o.m[2][3] = 0;
		o.m[3][0] = 0; o.m[3][1] = 0; o.m[3][2] = 0; o.m[3][3] = 1;
		return o;
	}
	static mat44 CreateYRot(float a)
	{
		mat44 o;

		o.m[0][0] = cos(a); o.m[0][1] = 0; o.m[0][2] = sin(a); o.m[0][3] = 0;
		o.m[1][0] = 0; o.m[1][1] = 1; o.m[1][2] = 0; o.m[1][3] = 0;
		o.m[2][0] = -sin(a); o.m[2][1] = 0; o.m[2][2] = cos(a); o.m[2][3] = 0;
		o.m[3][0] = 0; o.m[3][1] = 0; o.m[3][2] = 0; o.m[3][3] = 1;
		return o;

	}
	static mat44 CreateZRot(float a)
	{
		mat44 o;

		o.m[0][0] = cos(a); o.m[0][1] = -sin(a); o.m[0][2] = 0; o.m[0][3] = 0;
		o.m[1][0] = sin(a); o.m[1][1] = cos(a); o.m[1][2] = 0; o.m[1][3] = 0;
		o.m[2][0] = 0; o.m[2][1] = 0; o.m[2][2] = 1; o.m[2][3] = 0;
		o.m[3][0] = 0; o.m[3][1] = 0; o.m[3][2] = 0; o.m[3][3] = 1;
		return o;
	}


	static mat44 LookAt(vf3d c, vf3d point)
	{

		vf3d up = { 0,1,0 };
		vf3d z = (point-c).norm();
		vf3d x = z.cross(up);

		vf3d y = x.cross(z);


		mat44 t;

		t.m[0][0] = x.x; t.m[0][1] = y.x; t.m[0][2] = z.x; 
		t.m[1][0] = x.y; t.m[1][1] = y.y; t.m[1][2] = z.y; 
		t.m[2][0] = x.z; t.m[2][1] = y.z; t.m[2][2] = z.z; 

		/*t.m[0][0] = x.x; t.m[0][1] = x.y; t.m[0][2] = x.z;
		t.m[1][0] = y.x; t.m[1][1] = y.y; t.m[1][2] = y.z;
		t.m[2][0] = z.x; t.m[2][1] = z.y; t.m[2][2] = z.z;*/

		t.m[3][3] = 1;
	


		return t;


	}
	


	vf3d GetBasisX()
	{
		return { m[0][0],m[1][0],m[2][0] };
	}
	vf3d GetBasisY()
	{
		return { m[0][1],m[1][1],m[2][1] };
	}
	vf3d GetBasisZ()
	{
		return { m[0][2],m[1][2],m[2][2] };
	}

	void reOrthogonalize()
	{

		vf3d x = GetBasisX();
		vf3d y = GetBasisY();
		vf3d z = GetBasisZ();


		z = y.cross(x).norm();
		x = z.cross(y).norm();
		y = x.cross(z).norm();


		m[0][0] = x.x;
		m[1][0] = x.y;
		m[2][0] = x.z;

		m[0][1] = y.x;
		m[1][1] = y.y;
		m[2][1] = y.z;

		m[0][2] = z.x;
		m[1][2] = z.y;
		m[2][2] = z.z;
	}


	mat44 differentiate(vf3d v)
	{
		mat44 temp = mat44::CreateIdentity();


		vf3d x = v.cross(GetBasisX());
		vf3d y = v.cross(GetBasisY());
		vf3d z = v.cross(GetBasisZ());


		temp.m[0][0] = x.x;
		temp.m[1][0] = x.y;
		temp.m[2][0] = x.z;
		temp.m[0][1] = y.x;
		temp.m[1][1] = y.y;
		temp.m[2][1] = y.z;
		temp.m[0][2] = z.x;
		temp.m[1][2] = z.y;
		temp.m[2][2] = z.z;


		return temp;


	}



};

ostream& operator << (ostream& os, mat44 m)
{

	os << "---------------------------------------" << endl;
	for (int i = 0; i < 4; i++)
		os << "-- " << m.m[i][0] << "-- " << m.m[i][1] << "-- " << m.m[i][2] << "-- " << m.m[i][3] << endl;;
	os << "---------------------------------------" << endl;


	return os;
}