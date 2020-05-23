#pragma once
#include <iostream>
#include <cmath>
using namespace std;

struct vec3
{
	union 
	{
		struct 
		{
			float x, y, z;
		};
		struct 
		{
			float r, g, b;
		};
	};

	//multiplication d'un vecteur par un float
	inline vec3 operator*(const float t) const 
	{
		return
		{ 
			x*t, y*t, z*t 
		};
	}

	//addition entre vecteurs
	inline vec3 operator+(const vec3& rhs) const
	{
		return
		{ 
			x + rhs.x, y + rhs.y, z + rhs.z 
		};
	}

	//soustraction entre vecteurs
	inline vec3 operator-(const vec3& rhs) const
	{
		return
		{
			x - rhs.x, y - rhs.y, z - rhs.z 
		};
	}

	//multiplication avec un autre vecteur
	inline vec3 operator*(const vec3& rhs) const
	{
		return
		{ 
			x * rhs.x, y * rhs.y, z * rhs.z 
		};
	}

	//produit scalaire
	inline float dot(const vec3& rhs) const 
	{
		return x * rhs.x + y * rhs.y + z * rhs.z;
	}

	//fonction de normalisation
	inline vec3& normalize() 
	{
		float inv_length = 1.f / sqrtf(x*x + y * y + z * z);
		x *= inv_length;
		y *= inv_length;
		z *= inv_length;
		return *this;
	}
};

ostream& operator <<(ostream& o, const vec3& v)
{
	if(v.x != NULL) o << "(" << v.x << ", " << v.y << ", " << v.z << ")";
	else o << "(" << v.r << ", " << v.g << ", " << v.b << ")";
	return o;
}
// equivalent a typedef vec3 color;
using color = vec3;
