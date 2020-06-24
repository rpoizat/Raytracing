#pragma once
#include "Vec3.hpp"

namespace outils {

	class Material {

	public:

		color ka;
		color kd;
		color ks;

		// Positif, plus la valeur est grande plus la surface est brillante.
		float shininess;

		Material() {

		}

		Material(color composanteAmbiante, color composanteDiffuse, color composanteSpeculaire, float laShininess) {
			ka = composanteAmbiante * (1.0f / 255.0f);
			kd = composanteDiffuse * (1.0f / 255.0f);
			ks = composanteSpeculaire * (1.0f / 255.0f);
			shininess = laShininess;
		}


	};


}
