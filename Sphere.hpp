#pragma once
#include "Entite.hpp";
using namespace std;

//classe d�finissant la sph�re d�riv�e d'Entit� - Dispose d'un rayon en plus de sa position
class Sphere : public Entite
{
	private:
		float rayon;

	public:

		Sphere() {};
		Sphere(vec3 p, float r) : Entite(p), rayon(r){}

		//getteur du rayon
		float GetRayon()
		{
			return rayon;
		}
};