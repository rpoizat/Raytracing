#pragma once
#include "Entite.hpp"

class ConeInf : public Entite
{
	private:

		float angle;

	public:

		//constructeur
		ConeInf() {};
		ConeInf(Vec3 p, Vec3 rot, float a, Material m) : Entite(p, rot, m)
		{
			angle = a * 3.1415 / 180.0f;
		}

		//getteur sur l'angle
		float GetAngle()
		{
			return angle;
		}

		//fonction d'intersection
		bool Intersection(const Ray& ray, outils::Point& impact) const override
		{
			Ray localRay = GlobalToLocal(ray);

			Vec3 v(0.0f, -1.0f, 0.0f);
			Vec3 positionLoc(0.0f, 0.0f, 0.0f);
			Vec3 CO(localRay.origin.GetPosition() - positionLoc);

			float a = (pow(localRay.dir.dot(v), 2)) - pow(cos(angle), 2);
			float b = 2 * (localRay.dir.dot(v) * (CO.dot(v)) - localRay.dir.dot(CO * pow(cos(angle), 2)));
			float c = pow(CO.dot(v), 2) - CO.dot(CO * pow(cos(angle), 2));

			float delta = pow(b, 2) - (4 * a * c);

			if (delta > 0.0f)
			{
				float t1 = (-b - sqrt(delta)) / (2 * a);
				float t2 = (-b + sqrt(delta)) / (2 * a);

				float t;

				if (t1 < t2 && t1 > 0.f) t = t1;
				else if (t1 > 0.f && t2 < 0.f) t = t1;
				else t = t2;

				if (t > 0)
				{
					impact = localRay.origin.GetPosition() + t * localRay.dir;

					//éviter le double cone
					if (impact.dot(v) > 0.0f)
					{
						impact = LocalToGlobal(impact);
						return true;
					}
					else
					{
						return false;
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
			return false;
		}

		//fonction pour récupérer la normale au point d'impact
		Ray getNormal(const outils::Point& impact, const outils::Point& o)const
		{
			outils::Point localImpact = GlobalToLocal(impact);
			outils::Point localObservator = GlobalToLocal(o);

			Vec3 v(0.f, -1.0f, 0.0f);

			Vec3 n = ((localImpact.GetPosition() * v.dot(localImpact.GetPosition())) / localImpact.GetPosition().dot(localImpact.GetPosition())) - v;

			Ray normal(localImpact, n);
			normal = LocalToGlobal(normal);
			normal.normalize();
			return normal;
		}
};