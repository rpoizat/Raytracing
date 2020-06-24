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
	vector<Light*> listeLumieres;
	color ambiant = color(0.0f, 0.0f, 0.0f);

	//option d'activer/désactiver les ombres
	bool ombre;

public:

#pragma region Contructeurs

	//Contructeurs
	Scene() {}

	Scene(bool o)
	{
		ombre = o;
	}

	~Scene()
	{
		for (int i = listeObjets.size() - 1; i >= 0; i--)
		{
			delete listeObjets[i];
		}

		for (int i = listeLumieres.size() - 1; i >= 0; i--)
		{
			delete listeLumieres[i];
		}
	}

#pragma endregion

#pragma region fonctions ajout objets

	//fonction pour ajouter un objet à la scène
	/*void ajoutObjet(Sphere e)
	{
		Entite* newObj = new Sphere(e.GetPosition(), e.GetRotation(), e.GetColor(), e.GetRayon(), e.GetMaterial());
		listeObjets.push_back(newObj);
	}*/

	void ajoutObjetMaterial(Sphere e)
	{
		Entite* newObj = new Sphere(e.GetPosition(), e.GetRotation(), e.GetRayon(), e.GetMaterial());
		listeObjets.push_back(newObj);
	}

	//fonction pour ajouter une lumière à la scène
	void ajoutLumiere(Light e)
	{
		Light* newLight = new Light(e.GetPosition(), e.GetDiffuse(), e.GetSpecular());
		listeLumieres.push_back(newLight);
	}

	//fonction pour ajouter un cube à la scène
	void ajoutObjet(Cube e)
	{
		Entite* newObj = new Cube(e.GetPosition(), e.GetRotation(), e.GetCote(), e.GetMaterial());
		listeObjets.push_back(newObj);
	}

	//fonction pour ajouter un cylindre infini à la scène
	void ajoutObjet(CylindreInf e)
	{
		Entite* newObj = new CylindreInf(e.GetPosition(), e.GetRotation(), e.GetRayon(), e.GetMaterial());
		listeObjets.push_back(newObj);
	}

	//fonction pour ajouter un plan infini à la scène
	void ajoutObjet(PlanInf e)
	{
		Entite* newObj = new PlanInf(e.GetPosition(), e.GetRotation(), e.GetMaterial());
		listeObjets.push_back(newObj);
	}

#pragma endregion

