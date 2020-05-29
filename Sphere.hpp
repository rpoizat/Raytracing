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
		}
};