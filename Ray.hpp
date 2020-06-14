#pragma once
#include "Point.hpp"
using namespace outils;

class Ray 
{
	public:

		Vec3 dir;
		outils::Point origin;

#pragma region Constructeurs

		//constructeur vide
		Ray()
		{
			dir = Vec3();
			origin = outils::Point();
		}

		//constructeurs avec paramètres
		Ray(outils::Point p, Vec3 v)
		{
			dir = v;
			origin = p;
		}

		Ray(float ox, float oy, float oz, float vx, float vy, float vz)
		{
			dir = Vec3(vx, vy, vz);
			origin = outils::Point(ox, oy, oz);
		}

		void normalize() {

			dir.normalize();

		}
#pragma endregion
};