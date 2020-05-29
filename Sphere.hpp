#pragma once

#include "Entite.hpp";

using namespace std;

//classe définissant la sphère dérivée d'Entité - Dispose d'un rayon en plus de sa position
class Sphere : public Entite
{
	private:
		float rayon;

	public:

		Sphere() {};
		Sphere(Vec3 p, float r) : Entite(p), rayon(r){}

		//getteur du rayon
		float GetRayon()
		{
			return rayon;

			GlobalToLocal(GetPosition());
		}

		void AfficherMatTrans()
		{
			for (int i = 0; i < trans.rows; i++)
			{
				for (int j = 0; j < trans.cols; j++)
				{
					cout << trans.at<float>(i, j) << " ";
				}

				cout << endl;
			}
		}

		void AfficherMatInv()
		{
			for (int i = 0; i < inv.rows; i++)
			{
				for (int j = 0; j < inv.cols; j++)
				{
					cout << inv.at<float>(i, j) << " ";
				}

				cout << endl;
			}
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