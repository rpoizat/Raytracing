#pragma once
#include "Vec3.hpp";

//classe mère Entite qui regroupe l'ensemble des objets disposables dans la scène
class Entite
{
	protected:
		vec3 position;
	public:

		Entite() {};
		Entite(vec3 p)
		{
			position = p;
		}

		~Entite() {};

		//chaque entité dispose d'une position
		vec3 GetPosition()
		{
			return position;
		}
};