#pragma once
#include "Entite.hpp"

class Carre : public Entite
{
	private :

		float cote;

	public:

		Carre() {};
		Carre(Vec3 p, Vec3 rot, float c, Material m) : Entite(p, rot, m), cote(c) {}

		//getteur sur la cote du carre
		float GetCote() const
		{
			return cote;
		}

		//fonction d'intersection
		bool Intersection(const Ray& ray, outils::Point& impact) const override
		{
			Ray localRay = GlobalToLocal(ray);

			float t = -localRay.origin[2] / localRay.dir[2];

			if (t >= 0)
			{
				impact[0] = localRay.origin[0] + t * localRay.dir[0];
				impact[1] = localRay.origin[1] + t * localRay.dir[1];
				impact[2] = localRay.origin[2] + t * localRay.dir[2];

				if (impact[0] < -1 || impact[0]> 1)
				{
					return false;
				}
				else
				{
					if (impact[1] < -1 || impact[1] > 1)
					{
						return false;
					}
					else
					{
						impact = LocalToGlobal(impact);
						return true;
					}
				}
			}
			else
			{
				return false;
			}
		}

		//fonction pour obtenir la normale
		Ray getNormal(const outils::Point& p, const outils::Point& o)const
		{
			outils::Point localImpact = GlobalToLocal(p);
			outils::Point localObservator = GlobalToLocal(o);

			if (localObservator[2] >= 0)
			{
				Vec3 vecNorm(0, 0, 1);
				Ray normal(localImpact, vecNorm);
				normal = LocalToGlobal(normal);
				normal.dir.normalize();
				return normal;	
			}
			else
			{
				Vec3 vecNorm(0, 0, -1);
				Ray normal(localImpact, vecNorm);
				normal = LocalToGlobal(normal);
				normal.dir.normalize();
				return normal;
			}
		}
};