#pragma once
#include "Vec3.hpp"

namespace outils {

	class Material {

	public:

		color ka;
		color kd;
		color ks;

		float shininess;

		Material() {

		}

		Material(color composanteAmbiante, color composanteDiffuse, color composanteSpeculaire, float laShininess) {
			ka = composanteAmbiante;
			kd = composanteDiffuse;
			ks = composanteSpeculaire;
			shininess = laShininess;
		}


	};


}
