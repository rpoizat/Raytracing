#pragma once
#include <opencv2/core.hpp>
#include <fstream>
#include "opencv2/imgproc.hpp"
#include "Sphere.hpp"
#include "Light.hpp"
#include "FonctionDiverses.hpp"


using namespace std;
using namespace cv;

//classe contenant la configuration lue dans le fichier donn� en param�tre
class Scene
{
	private:
		vector<Entite> listeObjets;
		vector<Entite> listeLumieres;

	public:

		Scene(){}

		//fonction pour ajouter un objet � la sc�ne
		void ajoutObjet(Entite e)
		{
			listeObjets.push_back(e);
		}

		//fonction pour ajouter une lumi�re � la sc�ne
		void ajoutLumiere(Entite e)
		{
			listeLumieres.push_back(e);
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

					vec3 position;
					//si on a bien toutes les donn�es pour la position
					if (donneesPosition.size() == 3)
					{
						position.x = stof(donneesPosition.at(0));
						position.y = stof(donneesPosition.at(1));
						position.z = stof(donneesPosition.at(2));
					}
					else
					{
						cout << "Donnees invalides sur la position de l'objet de type Sphere, l'objet sera en 0 1 1 par defaut" << endl;
						position.x = 0;
						position.y = 1;
						position.z = 1;
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

					vec3 position;
					//si on a bien toutes les donn�es pour la position
					if (donneesPosition.size() == 3)
					{
						position.x = stof(donneesPosition.at(0));
						position.y = stof(donneesPosition.at(1));
						position.z = stof(donneesPosition.at(2));
					}
					else
					{
						cout << "Donnees invalides sur la position de l'objet de type Lumiere, l'objet sera en 0 0 0 par defaut" << endl;
						position.x = 0;
						position.y = 0;
						position.z = 0;
					}

					//r�cup�ration de la composante diffuse
					vector<string> donneesDiffuse = explode(donnees.at(2), '_');

					vec3 compDiffuse;
					//si on a bien toutes les donn�es pour la composante diffuse
					if (donneesDiffuse.size() == 3)
					{
						compDiffuse.r = stof(donneesDiffuse.at(0));
						compDiffuse.g = stof(donneesDiffuse.at(1));
						compDiffuse.b = stof(donneesDiffuse.at(2));
					}
					else
					{
						compDiffuse.r = 255;
						compDiffuse.g = 255;
						compDiffuse.b = 255;
						cout << "donnees invalides sur la composante diffuse de l'objet de type lumiere, composante mise a " << compDiffuse << "par defaut" << endl;
					}

					//r�cup�ration de la composante sp�culaire
					vector<string> donneesSpecular = explode(donnees.at(2), '_');

					vec3 compSpecular;
					//si on a bien toutes les donn�es pour la composante diffuse
					if (donneesSpecular.size() == 3)
					{
						compSpecular.r = stof(donneesSpecular.at(0));
						compSpecular.g = stof(donneesSpecular.at(1));
						compSpecular.b = stof(donneesSpecular.at(2));
					}
					else
					{
						compSpecular.r = 255;
						compSpecular.g = 255;
						compSpecular.b = 255;
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
};