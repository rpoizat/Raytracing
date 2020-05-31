#pragma once
#include "Entite.hpp"

class CylindreInf : public Entite
{
	private:

		float rayon;

	public:

		//constructeurs
		CylindreInf() {};
		CylindreInf(Vec3 p, Vec3 rot, color c, float r) : Entite(p, rot, c), rayon(r) {}

		//Getteur sur le rayon du cylindre
		float GetRayon()
		{
			return rayon;
		}

		//Fonction d'intersection entre le cylindre infini et le rayon donné en paramètre
		bool Intersection(const Ray& ray, outils::Point& impact) const override
		{
			Ray localR = GlobalToLocal(ray);

			float a = pow(localR.dir[0], 2) + pow(localR.dir[2], 2);
			float b = 2 * (localR.origin[0] * localR.dir[0] + localR.origin[2] * localR.dir[2]);
			float c = pow(localR.origin[0], 2) + pow(localR.origin[2], 2) - 1;

			float delta = pow(b, 2) - 4 * a*c;

			float t1 = (-b + sqrt(delta)) / (2 * a);
			float t2 = (-b - sqrt(delta)) / (2 * a);

			float t;

			if (t1 < t2 && t1 > 0) t = t1;
			else if (t1 > 0 && t2 < 0) t = t1;
			else t = t2;

			if (t > 0)
			{
				impact[0] = localR.origin[0] + t * localR.dir[0];
				impact[1] = localR.origin[1] + t * localR.dir[1];
				impact[2] = localR.origin[2] + t * localR.dir[2];

				impact = LocalToGlobal(impact);
				return true;
			}
			else
			{
				return false;
			}

		}
};