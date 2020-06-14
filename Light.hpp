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
		Light(Vec3 p, color cd, color cs) : Entite(p, Vec3(0.f,0.f,0.f), color(0.f, 0.f, 0.f)), compDiffuse(cd), compSpecular(cs){}

		color GetDiffuse()
		{
			return compDiffuse;
		}

		color GetSpecular()
		{
			return compSpecular;
		}

		Vec3 getVectorToLight(outils::Point base) {

			Vec3 vectorToLight(position[0] - base[0], position[1] - base[1], position[2] - base[2]);

			return vectorToLight;

		}

		bool Intersection(const Ray& ray, outils::Point& impact) const
		{
			return false;
		}
};