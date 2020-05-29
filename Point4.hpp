#pragma once

#include "Vec4.hpp";
#include "Point.hpp"

using namespace outils;

//représente le point en coordonnées homogènes
class Point4
{
	private:
		Vec4 position4;

	public:

#pragma region Constructeurs
		//constructeur vide
		Point4()
		{
			position4[0] = 0.f;
			position4[1] = 0.f;
			position4[2] = 0.f;
			position4[3] = 1.f;
		}

		//constructeurs avec paramètres
		Point4(float x, float y, float z, float w)
		{
			position4[0] = x;
			position4[1] = y;
			position4[2] = z;
			position4[3] = w;
		}

		Point4(outils::Point p)
		{
			position4[0] = p[0];
			position4[1] = p[1];
			position4[2] = p[2];
			position4[3] = 1.f;
		}

		Point4(Vec3 v)
		{
			position4[0] = v[0];
			position4[1] = v[1];
			position4[2] = v[2];
			position4[3] = 0.f;
		}

		Point4(Vec4 v)
		{
			position4[0] = v[0];
			position4[1] = v[1];
			position4[2] = v[2];
			position4[3] = v[3];
		}

#pragma endregion

#pragma region Fonctions

		//getteur sur la position
		const Vec4 GetPosition() const
		{
			return position4;
		}

		//produit scalaire
		inline float dot(const Point4& p) const
		{
			return position4.dot(p.position4);
		}

#pragma endregion

#pragma region Operateurs

		//accès en lecture aux coordonnées du point
		float operator[](int i) const
		{
			switch (i)
			{
			case 0:
				return position4[0];

			case 1:
				return position4[1];

			case 2:
				return position4[2];

			case 3:
				return position4[3];

			default:
				return position4[i%4];
			}
		}

		//accès en lecture aux coordonnées du point
		float& operator[](int i) 
		{
			switch (i)
			{
			case 0:
				return position4[0];

			case 1:
				return position4[1];

			case 2:
				return position4[2];

			case 3:
				return position4[3];

			default:
				return position4[i%4];
			}
		}

		//affectation
		inline Point4& operator=(Point4 p)
		{
			position4 = p.position4;

			return *this;
		}

		//operateur +=
		inline Point4& operator+=(const Point4& p)
		{
			position4 += p.position4;
			return *this;
		}

		//operateur -=
		inline Point4& operator-=(const Point4& p)
		{
			position4 -= p.position4;
			return *this;
		}

		//operateur *=
		inline Point4& operator*=(const Point4& p)
		{
			position4 *= p.position4;
			return *this;
		}

#pragma endregion
};

#pragma region Operateurs externes

//addition entre point4
inline Point4 operator+(Point4 p1, const Point4& p2)
{
	return p1 += p2;
}

//soustraction entre point4
inline Point4 operator-(Point4 p1, const Point4& p2)
{
	return p1 -= p2;
}

//multiplication entre point4
inline Point4 operator*(Point4 p1, const Point4& p2)
{
	return p1 *= p2;
}

//multiplication entre matrice 4x4 et point4
Point4 operator*(Mat mat4, const Point4 p)
{
	return Point4(mat4 * p.GetPosition());
}

//flux
inline ostream& operator<<(ostream& os, Point4 p)
{
	os << p.GetPosition();
}
#pragma endregion