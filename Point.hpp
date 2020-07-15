#pragma once
#include "Vec3.hpp"

namespace outils
{
	class Point
	{
	private:
		Vec3 position;

	public:

#pragma region Constructeurs
		Point()
		{
			position[0] = 0.f;
			position[1] = 0.f;
			position[2] = 0.f;
		}

		Point(float x, float y, float z)
		{
			position[0] = x;
			position[1] = y;
			position[2] = z;
		}

		Point(Vec3 v)
		{
			position = v;
		}
#pragma endregion

#pragma region Fonctions

		//getteur sur la position
		inline Vec3 GetPosition() const
		{
			return position;
		}

		//produit scalaire
		inline float dot(const Point& p) const
		{
			return position.dot(p.position);
		}

#pragma endregion

#pragma region operateurs
		//accès en lecture aux coordonnées du point
		float operator[](int i) const
		{
			switch (i)
			{
			case 0:
				return position[0];

			case 1:
				return position[1];

			case 2:
				return position[2];

			default:
				return position[i % 3];
			}
		}

		//accès en écriture aux coordonnées du point
		float& operator[](int i)
		{
			switch (i)
			{
			case 0:
				return position[0];

			case 1:
				return position[1];

			case 2:
				return position[2];

			default:
				return position[i % 3];
			}
		}

		//affectation
		inline Point& operator=(Point p)
		{
			position = p.position;

			return *this;
		}

		//operateur +=
		inline Point& operator+=(const Point& p)
		{
			position + p.position;

			return *this;
		}

		//operateur -=
		inline Point& operator-=(const Point& p)
		{
			position - p.position;

			return *this;
		}
#pragma endregion
	};

#pragma region operateurs externes

	//operateur +
	inline Point operator+(Point p1, const Point& p2)
	{
		p1 += p2;
		return p1;
	}

	//operateur -
	inline Point operator-(Point p1, const Point& p2)
	{
		p1 -= p2;
		return p1;
	}

	//operateur *
	inline Point& operator*(Point& p, const float& f)
	{
		p.GetPosition() * f;

		return p;
	}

	//operateur de flux
	ostream& operator<<(ostream& os, Point p)
	{
		os << p.GetPosition();
		return os;
	}

#pragma endregion
}