#pragma region Traitement de la scène

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
			//création d'une sphère en commentaire, j'ai laissé la version avec le material à la place
			/*case str2int("sphere"):
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
				Sphere s(position, rotation, color(255.f, 0.f, 0.f), rayon);

				//ajout de la sphère à la liste des objets
				ajoutObjet(s);

				cout << "ajout d'une sphere de rayon " << s.GetRayon() << " a la position " << s.GetPosition() << " de rotation " << s.GetRotation() << endl;

				break;
			}*/

			//Cas pour tester une ligne du fichier qui renseigne sur une sphère et son material
		case str2int("sphereMat"):
		{
			//récupération de la position
			vector<string> donneesPosition = explode(donnees.at(1), '_');

			Material mat;
			//Récuperation données composante ambiante
			vector<string> donneesAmbiante = explode(donnees.at(5), '_');

			if (donneesAmbiante.size() == 3)
			{
				mat.ka[0] = stof(donneesAmbiante.at(0)) * (1.0f / 255.0f);
				mat.ka[1] = stof(donneesAmbiante.at(1)) * (1.0f / 255.0f);
				mat.ka[2] = stof(donneesAmbiante.at(2)) * (1.0f / 255.0f);

			}
			else
			{
				cout << "Donnees invalides sur la composante ambiante de la sphère , remplacement par un vec3(0,0,0)" << endl;
				mat.ka[0] = 0;
				mat.ka[1] = 0;
				mat.ka[2] = 0;
			}

			//Récuperation données composante diffuse
			vector<string> donneesDiffuse = explode(donnees.at(6), '_');

			if (donneesDiffuse.size() == 3)
			{
				mat.kd[0] = stof(donneesDiffuse.at(0)) * (1.0f /255.0f);
				mat.kd[1] = stof(donneesDiffuse.at(1)) * (1.0f /255.0f);
				mat.kd[2] = stof(donneesDiffuse.at(2)) * (1.0f /255.0f);

			}
			else
			{
				cout << "Donnees invalides sur la composante diffuse de la sphère , remplacement par un vec3(0,0,0)" << endl;
				mat.kd[0] = 0;
				mat.kd[1] = 0;
				mat.kd[2] = 0;
			}

			//Récuperation données composante spéculaire
			vector<string> donneesSpeculaire = explode(donnees.at(7), '_');

			if (donneesSpeculaire.size() == 3)
			{
				mat.ks[0] = stof(donneesSpeculaire.at(0)) * (1.0f/255.0f);
				mat.ks[1] = stof(donneesSpeculaire.at(1)) * (1.0f/255.0f);
				mat.ks[2] = stof(donneesSpeculaire.at(2)) * (1.0f/255.0f);

			}
			else
			{
				cout << "Donnees invalides sur la composante spéculaire de la sphère , remplacement par un vec3(0,0,0)" << endl;
				mat.ks[0] = 0;
				mat.ks[1] = 0;
				mat.ks[2] = 0;
			}

			//Récuperation données Shininess
			vector<string> donneeShininess = explode(donnees.at(8), '_');

			if (donneeShininess.size() == 1)
			{
				mat.shininess = stof(donneeShininess.at(0));

			}
			else
			{
				cout << "Donnees invalides sur la composante shininess de la sphère , remplacement par un 0" << endl;

				mat.shininess = 0.f;
			}

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
			Sphere s(position, rotation, rayon, mat);

			//ajout de la sphère à la liste des objets
			ajoutObjetMaterial(s);

			cout << "ajout d'une sphere de rayon " << s.GetRayon() << " a la position " << s.GetPosition() << " de rotation " << s.GetRotation() <<

				"avec le composante ka(" << mat.ka[0] * 255.0f << ", " << mat.ka[1] * 255.0f << ", " << mat.ka[2] * 255.0f << ")" <<
				"avec le composante kd(" << mat.kd[0] * 255.0f << ", " << mat.kd[1] * 255.0f << ", " << mat.kd[2] * 255.0f << ")"
				"avec le composante ks(" << mat.ks[0] * 255.0f << ", " << mat.ks[1] * 255.0f << ", " << mat.ks[2] * 255.0f << ")"
				" et de shininess " << mat.shininess << endl;

			break;
		}

		//création d'un cube vert
		case str2int("cube"):
		{
			Material mat;
			//Récuperation données composante ambiante
			vector<string> donneesAmbiante = explode(donnees.at(5), '_');

			if (donneesAmbiante.size() == 3)
			{
				mat.ka[0] = stof(donneesAmbiante.at(0)) * (1.0f/255.0f);
				mat.ka[1] = stof(donneesAmbiante.at(1)) * (1.0f/255.0f);
				mat.ka[2] = stof(donneesAmbiante.at(2)) * (1.0f/255.0f);

			}
			else
			{
				cout << "Donnees invalides sur la composante ambiante de la sphère , remplacement par un vec3(0,0,0)" << endl;
				mat.ka[0] = 0.0f;
				mat.ka[1] = 0.0f;
				mat.ka[2] = 0.0f;
			}

			//Récuperation données composante diffuse
			vector<string> donneesDiffuse = explode(donnees.at(6), '_');

			if (donneesDiffuse.size() == 3)
			{
				mat.kd[0] = stof(donneesDiffuse.at(0)) * (1.0f / 255.0f);
				mat.kd[1] = stof(donneesDiffuse.at(1)) * (1.0f / 255.0f);
				mat.kd[2] = stof(donneesDiffuse.at(2)) * (1.0f / 255.0f);

			}
			else
			{
				cout << "Donnees invalides sur la composante diffuse du cube , remplacement par un vec3(0,0,0)" << endl;
				mat.kd[0] = 0.0f;
				mat.kd[1] = 0.0f;
				mat.kd[2] = 0.0f;
			}

			//Récuperation données composante spéculaire
			vector<string> donneesSpeculaire = explode(donnees.at(7), '_');

			if (donneesSpeculaire.size() == 3)
			{
				mat.ks[0] = stof(donneesSpeculaire.at(0)) * (1.0f / 255.0f);
				mat.ks[1] = stof(donneesSpeculaire.at(1)) * (1.0f / 255.0f);
				mat.ks[2] = stof(donneesSpeculaire.at(2)) * (1.0f / 255.0f);

			}
			else
			{
				cout << "Donnees invalides sur la composante spéculaire du cube , remplacement par un vec3(0,0,0)" << endl;
				mat.ks[0] = 0.0f;
				mat.ks[1] = 0.0f;
				mat.ks[2] = 0.0f;
			}

			//Récuperation données Shininess
			vector<string> donneeShininess = explode(donnees.at(8), '_');

			if (donneeShininess.size() == 1)
			{
				mat.shininess = stof(donneeShininess.at(0));

			}
			else
			{
				cout << "Donnees invalides sur la composante shininess du cube , remplacement par un 0" << endl;

				mat.shininess = 0.f;
			}

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
			Cube c(position, rotation, cote, mat);

			//ajout du cube à la liste des objets
			ajoutObjet(c);

			cout << "ajout d'une cube de cote " << c.GetCote() << " a la position " << c.GetPosition() << " de rotation " << c.GetRotation() 
				<< "avec le materiau d'ambiant " << mat.ka * 255 << " de diffuse " << mat.kd * 255 << " de speculaire "
				<< mat.ks * 255 << " et de shininess " << mat.shininess <<endl;

			break;
		}

		//création d'un cylindre infini bleu
		case str2int("cylindre"):
		{
			Material mat;
			//Récuperation données composante ambiante
			vector<string> donneesAmbiante = explode(donnees.at(5), '_');

			if (donneesAmbiante.size() == 3)
			{
				mat.ka[0] = stof(donneesAmbiante.at(0)) * (1.0f / 255.0f);
				mat.ka[1] = stof(donneesAmbiante.at(1)) * (1.0f / 255.0f);
				mat.ka[2] = stof(donneesAmbiante.at(2)) * (1.0f / 255.0f);

			}
			else
			{
				cout << "Donnees invalides sur la composante ambiante du cylindre , remplacement par un vec3(0,0,0)" << endl;
				mat.ka[0] = 0.0f;
				mat.ka[1] = 0.0f;
				mat.ka[2] = 0.0f;
			}

			//Récuperation données composante diffuse
			vector<string> donneesDiffuse = explode(donnees.at(6), '_');

			if (donneesDiffuse.size() == 3)
			{
				mat.kd[0] = stof(donneesDiffuse.at(0)) * (1.0f / 255.0f);
				mat.kd[1] = stof(donneesDiffuse.at(1)) * (1.0f / 255.0f);
				mat.kd[2] = stof(donneesDiffuse.at(2)) * (1.0f / 255.0f);

			}
			else
			{
				cout << "Donnees invalides sur la composante diffuse du cylindre , remplacement par un vec3(0,0,0)" << endl;
				mat.kd[0] = 0.0f;
				mat.kd[1] = 0.0f;
				mat.kd[2] = 0.0f;
			}

			//Récuperation données composante spéculaire
			vector<string> donneesSpeculaire = explode(donnees.at(7), '_');

			if (donneesSpeculaire.size() == 3)
			{
				mat.ks[0] = stof(donneesSpeculaire.at(0)) * (1.0f / 255.0f);
				mat.ks[1] = stof(donneesSpeculaire.at(1)) * (1.0f / 255.0f);
				mat.ks[2] = stof(donneesSpeculaire.at(2)) * (1.0f / 255.0f);

			}
			else
			{
				cout << "Donnees invalides sur la composante spéculaire du cylindre , remplacement par un vec3(0,0,0)" << endl;
				mat.ks[0] = 0.0f;
				mat.ks[1] = 0.0f;
				mat.ks[2] = 0.0f;
			}

			//Récuperation données Shininess
			vector<string> donneeShininess = explode(donnees.at(8), '_');

			if (donneeShininess.size() == 1)
			{
				mat.shininess = stof(donneeShininess.at(0));

			}
			else
			{
				cout << "Donnees invalides sur la composante shininess du cylindre , remplacement par un 0" << endl;

				mat.shininess = 0.f;
			}

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

			//création du cylindre
			CylindreInf c(position, rotation, rayon, mat);

			//ajout du cylindre à la liste des objets
			ajoutObjet(c);

			cout << "ajout d'un cylindre infini de rayon " << c.GetRayon() << " a la position " << c.GetPosition() << " de rotation " << c.GetRotation() <<
				"avec le composante ka(" << mat.ka[0] * 255.0f << ", " << mat.ka[1] * 255.0f << ", " << mat.ka[2] * 255.0f << ")" <<
				"avec le composante kd(" << mat.kd[0] * 255.0f << ", " << mat.kd[1] * 255.0f << ", " << mat.kd[2] * 255.0f << ")"
				"avec le composante ks(" << mat.ks[0] * 255.0f << ", " << mat.ks[1] * 255.0f << ", " << mat.ks[2] * 255.0f << ")"
				" et de shininess " << mat.shininess << endl;

			break;
		}

		//création d'un plan infini gris
		case str2int("plan"):
		{

			Material mat;
			//Récuperation données composante ambiante
			vector<string> donneesAmbiante = explode(donnees.at(6), '_');

			if (donneesAmbiante.size() == 3)
			{
				mat.ka[0] = stof(donneesAmbiante.at(0)) * (1.0f / 255.0f);
				mat.ka[1] = stof(donneesAmbiante.at(1)) * (1.0f / 255.0f);
				mat.ka[2] = stof(donneesAmbiante.at(2)) * (1.0f / 255.0f);

			}
			else
			{
				cout << "Donnees invalides sur la composante ambiante du plan , remplacement par un vec3(0,0,0)" << endl;
				mat.ka[0] = 0.0f;
				mat.ka[1] = 0.0f;
				mat.ka[2] = 0.0f;
			}

			//Récuperation données composante diffuse
			vector<string> donneesDiffuse = explode(donnees.at(7), '_');

			if (donneesDiffuse.size() == 3)
			{
				mat.kd[0] = stof(donneesDiffuse.at(0)) * (1.0f / 255.0f);
				mat.kd[1] = stof(donneesDiffuse.at(1)) * (1.0f / 255.0f);
				mat.kd[2] = stof(donneesDiffuse.at(2)) * (1.0f / 255.0f);

			}
			else
			{
				cout << "Donnees invalides sur la composante diffuse du plan , remplacement par un vec3(0,0,0)" << endl;
				mat.kd[0] = 0.0f;
				mat.kd[1] = 0.0f;
				mat.kd[2] = 0.0f;
			}

			//Récuperation données composante spéculaire
			vector<string> donneesSpeculaire = explode(donnees.at(8), '_');

			if (donneesSpeculaire.size() == 3)
			{
				mat.ks[0] = stof(donneesSpeculaire.at(0)) * (1.0f / 255.0f);
				mat.ks[1] = stof(donneesSpeculaire.at(1)) * (1.0f / 255.0f);
				mat.ks[2] = stof(donneesSpeculaire.at(2)) * (1.0f / 255.0f);

			}
			else
			{
				cout << "Donnees invalides sur la composante spéculaire du plan , remplacement par un vec3(0,0,0)" << endl;
				mat.ks[0] = 0.0f;
				mat.ks[1] = 0.0f;
				mat.ks[2] = 0.0f;
			}

			//Récuperation données Shininess
			vector<string> donneeShininess = explode(donnees.at(9), '_');

			if (donneeShininess.size() == 1)
			{
				mat.shininess = stof(donneeShininess.at(0));

			}
			else
			{
				cout << "Donnees invalides sur la composante shininess du plan , remplacement par un 0" << endl;

				mat.shininess = 0.f;
			}

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
			PlanInf p(position, rotation, mat);

			//ajout du cylindre à la liste des objets
			ajoutObjet(p);

			cout << "ajout d'un plan infini de rayon a la position " << p.GetPosition() << " de rotation " << p.GetRotation() <<
				"avec le composante ka(" << mat.ka[0] * 255.0f << ", " << mat.ka[1] * 255.0f << ", " << mat.ka[2] * 255.0f << ")" <<
				"avec le composante kd(" << mat.kd[0] * 255.0f << ", " << mat.kd[1] * 255.0f << ", " << mat.kd[2] * 255.0f << ")"
				"avec le composante ks(" << mat.ks[0] * 255.0f << ", " << mat.ks[1] * 255.0f << ", " << mat.ks[2] * 255.0f << ")"
				" et de shininess " << mat.shininess << endl;
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

	//fonction pour définir la couleur du pixel correspondant au Ray donné en paramètre
	color RayTrace(Ray r)
	{
		float zMax = 100.f;
		int indiceZMax = -1;
		outils::Point impact;
		outils::Point impactMax;

		//recherche de l'impact le plus proche
		for (int i = 0; i < listeObjets.size(); i++)
		{
			impact = outils::Point(0, 0, 0);

			if (listeObjets[i]->Intersection(r, impact))
			{
				//si l'objet est plus proche de la caméra que le dernier objet sur lequel on a eu un impact, c'est celui ci qui passe devant
				if (impact[2] < zMax)
				{
					zMax = impact[2];
					impactMax = impact;
					indiceZMax = i;
				}
			}
		}

		//si on a eu un impact
		if (indiceZMax >= 0)
		{
			//traiter l'illumination et les ombres
			return SceneGetImpactColor(r, *listeObjets[indiceZMax], impactMax, this);
			//return SceneGetImpactColorLambert(r, *listeObjets[indiceZMax], impactMax, this);
			//Entite e = *listeObjets[indiceZMax];
			//return e.GetMaterial().kd * 255.0f;
		}
		else return color(0.f, 0.f, 0.f);
	}

	color SceneGetImpactColor(Ray& ray, Entite& obj, outils::Point& impact, const Scene& scene)
	{ 
		Material m = obj.GetMaterial();

		Ray normal = obj.getNormal(impact, ray.origin);
		normal.normalize();
		color col = m.ka*(ambiant * (1.0f / 255.0f));
		color bckup = col;

		for (int l = 0; l < listeLumieres.size(); l++)
		{
			Light* light = listeLumieres[l];
			color ldif = light->GetDiffuse() * (1.f / 255.f);
			color lspe = light->GetSpecular() * (1.f / 255.f);
			
			Vec3 vecteurLight = light->getVectorToLight(impact);
			vecteurLight.normalize();

			float a = vecteurLight.dot(normal.dir);

			if (a > 0)
			{
				color tmp = (ldif * (m.kd)) * a;
				col[0] = col[0] + tmp[0];
				col[1] = col[1] + tmp[1];
				col[2] = col[2] + tmp[2];
			}

			if (col == bckup)
			{
				Ray normalInv(normal);
				normalInv.dir[0] = -normal.dir[0];
				normalInv.dir[1] = -normal.dir[1];
				normalInv.dir[2] = -normal.dir[2];

				float aInv = vecteurLight.dot(normalInv.dir);

				if (aInv > 0)
				{
					color tmp = (ldif * (m.kd)) * aInv;
					col[0] = col[0] + tmp[0];
					col[1] = col[1] + tmp[1];
					col[2] = col[2] + tmp[2];
				}
			}

			Vec3 rm = (2 * vecteurLight.dot(normal.dir)) * normal.dir - vecteurLight;
			rm.normalize();

			float beta = -(rm.dot(ray.dir));
			
			if (beta > 0)
			{
				color tmp = (m.ks) * pow(beta, m.shininess) * lspe;
				col[0] = col[0] + tmp[0];
				col[1] = col[1] + tmp[1];
				col[2] = col[2] + tmp[2];
			}
		}

		if (col[0] > 1.0f) col[0] = 1.0f;
		if (col[1] > 1.0f) col[1] = 1.0f;
		if (col[2] > 1.0f) col[2] = 1.0f;

		return col * 255;
	}

	color SceneGetImpactColorLambert(const Ray& ray, Entite& obj, outils::Point& impact, const Scene& scene)
	{
		Material m = obj.GetMaterial();

		Ray normal = obj.getNormal(impact, ray.origin);
		color col = m.ka * (ambiant * (1.0f / 255.0f));
		color bckup = col;

		//pour chaque lumière de la scène
		for (int l = 0; l < listeLumieres.size(); l++)
		{
			//récupérer le vecteur entre le point d'impact et la lumière
			Light* light = listeLumieres[l];
			Vec3 vecToLight = light->getVectorToLight(impact);
			vecToLight = vecToLight.normalize();

			if (vecToLight.dot(normal.dir) > 0.0f)
			{
				color tmp = m.kd * vecToLight.dot(normal.dir);
				col[0] = col[0] + tmp[0];
				col[1] = col[1] + tmp[1];
				col[2] = col[2] + tmp[2];
			}

			//cout << "couleur " << col << " scal " << vecToLight.dot(normal.dir) << " impact " << impact.GetPosition() << " normale " << normal.dir << endl;
		}

		//si la couleur calculée est identique à la backup, il faut retester avec l'inverse de la normale
		if (col == bckup)
		{
			normal.dir[0] = -normal.dir[0];
			normal.dir[1] = -normal.dir[1];
			normal.dir[2] = -normal.dir[2];

			//pour chaque lumière de la scène
			for (int l = 0; l < listeLumieres.size(); l++)
			{
				//récupérer le vecteur entre le point d'impact et la lumière
				Light* light = listeLumieres[l];
				Vec3 vecToLight = light->getVectorToLight(impact);
				vecToLight = vecToLight.normalize();

				if (vecToLight.dot(normal.dir) > 0.0f)
				{
					color tmp = m.kd * vecToLight.dot(normal.dir);
					col[0] = col[0] + tmp[0];
					col[1] = col[1] + tmp[1];
					col[2] = col[2] + tmp[2];
				}

				//cout << "couleur " << col << " scal " << vecToLight.dot(normal.dir) << " impact " << impact.GetPosition() << " normale " << normal.dir << endl;
			}
		}

		if (col[0] > 1.0f) col[0] = 1.0f;
		if (col[1] > 1.0f) col[1] = 1.0f;
		if (col[2] > 1.0f) col[2] = 1.0f;

		return col * 255.0f;
	}

#pragma endregion
};