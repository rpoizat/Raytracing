#pragma once
#include <opencv2/core.hpp>
#include <fstream>
#include "opencv2/imgproc.hpp"
#include "Sphere.hpp"
#include "Cube.hpp"
#include "CylindreInf.hpp"
#include "PlanInf.hpp"
#include "Light.hpp"
#include "FonctionDiverses.hpp"

using namespace std;
using namespace cv;

//classe contenant la configuration lue dans le fichier donné en paramètre
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

		//fonction pour ajouter un objet à la scène
		void ajoutObjet(Sphere e)
		{
			Entite* newObj = new Sphere(e.GetPosition(), e.GetRotation(), e.GetRayon());
			listeObjets.push_back(newObj);
		}

		//fonction pour ajouter une lumière à la scène
		void ajoutLumiere(Light e)
		{
			Entite* newLight = new Light(e.GetPosition(), e.GetDiffuse(), e.GetSpecular());
			listeLumieres.push_back(newLight);
		}

		//fonction pour ajouter un cube à la scène
		void ajoutObjet(Cube e)
		{
			Entite* newObj = new Cube(e.GetPosition(), e.GetRotation(), e.GetCote());
			listeObjets.push_back(newObj);
		}

		//fonction pour ajouter un cylindre infini à la scène
		void ajoutObjet(CylindreInf e)
		{
			Entite* newObj = new CylindreInf(e.GetPosition(), e.GetRotation(), e.GetRayon());
			listeObjets.push_back(newObj);
		}

		//fonction pour ajouter un plan infini à la scène
		void ajoutObjet(PlanInf e)
		{
			Entite* newObj = new PlanInf(e.GetPosition(), e.GetRotation());
			listeObjets.push_back(newObj);
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

					Vec3 position;
					//si on a bien toutes les données pour la position
					if (donneesPosition.size() == 3)
					{
						position[0] = -stof(donneesPosition.at(0));
						position[1] = -stof(donneesPosition.at(1));
						position[2] = stof(donneesPosition.at(2));
					}
					else
					{
						cout << "Donnees invalides sur la position de l'objet de type Sphere, l'objet sera en 0 1 -10 par defaut" << endl;
						position[0] = 0.f;
						position[1] = 1.f;
						position[2] = -10.f;
					}

					//récupération de la rotation
					vector<string> donneesRotation = explode(donnees.at(2), '_');

					Vec3 rotation;
					//si on a bien toutes les données pour la position
					if (donneesRotation.size() == 3)
					{
						rotation[0] = stof(donneesRotation.at(0));
						rotation[1] = stof(donneesRotation.at(1));
						rotation[2] = stof(donneesRotation.at(2));
					}
					else
					{
						cout << "Donnees invalides sur la rotation de l'objet de type Sphere, la rotation sera en 0 0 0 par defaut" << endl;
						rotation[0] = 0.f;
						rotation[1] = 0.f;
						rotation[2] = 0.f;
					}

					float rayon;

					//récupération du rayon, sinon initialisé à 1 par défaut
					if (!donnees.at(3).empty())
					{
						rayon = stof(donnees.at(3));
					}
					else rayon = 1.f;

					//création de la sphère
					Sphere s(position, rotation, rayon);

					//ajout de la sphère à la liste des objets
					ajoutObjet(s);

					cout << "ajout d'une sphere de rayon " << s.GetRayon() << " a la position " << s.GetPosition() << " de rotation " << s.GetRotation() << endl;

					break;
				}

				//création d'un cube
				case str2int("cube"):
				{
					//récupération de la position
					vector<string> donneesPosition = explode(donnees.at(1), '_');

					Vec3 position;
					//si on a bien toutes les données pour la position
					if (donneesPosition.size() == 3)
					{
						position[0] = -stof(donneesPosition.at(0));
						position[1] = -stof(donneesPosition.at(1));
						position[2] = stof(donneesPosition.at(2));
					}
					else
					{
						cout << "Donnees invalides sur la position de l'objet de type Cube, l'objet sera en 0 1 -10 par defaut" << endl;
						position[0] = 0.f;
						position[1] = 1.f;
						position[2] = -10.f;
					}

					//récupération de la rotation
					vector<string> donneesRotation = explode(donnees.at(2), '_');

					Vec3 rotation;
					//si on a bien toutes les données pour la position
					if (donneesRotation.size() == 3)
					{
						rotation[0] = stof(donneesRotation.at(0));
						rotation[1] = stof(donneesRotation.at(1));
						rotation[2] = stof(donneesRotation.at(2));
					}
					else
					{
						cout << "Donnees invalides sur la rotation de l'objet de type Cube, la rotation sera en 0 0 0 par defaut" << endl;
						rotation[0] = 0.f;
						rotation[1] = 0.f;
						rotation[2] = 0.f;
					}

					float cote;

					//récupération du cote, sinon initialisé à 1 par défaut
					if (!donnees.at(3).empty())
					{
						cote = stof(donnees.at(3));
					}
					else cote = 1.f;

					//création du cube
					Cube c(position, rotation, cote);

					//ajout du cube à la liste des objets
					ajoutObjet(c);

					cout << "ajout d'une cube de cote " << c.GetCote() << " a la position " << c.GetPosition() << " de rotation " << c.GetRotation() << endl;

					break;
				}

				//création d'un cylindre infini
				case str2int("cylindre"):
				{
					//récupération de la position
					vector<string> donneesPosition = explode(donnees.at(1), '_');

					Vec3 position;
					//si on a bien toutes les données pour la position
					if (donneesPosition.size() == 3)
					{
						position[0] = -stof(donneesPosition.at(0));
						position[1] = -stof(donneesPosition.at(1));
						position[2] = stof(donneesPosition.at(2));
					}
					else
					{
						cout << "Donnees invalides sur la position de l'objet de type Cylindre, l'objet sera en 0 1 -10 par defaut" << endl;
						position[0] = 0.f;
						position[1] = 1.f;
						position[2] = -10.f;
					}

					//récupération de la rotation
					vector<string> donneesRotation = explode(donnees.at(2), '_');

					Vec3 rotation;
					//si on a bien toutes les données pour la position
					if (donneesRotation.size() == 3)
					{
						rotation[0] = stof(donneesRotation.at(0));
						rotation[1] = stof(donneesRotation.at(1));
						rotation[2] = stof(donneesRotation.at(2));
					}
					else
					{
						cout << "Donnees invalides sur la rotation de l'objet de type Cylindre, la rotation sera en 0 0 0 par defaut" << endl;
						rotation[0] = 0.f;
						rotation[1] = 0.f;
						rotation[2] = 0.f;
					}

					float rayon;

					//récupération du rayon, sinon initialisé à 1 par défaut
					if (!donnees.at(3).empty())
					{
						rayon = stof(donnees.at(3));
					}
					else rayon = 1.f;

					//création de la sphère
					CylindreInf c(position, rotation, rayon);

					//ajout du cylindre à la liste des objets
					ajoutObjet(c);

					cout << "ajout d'un cylindre infini de rayon " << c.GetRayon() << " a la position " << c.GetPosition() << " de rotation " << c.GetRotation() << endl;

					break;
				}

				//création d'un plan infini
				case str2int("plan"):
				{
					//récupération de la position
					vector<string> donneesPosition = explode(donnees.at(1), '_');

					Vec3 position;
					//si on a bien toutes les données pour la position
					if (donneesPosition.size() == 3)
					{
						position[0] = -stof(donneesPosition.at(0));
						position[1] = -stof(donneesPosition.at(1));
						position[2] = stof(donneesPosition.at(2));
					}
					else
					{
						cout << "Donnees invalides sur la position de l'objet de type Plan, l'objet sera en 0 1 -10 par defaut" << endl;
						position[0] = 0.f;
						position[1] = 1.f;
						position[2] = -10.f;
					}

					//récupération de la rotation
					vector<string> donneesRotation = explode(donnees.at(2), '_');

					Vec3 rotation;
					//si on a bien toutes les données pour la position
					if (donneesRotation.size() == 3)
					{
						rotation[0] = stof(donneesRotation.at(0));
						rotation[1] = stof(donneesRotation.at(1));
						rotation[2] = stof(donneesRotation.at(2));
					}
					else
					{
						cout << "Donnees invalides sur la rotation de l'objet de type Plan, la rotation sera en 0 0 0 par defaut" << endl;
						rotation[0] = 0.f;
						rotation[1] = 0.f;
						rotation[2] = 0.f;
					}

					//création de la sphère
					PlanInf p(position, rotation);

					//ajout du cylindre à la liste des objets
					ajoutObjet(p);

					cout << "ajout d'un plan infini de rayon a la position " << p.GetPosition() << " de rotation " << p.GetRotation() << endl;

					break;
				}

				//création d'une lumière
				case str2int("light"):
				{
					//récupération de la position
					vector<string> donneesPosition = explode(donnees.at(1), '_');

					Vec3 position;
					//si on a bien toutes les données pour la position
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

					//récupération de la composante diffuse
					vector<string> donneesDiffuse = explode(donnees.at(2), '_');

					color compDiffuse;
					//si on a bien toutes les données pour la composante diffuse
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

					//récupération de la composante spéculaire
					vector<string> donneesSpecular = explode(donnees.at(2), '_');

					color compSpecular;
					//si on a bien toutes les données pour la composante diffuse
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

					//création de la lumière
					Light l(position, compDiffuse, compSpecular);

					cout << "Ajout d'une lumiere en " << l.GetPosition() << " avec le Diffuse a " << l.GetDiffuse() << " et le specular a " << l.GetSpecular() << endl;
					//ajout de la lumière à la scène
					ajoutLumiere(l);

					break;
				}
			}
		}

		//fonction pour définir la couleur du  pixel correspondant au Ray donné en paramètre
		color RayTrace(Ray r)
		{
			for (int i = 0; i < listeObjets.size(); i++)
			{
				outils::Point impact;

				if (listeObjets[i]->Intersection(r, impact))
				{
					return color(255.f, 255.f, 255.f);
				}
			}
			return color(255.f, 0.f, 0.f);
		}
};