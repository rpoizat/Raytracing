#pragma once
#include "Entite.hpp";
using namespace std;

//Classe définissant la lumière, dérive d'Entite et y ajoute les composantes diffuse et specular pour l'illumination de Phong
class Light : public Entite
{
	private:
		vec3 compDiffuse;
		vec3 compSpecular;

	public:
		Light() {};
		Light(vec3 p, vec3 cd, vec3 cs) : Entite(p), compDiffuse(cd), compSpecular(cs){}

		vec3 GetDiffuse()
		{
			return compDiffuse;
		}

		vec3 GetSpecular()
		{
			return compSpecular;
		}
};