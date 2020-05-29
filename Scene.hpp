#pragma once
#include <opencv2/core.hpp>
#include <fstream>
#include "opencv2/imgproc.hpp"
#include "Sphere.hpp"
#include "Light.hpp"
#include "FonctionDiverses.hpp"
using namespace std;

using namespace std;
using namespace cv;

//classe contenant la configuration lue dans le fichier donn� en param�tre
class Scene
{
	private:
		vector<Entite*> listeObjets;
		vector<Entite*> listeLumieres;

	public:

		Scene(){}

		~Scene()
		{
			for (int i = listeObjets.size()-1; i >= 0; i--)
			{
				delete listeObjets[i];
			}

			for (int i = listeLumieres.size() - 1; i >= 0; i--)
			{
				delete listeLumieres[i];
			}
		}

		//fonction pour ajouter un objet � la sc�ne
		void ajoutObjet(Sphere e)
		{
			Entite* newObj = new Sphere(e.GetPosition(), e.GetRayon());
			listeObjets.push_back(newObj);
		}

		//fonction pour ajouter une lumi�re � la sc�ne
		void ajoutLumiere(Light e)
		{
			Entite* newLight = new Light(e.GetPosition(), e.GetDiffuse(), e.GetSpecular());
			listeLumieres.push_back(newLight);
		}

		//fonction de lecture du fichier de la scene donn� en param�tre
		void LectureConfiguration(string cheminFichier)
		{
			ifstream lecteur(cheminFichier);

			if (lecteur.is_open()) 
			{
				//lecture du fichier ligne par ligne
				string ligne;
				while (getline(lecteur, ligne)) 
				{
					ProcessLigne(ligne);
				}

				lecteur.close();
			}
			else
			{
				cout << "Erreur a l'ouverture du fichier : " << cheminFichier << endl;
			}
		}

		//fonction pour traiter la ligne en cours du fichier de configuration
		void ProcessLigne(string l)
		{
			vector<string> donnees = explode(l, ':');

			switch (str2int(donnees.at(0).c_str()))
			{
				//cr�ation d'une sph�re
				case str2int("sphere"):
				{
					//r�cup�ration de la position
					vector<string> donneesPosition = explode(donnees.at(1), '_');

					Vec3 position;
					//si on a bien toutes les donn�es pour la position
					if (donneesPosition.size() == 3)
					{
						position[0] = stof(donneesPosition.at(0));
						position[1] = stof(donneesPosition.at(1));
						position[2] = stof(donneesPosition.at(2));
					}
					else
					{
						cout << "Donnees invalides sur la position de l'objet de type Sphere, l'objet sera en 0 1 1 par defaut" << endl;
						position[0] = 0;
						position[1] = 1;
						position[2] = 1;
					}

					float rayon;

					//r�cup�ration du rayon, sinon initialis� � 1 par d�faut
					if (!donnees.at(2).empty())
					{
						rayon = stof(donnees.at(2));
					}
					else rayon = 1;

					//cr�ation de la sph�re
					Sphere s(position, rayon);

					//ajout de la sph�re � la liste des objets
					ajoutObjet(s);

					cout << "ajout d'une sphere de rayon " << s.GetRayon() << " a la position " << s.GetPosition() << endl;

					break;
				}
				//cr�ation d'une lumi�re
				case str2int("light"):
				{
					//r�cup�ration de la position
					vector<string> donneesPosition = explode(donnees.at(1), '_');

					Vec3 position;
					//si on a bien toutes les donn�es pour la position
					if (donneesPosition.size() == 3)
					{
						position[0] = stof(donneesPosition.at(0));
						position[1] = stof(donneesPosition.at(1));
						position[2] = stof(donneesPosition.at(2));
					}
					else
					{
						cout << "Donnees invalides sur la position de l'objet de type Lumiere, l'objet sera en 0 0 0 par defaut" << endl;
						position[0] = 0;
						position[1] = 0;
						position[2] = 0;
					}

					//r�cup�ration de la composante diffuse
					vector<string> donneesDiffuse = explode(donnees.at(2), '_');

					color compDiffuse;
					//si on a bien toutes les donn�es pour la composante diffuse
					if (donneesDiffuse.size() == 3)
					{
						compDiffuse[0] = stof(donneesDiffuse.at(0));
						compDiffuse[1] = stof(donneesDiffuse.at(1));
						compDiffuse[2] = stof(donneesDiffuse.at(2));
					}
					else
					{
						compDiffuse[0] = 255;
						compDiffuse[1] = 255;
						compDiffuse[2] = 255;
						cout << "donnees invalides sur la composante diffuse de l'objet de type lumiere, composante mise a " << compDiffuse << "par defaut" << endl;
					}

					//r�cup�ration de la composante sp�culaire
					vector<string> donneesSpecular = explode(donnees.at(2), '_');

					color compSpecular;
					//si on a bien toutes les donn�es pour la composante diffuse
					if (donneesSpecular.size() == 3)
					{
						compSpecular[0] = stof(donneesSpecular.at(0));
						compSpecular[1] = stof(donneesSpecular.at(1));
						compSpecular[2] = stof(donneesSpecular.at(2));
					}
					else
					{
						compSpecular[0] = 255;
						compSpecular[1] = 255;
						compSpecular[2] = 255;
						cout << "donnees invalides sur la composante speculaire de l'objet de type lumiere, composante mise a " << compSpecular << "par defaut" << endl;
					}

					//cr�ation de la lumi�re
					Light l(position, compDiffuse, compSpecular);

					cout << "Ajout d'une lumiere en " << l.GetPosition() << " avec le Diffuse a " << l.GetDiffuse() << " et le specular a " << l.GetSpecular() << endl;
					//ajout de la lumi�re � la sc�ne
					ajoutLumiere(l);

					break;
				}
			}
		}

		//fonction pour d�finir la couleur du  pixel correspondant au Ray donn� en param�tre
		color RayTrace(Ray r)
		{
			for (int i = 0; i < listeObjets.size(); i++)
			{
				outils::Point impact;

				if (listeObjets[i]->Intersection(r, impact))
				{
					return color(255.f, 255.f, 255.f);
				}
				else
				{
					return color(255.f, 0.f, 0.f);
				}
			}
		}
};