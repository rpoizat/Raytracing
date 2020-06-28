#pragma once
#include "Entite.hpp"

class Triangle : public Entite
{
	public:

		//les trois sommets du triangle
		Vec3 s1, s2, s3;

		//constructeurs
		Triangle() {};
		Triangle(Vec3 som1, Vec3 som2, Vec3 som3, Vec3 p, Vec3 rot, Material m) : Entite(p, rot, m), s1(som1), s2(som2), s3(som3){}

		//fonction d'intersection
		bool Intersection(const Ray& ray, outils::Point& impact)const override
		{
			Vec3 s1s2 = s1 - s2;
			Vec3 s1s3 = s1 - s3;
			Vec3 normal = s1s2.Cross(s1s3);
			normal.normalize();

			if (normal[0] == -0.0f)
			{
				normal[0] = abs(normal[0]);
			}

			if (normal[1] == -0.0f)
			{
				normal[1] = abs(normal[1]);
			}

			//si le rayon est orthogonal à la normale du plan du triangle, alors il est parallèle au triangle et ne le touchera jamais
			if (normal.dot(ray.dir) == 0.0f)
			{
				return false;
			}
			else
			{
				//sinon on calcule son point d'impact sur le plan du triangle
				float t = (normal.dot(s1) - normal.dot(ray.origin.GetPosition())) / normal.dot(ray.dir);

				Vec3 imp = ray.origin.GetPosition() + t * ray.dir;

				impact[0] = imp[0];
				impact[1] = imp[1];
				impact[2] = imp[2];
				
				//déterminer si le point d'impact est dans le triangle
				if ((s1 - s2).Cross((impact.GetPosition() - s1)).dot(normal) >= 0.0f &&
					(s2 - s3).Cross((impact.GetPosition() - s2)).dot(normal) >= 0.0f &&
					(s3 - s1).Cross((impact.GetPosition() - s3)).dot(normal) >= 0.0f)
				{
					impact[0] = -impact[0];
					impact[1] = -impact[1];
					impact[2] = -impact[2];
					return true;
				}
				else
				{
					//tester avec la normale inversée pour traiter l'autre face du triangle
					normal[0] = -normal[0];
					normal[1] = -normal[1];
					normal[2] = -normal[2];

					if ((s1 - s2).Cross((impact.GetPosition() - s1)).dot(normal) >= 0.0f &&
						(s2 - s3).Cross((impact.GetPosition() - s2)).dot(normal) >= 0.0f &&
						(s3 - s1).Cross((impact.GetPosition() - s3)).dot(normal) >= 0.0f)
					{
						return true;
					}
					else return false;
					return false;
				}
			}
		}

		//fonction pour avoir la normale du triangle qui est la normal du plan contenant le triangle
		Ray getNormal(const outils::Point& p, const outils::Point& o)const
		{
			Vec3 s1s2 = s2 - s1;
			Vec3 s1s3 = s3 - s1;
			Vec3 normal = s1s2.Cross(s1s3);
			normal.normalize();

			if (normal[0] == -0.0f)
			{
				normal[0] = abs(normal[0]);
			}

			if (normal[1] == -0.0f)
			{
				normal[1] = abs(normal[1]);
			}

			return Ray(p, normal);
		}
};