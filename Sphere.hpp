﻿#pragma once

#include "Entite.hpp";


using namespace std;

//classe définissant la sphère dérivée d'Entité - Dispose d'un rayon en plus de sa position
class Sphere : public Entite
{
	private:
		float rayon;
		Material material;

	public:

		Sphere() {};
		Sphere(Vec3 p, Vec3 rot, color c, float r, Material m) : Entite(p, rot, c, m), rayon(r){}

		//getteur du rayon
		float GetRayon()
		{
			return rayon;
		}


		//fonction d'intersection entre la sphère et le rayon donné en paramètre
		bool Intersection(const Ray& ray, outils::Point& impact) const override
		{
			Ray localR = GlobalToLocal(ray);

			float a = pow(localR.dir[0], 2) + pow(localR.dir[1], 2) + pow(localR.dir[2], 2);
			float b = 2 * (localR.origin[0] * localR.dir[0] + localR.origin[1] * localR.dir[1] + localR.origin[2] * localR.dir[2]);
			float c = pow(localR.origin[0], 2) + pow(localR.origin[1], 2) + pow(localR.origin[2], 2) - 1;

			float delta = pow(b, 2) - 4 * a*c;

			float t1 = (-b + sqrt(delta)) / (2 * a);
			float t2 = (-b - sqrt(delta)) / (2 * a);

			float t;

			if (t1 < t2 && t1 > 0.f) t = t1;
			else if (t1 > 0.f && t2 < 0.f) t = t1;
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

		Ray getNormal(const outils::Point& p, const outils::Point& o) const
		{

			outils::Point localObservator = GlobalToLocal(o);

			outils::Point newP = GlobalToLocal(p);

			Vec3 localImpact(newP[0], newP[1], newP[2]);

			if (localImpact.dot(localObservator.GetPosition()) >= 0) {


				Ray lereturn = LocalToGlobal(Ray(localImpact, localImpact * 1));
				lereturn.normalize();
				return lereturn;

			}
			else {

				Ray lereturn = LocalToGlobal(Ray(localImpact, localImpact * -1));
				lereturn.normalize();
				return lereturn;

			}

		}
};