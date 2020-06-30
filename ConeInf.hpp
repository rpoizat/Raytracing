#pragma once
#include "Entite.hpp"

class ConeInf : public Entite
{
	private:

		float angle;

	public:

		//constructeur
		ConeInf() {};
		ConeInf(Vec3 p, Vec3 rot, float a, Material m) : Entite(p, rot, m), angle((a * 3.1415) / 180){}

		//getteur sur l'angle
		float GetAngle()
		{
			return angle;
		}

		//fonction d'intersection
		bool Intersection(const Ray& ray, outils::Point& impact) const override
		{
			Ray localRay = GlobalToLocal(ray);
			Vec3 v(0.0f, 1.0f, 0.0f);
			Vec3 CO = localRay.origin.GetPosition() - position;

			float a = (pow(localRay.dir.dot(v), 2)) - pow(cos(angle), 2);
			float b = 2 * (localRay.dir.dot(v) * (CO.dot(v)) - localRay.dir.dot(CO * pow(cos(angle), 2)));
			float c = pow(CO.dot(v), 2) - CO.dot(CO * pow(cos(angle), 2));

			float delta = pow(b, 2) - 4 * a * c;

			if (delta > 0.0f)
			{
				float t1 = (-b - sqrt(delta)) / 2 * a;
				float t2 = (-b + sqrt(delta)) / 2 * a;

				Vec3 p1 = localRay.origin.GetPosition() + t1 * localRay.dir;
				Vec3 p2 = localRay.origin.GetPosition() + t2 * localRay.dir;

				if ((p1 - position).dot(v) > 0.0f)
				{
					impact = LocalToGlobal(p1);
					return true;
				}
				else
				{
					if ((p2 - position).dot(v) > 0.0f)
					{
						impact = LocalToGlobal(p2);
						return true;
					}
				}
			}
			else
			{
				if (delta == 0.0f)
				{
					float t = -b / 2 * a;

					Vec3 impactLoc = localRay.origin.GetPosition() + t * localRay.dir;
					impact = LocalToGlobal(impactLoc);

					return true;
				}
				else
				{
					return false;
				}
			}
		}

		//fonction pour récupérer la normale au point d'impact
		Ray getNormal(const outils::Point& impact, const outils::Point& o)const
		{

		}
};