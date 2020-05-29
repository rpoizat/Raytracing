#pragma once
#include <iostream>
#include <cmath>
using namespace std;

class Vec3
{
	private:

		float x, y, z;

	public:

#pragma region Constructeurs

		//constructeur vide
		Vec3()
		{
			x = 0;
			y = 0;
			z = 0;
		}

		//constructeur avec paramètres
		Vec3(float x1, float y1, float z1)
		{
			x = x1;
			y = y1;
			z = z1;
		}

#pragma endregion

#pragma region Operateurs

		//accès en lecture
		inline float operator[](int i) const
		{
			switch (i)
			{
				case 0:
					return x;

				case 1:
					return y;

				case 2:
					return z;

				default:
					return NULL;
			}
		}

		//accès en écriture
		inline float& operator[](int i)
		{
			switch (i)
			{
			case 0:
				return x;

			case 1:
				return y;

			case 2:
				return z;

			default:
				return x;
			}
		}

		//affectation
		inline Vec3& operator=(const Vec3& v)
		{
			x = v[0];
			y = v[1];
			z = v[2];

			return *this;
		}

		//addition entre vecteurs
		inline Vec3 operator+=(const Vec3& v)
		{
			x + v.x;
			y + v.y;
			z + v.z;

			return *this;
		}

		//soustraction entre vecteurs
		inline Vec3 operator-=(const Vec3& v)
		{
			x - v.x;
			y - v.y; 
			z - v.z;

			return *this;
		}

		//multiplication avec float
		inline Vec3 operator*=(const float& f)
		{
			x *= f;
			y *= f;
			z *= f;

			return *this;
		}

		//mutliplication avec un Vec3
		inline Vec3 operator *=(const Vec3& v)
		{
			x *= v.x;
			y *= v.y;
			z *= v.z;

			return *this;
		}

#pragma endregion

#pragma region Fonctions

	//produit scalaire
	inline float dot(const Vec3& v) const 
	{
		return x * v.x + y * v.y + z * v.z;
	}

	//fonction de normalisation
	inline Vec3& normalize() 
	{
		float inv_length = 1.f / sqrtf(x*x + y * y + z * z);
		x *= inv_length;
		y *= inv_length;
		z *= inv_length;

		return *this;
	}

#pragma endregion
};

#pragma region operateurs externes

//multiplication d'un vecteur par un float
inline Vec3 operator*(Vec3 v, const float& t)
{
	return v *= t;
}

//multiplication d'un vecteur par un autre vecteur
inline Vec3 operator*(Vec3 v1, const Vec3& v2)
{
	return v1 *= v2;
}

//addition entre vecteurs
inline Vec3 operator+(Vec3 v1, const Vec3& v2)
{
	return v1 += v2;
}

//soustraction entre vecteurs
inline Vec3 operator-(Vec3 v1, const Vec3& v2)
{
	return v1 -= v2;
}

//operateur de flux
ostream& operator <<(ostream& o, const Vec3& v)
{
	o << "(" << v[0] << ", " << v[1] << ", " << v[2] << ")";
	return o;
}

#pragma endregion

// equivalent a typedef vec3 color;
using color = Vec3;
