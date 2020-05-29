#pragma once
#include "Entite.hpp";
using namespace std;

//Classe définissant la lumière, dérive d'Entite et y ajoute les composantes diffuse et specular pour l'illumination de Phong
class Light : public Entite
{
	private:
		color compDiffuse;
		color compSpecular;

	public:
		Light() {};
		Light(Vec3 p, color cd, color cs) : Entite(p), compDiffuse(cd), compSpecular(cs){}

		color GetDiffuse()
		{
			return compDiffuse;
		}

		color GetSpecular()
		{
			return compSpecular;
		}
};