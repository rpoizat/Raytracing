#pragma once
#include <iostream>
#include <cmath>
using namespace std;

const float EPSILON = 0.0001f;

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

		//constructeur avec param�tres
		Vec3(float x1, float y1, float z1)
		{
			x = x1;
			y = y1;
			z = z1;
		}

#pragma endregion

#pragma region Operateurs

		//acc�s en lecture
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

		//acc�s en �criture
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
			x += v.x;
			y += v.y;
			z += v.z;

			return *this;
		}

		//soustraction entre vecteurs
		inline Vec3 operator-=(const Vec3& v)
		{
			x -= v.x;
			y -= v.y; 
			z -= v.z;

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
		inline Vec3 operator*=(const Vec3& v)
		{
			x *= v.x;
			y *= v.y;
			z *= v.z;

			return *this;
		}

		//division avec un Vec3
		inline Vec3 operator/=(const Vec3& v)
		{
			x /= v.x;
			y /= v.y;
			z /= v.z;

			return *this;
		}

		inline bool operator==(const Vec3& v)
		{
			//si c'est le cas, les x sont vraiment tr�s tr�s proches
			if (x + EPSILON > v.x && v.x + EPSILON > x)
			{
				//si c'est le cas, les y sont vraiment tr�s tr�s proches
				if (y + EPSILON > v.y && v.y + EPSILON > y)
				{
					//si c'est le cas, les z sont vraiment tr�s tr�s proches
					if (z + EPSILON > v.z && v.z + EPSILON > z)
					{
						return true;
					}
				}
			}
			else return false;
		}

		//division avec un float
		inline Vec3 operator/=(const float& f)
		{
			x /= f;
			y /= f;
			z /= f;

			return *this;
		}
#pragma endregion

#pragma region Fonctions

	//produit scalaire
	inline float dot(const Vec3& v) const 
	{
		return x * v.x + y * v.y + z * v.z;
	}

	//cross product
	inline Vec3 Cross(const Vec3& v)
	{
		Vec3 res(0.0f, 0.0f, 0.0f);
		res[0] = y * v[2] - z * v[1];
		res[1] = z * v[0] - x * v[2];
		res[2] = x * v[1] - y * v[0];

		return res;
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

//multiplication entre vec3 et float
inline Vec3 operator*(const float& f, Vec3 v1)
{
	return v1 *= f;
}

//division entre vec3
inline Vec3 operator/(Vec3 v1, const Vec3& v2)
{
	return v1 /= v2;
}

//division par un float
inline Vec3 operator/(Vec3 v1, const float& f)
{
	return v1 /= f;
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
