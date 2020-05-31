#pragma once
#include "Entite.hpp"

class PlanInf : public Entite
{
	public:

		//constructeurs
		PlanInf() {};
		PlanInf(Vec3 p, Vec3 rot, color c) : Entite(p, rot, c){}

		//Getteur sur la position
		Vec3 GetPosition()
		{
			return position;
		}

		//fonction d'intersection entre le plan infini et le rayon donné en paramètre
		bool Intersection(const Ray& ray, outils::Point& impact) const override
		{
			Ray localRay = GlobalToLocal(ray);

			float t = -localRay.origin[2] / localRay.dir[2];

			if (t >= 0)
			{
				impact[0] = localRay.origin[0] + t * localRay.dir[0];
				impact[1] = localRay.origin[1] + t * localRay.dir[1];
				impact[2] = localRay.origin[2] + t * localRay.dir[2];

				impact = LocalToGlobal(impact);
				return true;
			}
			else
			{
				return false;
			}
		}
};