#pragma once
#include "Vec3.hpp";

//classe m�re Entite qui regroupe l'ensemble des objets disposables dans la sc�ne
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

		//chaque entit� dispose d'une position
		vec3 GetPosition()
		{
			return position;
		}
};