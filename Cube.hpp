#pragma once
#include "Entite.hpp";

class Cube : public Entite
{
private:
	float cote;

public:

	//constructeurs
	Cube() {};
	Cube(Vec3 p, Vec3 rot, color co, float c, Material m) : Entite(p, rot, co, m), cote(c) {}

	//getteur sur la cote du carré
	float GetCote()
	{
		return cote;
	}

    Ray getNormal(const outils::Point& p, const outils::Point& o)const {


        outils::Point localImpact = GlobalToLocal(p);
		outils::Point localObservator = GlobalToLocal(o);

        float z;

        if (abs(localImpact[0]) > abs(localImpact[1]) && abs(localImpact[0]) > abs(localImpact[2])) {


            if (localObservator[0] >= 0) {
                z = localImpact[0];
                Vec3 v(1, 0, 0);
				Ray lereturn = LocalToGlobal(Ray(localImpact, v));
				lereturn.normalize();
                return lereturn;
            }

            else {
                z = localImpact[0];
				Vec3 v(-1, 0, 0);
				Ray lereturn = LocalToGlobal(Ray(localImpact, v));
				lereturn.normalize();
				return lereturn;
            }


        }

        if (abs(localImpact[1]) > abs(localImpact[0]) && abs(localImpact[1]) > abs(localImpact[2])) {

            if (localObservator[1] >= 0) {
                z = localImpact[1];
				Vec3 v(0, 1, 0);
				Ray lereturn = LocalToGlobal(Ray(localImpact, v));
				lereturn.normalize();
				return lereturn;
            }

            else {
                z = localImpact[1];
				Vec3 v(0, -1, 0);
				Ray lereturn = LocalToGlobal(Ray(localImpact, v));
				lereturn.normalize();
				return lereturn;
            }

        }

        if (abs(localImpact[2]) > abs(localImpact[0]) && abs(localImpact[2]) > abs(localImpact[1])) {

            if (localObservator[2] >= 0) {
                z = localImpact[2];
				Vec3 v(0, 0, 1);
				Ray lereturn = LocalToGlobal(Ray(localImpact, v));
				lereturn.normalize();
				return lereturn;
            }

            else {
                z = localImpact[2];
				Vec3 v(0, 0, -1);
				Ray lereturn = LocalToGlobal(Ray(localImpact, v));
				lereturn.normalize();
				return lereturn;
            }

        }

    }

	//fonction d'intersection du cube avec le rayon donné en paramètre
	bool Intersection(const Ray& ray, outils::Point& impact)const override
	{
		//Passage en locale
		Ray localRay = GlobalToLocal(ray);

		outils::Point cubeMin(-cote/2, -cote/2, -cote/2);
		outils::Point cubeMax(cote/2, cote/2, cote/2);

		float tXmin, tXmax, tYmin, tYmax, tZmin, tZmax = 0.0f;

		tXmin = (cubeMin[0] - localRay.origin[0]) / localRay.dir[0];
		tXmax = (cubeMax[0] - localRay.origin[0]) / localRay.dir[0];
		if (tXmin > tXmax)
		{
			float tmp = tXmin;
			tXmin = tXmax;
			tXmax = tmp;
		}

		tYmin = (cubeMin[1] - localRay.origin[1]) / localRay.dir[1];
		tYmax = (cubeMax[1] - localRay.origin[1]) / localRay.dir[1];

		if (tYmin > tYmax)
		{
			float tmp = tYmin;
			tYmin = tYmax;
			tYmax = tmp;
		}

		if (tXmin > tYmax || tYmin > tXmax) return false;

		if (tYmin > tXmin) tXmin = tYmin;

		if (tYmax < tXmax) tXmax = tYmax;

		tZmin = (cubeMin[2] - localRay.origin[2]) / localRay.dir[2];
		tZmax = (cubeMax[2] - localRay.origin[2]) / localRay.dir[2];

		if (tZmin > tZmax)
		{
			float tmp = tZmin;
			tZmin = tZmax;
			tZmax = tmp;
		}

		if (tXmin > tZmax || tZmin > tXmax) return false;

		if (tZmin > tXmin) tXmin = tZmin;

		if (tZmax < tXmax) tXmax = tZmax;

		float t = tXmax > tXmin ? tXmin : tXmax;

		impact[0] = localRay.origin[0] + t * localRay.dir[0];
		impact[1] = localRay.origin[1] + t * localRay.dir[1];
		impact[2] = localRay.origin[2] + t * localRay.dir[2];

		impact = LocalToGlobal(impact);
		return true;
	}
};