#pragma once
#include <opencv2/core.hpp>
#include <fstream>
#include "opencv2/imgproc.hpp"
#include "Sphere.hpp"
#include "Light.hpp"
#include "FonctionDiverses.hpp"


using namespace std;
using namespace cv;

//classe contenant la configuration lue dans le fichier donné en paramètre
class Scene
{
	private:
		vector<Entite> listeObjets;
		vector<Entite> listeLumieres;

	public:

		Scene(){}

		//fonction pour ajouter un objet à la scène
		void ajoutObjet(Entite e)
		{
			listeObjets.push_back(e);
		}

		//fonction pour ajouter une lumière à la scène
		void ajoutLumiere(Entite e)
		{
			listeLumieres.push_back(e);
		}

		//fonction de lecture du fichier de la scene donné en paramètre
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
				//création d'une sphère
				case str2int("sphere"):
				{
					//récupération de la position
					vector<string> donneesPosition = explode(donnees.at(1), '_');

					vec3 position;
					//si on a bien toutes les données pour la position
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

					//récupération du rayon, sinon initialisé à 1 par défaut
					if (!donnees.at(2).empty())
					{
						rayon = stof(donnees.at(2));
					}
					else rayon = 1;

					//création de la sphère
					Sphere s(position, rayon);

					//ajout de la sphère à la liste des objets
					ajoutObjet(s);

					cout << "ajout d'une sphere de rayon " << s.GetRayon() << " a la position " << s.GetPosition() << endl;

					break;
				}
				//création d'une lumière
				case str2int("light"):
				{
					//récupération de la position
					vector<string> donneesPosition = explode(donnees.at(1), '_');

					vec3 position;
					//si on a bien toutes les données pour la position
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

					//récupération de la composante diffuse
					vector<string> donneesDiffuse = explode(donnees.at(2), '_');

					vec3 compDiffuse;
					//si on a bien toutes les données pour la composante diffuse
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

					//récupération de la composante spéculaire
					vector<string> donneesSpecular = explode(donnees.at(2), '_');

					vec3 compSpecular;
					//si on a bien toutes les données pour la composante diffuse
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

					//création de la lumière
					Light l(position, compDiffuse, compSpecular);

					cout << "Ajout d'une lumiere en " << l.GetPosition() << " avec le Diffuse a " << l.GetDiffuse() << " et le specular a " << l.GetSpecular() << endl;
					//ajout de la lumière à la scène
					ajoutLumiere(l);

					break;
				}
			}
		}
};