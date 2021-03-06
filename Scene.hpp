#pragma once
#include <opencv2/core.hpp>
#include <fstream>
#include "opencv2/imgproc.hpp"
#include "Sphere.hpp"
#include "Cube.hpp"
#include "CylindreInf.hpp"
#include "PlanInf.hpp"
#include "Light.hpp"
#include "Carre.hpp"
#include "Triangle.hpp"
#include "ConeInf.hpp"
#include "FonctionDiverses.hpp"


using namespace std;
using namespace cv;

//classe contenant la configuration lue dans le fichier donn� en param�tre
class Scene
{
private:
	vector<Entite*> listeObjets;
	vector<Light*> listeLumieres;
	color ambiant = color(125.0f, 125.0f, 125.0f);

	//option d'activer/d�sactiver les ombres
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

	//fonction pour ajouter une sph�re � la sc�ne
	void ajoutObjet(Sphere e)
	{
		Entite* newObj = new Sphere(e.GetPosition(), e.GetRotation(), e.GetRayon(), e.GetMaterial());
		listeObjets.push_back(newObj);
	}

	//fonction pour ajouter un cone infini a la scene
	void ajoutObjet(ConeInf e)
	{
		Entite* newObj = new ConeInf(e.GetPosition(), e.GetRotation(), (e.GetAngle() * 180) / 3.1415f, e.GetMaterial());
		listeObjets.push_back(newObj);
	}

	//fonction pour ajouter un triangle � la sc�ne
	void ajoutObjet(Triangle e)
	{
		Vec3 pos((e.s1[0] + e.s2[0] + e.s3[0]) / 3.0f, (e.s1[1] + e.s2[1] + e.s3[1]) / 3.0f, (e.s1[2] + e.s2[2] + e.s3[2]) / 3.0f);
		Entite* newObj = new Triangle(e.s1, e.s2, e.s3, pos, Vec3(0.0f, 0.0f, 0.0f), e.GetMaterial());
		listeObjets.push_back(newObj);
	}

	//fonction pour ajouter une lumi�re � la sc�ne
	void ajoutLumiere(Light e)
	{
		Light* newLight = new Light(e.GetPosition(), e.GetDiffuse(), e.GetSpecular());
		listeLumieres.push_back(newLight);
	}

	//fonction pour ajouter un cube � la sc�ne
	void ajoutObjet(Cube e)
	{
		Entite* newObj = new Cube(e.GetPosition(), e.GetRotation(), e.GetCote(), e.GetMaterial());
		listeObjets.push_back(newObj);
	}

	//fonction pour ajouter un cylindre infini � la sc�ne
	void ajoutObjet(CylindreInf e)
	{
		Entite* newObj = new CylindreInf(e.GetPosition(), e.GetRotation(), e.GetRayon(), e.GetMaterial());
		listeObjets.push_back(newObj);
	}

	//fonction pour ajouter un plan infini � la sc�ne
	void ajoutObjet(PlanInf e)
	{
		Entite* newObj = new PlanInf(e.GetPosition(), e.GetRotation(), e.GetMaterial());
		listeObjets.push_back(newObj);
	}

	//fonction pour ajouter un carre � la sc�ne
	void ajoutObjet(Carre e)
	{
		Entite* newObj = new Carre(e.GetPosition(), e.GetRotation(), e.GetCote(), e.GetMaterial());
		listeObjets.push_back(newObj);
	}

#pragma endregion

#pragma region Traitement de la scene

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
		//cas d'un carr�
		case str2int("carre"):
		{
			//r�cup�ration de la position
			vector<string> donneesPosition = explode(donnees.at(1), '_');

			Vec3 position;
			//si on a bien toutes les donn�es pour la position
			if (donneesPosition.size() == 3)
			{
				position[0] = -stof(donneesPosition.at(0));
				position[1] = -stof(donneesPosition.at(1));
				position[2] = stof(donneesPosition.at(2));
			}
			else
			{
				cout << "Donnees invalides sur la position de l'objet de type carre, l'objet sera en 0 1 -10 par defaut" << endl;
				position[0] = 0.f;
				position[1] = 1.f;
				position[2] = -10.f;
			}

			//r�cup�ration de la rotation
			vector<string> donneesRotation = explode(donnees.at(2), '_');

			Vec3 rotation;
			//si on a bien toutes les donn�es pour la position
			if (donneesRotation.size() == 3)
			{
				rotation[0] = stof(donneesRotation.at(0));
				rotation[1] = stof(donneesRotation.at(1));
				rotation[2] = stof(donneesRotation.at(2));
			}
			else
			{
				cout << "Donnees invalides sur la rotation de l'objet de type carre, la rotation sera en 0 0 0 par defaut" << endl;
				rotation[0] = 0.f;
				rotation[1] = 0.f;
				rotation[2] = 0.f;
			}

			float cote;

			//r�cup�ration de la cote, sinon initialis�e � 1 par d�faut
			if (!donnees.at(3).empty())
			{
				cote = stof(donnees.at(3));
			}
			else cote = 1.f;

			Material mat;
			//R�cuperation donn�es composante ambiante
			vector<string> donneesAmbiante = explode(donnees.at(5), '_');

			if (donneesAmbiante.size() == 3)
			{
				mat.ka[0] = stof(donneesAmbiante.at(0)) * (1.0f / 255.0f);
				mat.ka[1] = stof(donneesAmbiante.at(1)) * (1.0f / 255.0f);
				mat.ka[2] = stof(donneesAmbiante.at(2)) * (1.0f / 255.0f);
			}
			else
			{
				cout << "Donnees invalides sur la composante ambiante du carre , remplacement par un vec3(0,0,0)" << endl;
				mat.ka[0] = 0;
				mat.ka[1] = 0;
				mat.ka[2] = 0;
			}

			//R�cuperation donn�es composante diffuse
			vector<string> donneesDiffuse = explode(donnees.at(6), '_');

			if (donneesDiffuse.size() == 3)
			{
				mat.kd[0] = stof(donneesDiffuse.at(0)) * (1.0f / 255.0f);
				mat.kd[1] = stof(donneesDiffuse.at(1)) * (1.0f / 255.0f);
				mat.kd[2] = stof(donneesDiffuse.at(2)) * (1.0f / 255.0f);

			}
			else
			{
				cout << "Donnees invalides sur la composante diffuse du carre , remplacement par un vec3(0,0,0)" << endl;
				mat.kd[0] = 0;
				mat.kd[1] = 0;
				mat.kd[2] = 0;
			}

			//R�cuperation donn�es composante sp�culaire
			vector<string> donneesSpeculaire = explode(donnees.at(7), '_');

			if (donneesSpeculaire.size() == 3)
			{
				mat.ks[0] = stof(donneesSpeculaire.at(0)) * (1.0f / 255.0f);
				mat.ks[1] = stof(donneesSpeculaire.at(1)) * (1.0f / 255.0f);
				mat.ks[2] = stof(donneesSpeculaire.at(2)) * (1.0f / 255.0f);

			}
			else
			{
				cout << "Donnees invalides sur la composante sp�culaire du carre , remplacement par un vec3(0,0,0)" << endl;
				mat.ks[0] = 0;
				mat.ks[1] = 0;
				mat.ks[2] = 0;
			}

			//R�cuperation donn�es Shininess
			vector<string> donneeShininess = explode(donnees.at(8), '_');

			if (donneeShininess.size() == 1)
			{
				mat.shininess = stof(donneeShininess.at(0));

			}
			else
			{
				cout << "Donnees invalides sur la composante shininess du carre , remplacement par un 0" << endl;

				mat.shininess = 10.f;
			}

			//cr�ation du carre
			Carre c(position, rotation, cote, mat);

			//ajout de la sph�re � la liste des objets
			ajoutObjet(c);

			cout << "ajout d'un carre de cote " << c.GetCote() << " a la position " << c.GetPosition() << " de rotation " << c.GetRotation() <<

				"avec le composante ka(" << mat.ka[0] * 255.0f << ", " << mat.ka[1] * 255.0f << ", " << mat.ka[2] * 255.0f << ")" <<
				"avec le composante kd(" << mat.kd[0] * 255.0f << ", " << mat.kd[1] * 255.0f << ", " << mat.kd[2] * 255.0f << ")"
				"avec le composante ks(" << mat.ks[0] * 255.0f << ", " << mat.ks[1] * 255.0f << ", " << mat.ks[2] * 255.0f << ")"
				" et de shininess " << mat.shininess << endl;

			break;
		}

		//cas d'un triangle
		case str2int("triangle"):
		{
			//r�cup�ration de la position du premier sommet
			vector<string> donneesPositionS1 = explode(donnees.at(1), '_');

			Vec3 positionS1;
			//si on a bien toutes les donn�es pour la position
			if (donneesPositionS1.size() == 3)
			{
				positionS1[0] = stof(donneesPositionS1.at(0));
				positionS1[1] = stof(donneesPositionS1.at(1));
				positionS1[2] = -stof(donneesPositionS1.at(2));
			}
			else
			{
				cout << "Donnees invalides sur la position de l'objet de type triangle, l'objet sera en 0 1 -10 par defaut" << endl;
				positionS1[0] = -1.f;
				positionS1[1] = 0.f;
				positionS1[2] = -10.f;
			}

			//r�cup�ration de la position du deuxi�me sommet
			vector<string> donneesPositionS2 = explode(donnees.at(2), '_');

			Vec3 positionS2;
			//si on a bien toutes les donn�es pour la position
			if (donneesPositionS2.size() == 3)
			{
				positionS2[0] = stof(donneesPositionS2.at(0));
				positionS2[1] = stof(donneesPositionS2.at(1));
				positionS2[2] = -stof(donneesPositionS2.at(2));
			}
			else
			{
				cout << "Donnees invalides sur la position de l'objet de type triangle, l'objet sera en 0 1 -10 par defaut" << endl;
				positionS2[0] = 1.f;
				positionS2[1] = 0.f;
				positionS2[2] = -10.f;
			}

			//r�cup�ration de la position du troisi�me sommet
			vector<string> donneesPositionS3 = explode(donnees.at(3), '_');

			Vec3 positionS3;
			//si on a bien toutes les donn�es pour la position
			if (donneesPositionS3.size() == 3)
			{
				positionS3[0] = stof(donneesPositionS3.at(0));
				positionS3[1] = stof(donneesPositionS3.at(1));
				positionS3[2] = -stof(donneesPositionS3.at(2));
			}
			else
			{
				cout << "Donnees invalides sur la position de l'objet de type triangle, l'objet sera en 0 1 -10 par defaut" << endl;
				positionS3[0] = 1.f;
				positionS3[1] = 0.f;
				positionS3[2] = -10.f;
			}

			Material mat;
			//R�cuperation donn�es composante ambiante
			vector<string> donneesAmbiante = explode(donnees.at(5), '_');

			if (donneesAmbiante.size() == 3)
			{
				mat.ka[0] = stof(donneesAmbiante.at(0)) * (1.0f / 255.0f);
				mat.ka[1] = stof(donneesAmbiante.at(1)) * (1.0f / 255.0f);
				mat.ka[2] = stof(donneesAmbiante.at(2)) * (1.0f / 255.0f);
			}
			else
			{
				cout << "Donnees invalides sur la composante ambiante du carre , remplacement par un vec3(0,0,0)" << endl;
				mat.ka[0] = 0;
				mat.ka[1] = 0;
				mat.ka[2] = 0;
			}

			//R�cuperation donn�es composante diffuse
			vector<string> donneesDiffuse = explode(donnees.at(6), '_');

			if (donneesDiffuse.size() == 3)
			{
				mat.kd[0] = stof(donneesDiffuse.at(0)) * (1.0f / 255.0f);
				mat.kd[1] = stof(donneesDiffuse.at(1)) * (1.0f / 255.0f);
				mat.kd[2] = stof(donneesDiffuse.at(2)) * (1.0f / 255.0f);

			}
			else
			{
				cout << "Donnees invalides sur la composante diffuse du carre , remplacement par un vec3(0,0,0)" << endl;
				mat.kd[0] = 0;
				mat.kd[1] = 0;
				mat.kd[2] = 0;
			}

			//R�cuperation donn�es composante sp�culaire
			vector<string> donneesSpeculaire = explode(donnees.at(7), '_');

			if (donneesSpeculaire.size() == 3)
			{
				mat.ks[0] = stof(donneesSpeculaire.at(0)) * (1.0f / 255.0f);
				mat.ks[1] = stof(donneesSpeculaire.at(1)) * (1.0f / 255.0f);
				mat.ks[2] = stof(donneesSpeculaire.at(2)) * (1.0f / 255.0f);

			}
			else
			{
				cout << "Donnees invalides sur la composante sp�culaire du carre , remplacement par un vec3(0,0,0)" << endl;
				mat.ks[0] = 0;
				mat.ks[1] = 0;
				mat.ks[2] = 0;
			}

			//R�cuperation donn�es Shininess
			vector<string> donneeShininess = explode(donnees.at(8), '_');

			if (donneeShininess.size() == 1)
			{
				mat.shininess = stof(donneeShininess.at(0));

			}
			else
			{
				cout << "Donnees invalides sur la composante shininess du carre , remplacement par un 0" << endl;

				mat.shininess = 10.f;
			}

			//ajout de l'objet � la liste
			Triangle t(positionS1, positionS2, positionS3, Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), mat);
			ajoutObjet(t);

			cout << "ajout d'un triangle de sommet s1 " << t.s1 << " s2 " << t.s2 << " s3 " << t.s3 << 

				" avec le composante ka(" << mat.ka[0] * 255.0f << ", " << mat.ka[1] * 255.0f << ", " << mat.ka[2] * 255.0f << ")" <<
				" avec le composante kd(" << mat.kd[0] * 255.0f << ", " << mat.kd[1] * 255.0f << ", " << mat.kd[2] * 255.0f << ")"
				" avec le composante ks(" << mat.ks[0] * 255.0f << ", " << mat.ks[1] * 255.0f << ", " << mat.ks[2] * 255.0f << ")"
				" et de shininess " << mat.shininess << endl;

			break;
		}

		//Cas pour tester une ligne du fichier qui renseigne sur une sph�re et son material
		case str2int("sphere"):
		{
			//r�cup�ration de la position
			vector<string> donneesPosition = explode(donnees.at(1), '_');

			Material mat;
			//R�cuperation donn�es composante ambiante
			vector<string> donneesAmbiante = explode(donnees.at(5), '_');

			if (donneesAmbiante.size() == 3)
			{
				mat.ka[0] = stof(donneesAmbiante.at(0)) * (1.0f / 255.0f);
				mat.ka[1] = stof(donneesAmbiante.at(1)) * (1.0f / 255.0f);
				mat.ka[2] = stof(donneesAmbiante.at(2)) * (1.0f / 255.0f);

			}
			else
			{
				cout << "Donnees invalides sur la composante ambiante de la sph�re , remplacement par un vec3(0,0,0)" << endl;
				mat.ka[0] = 0;
				mat.ka[1] = 0;
				mat.ka[2] = 0;
			}

			//R�cuperation donn�es composante diffuse
			vector<string> donneesDiffuse = explode(donnees.at(6), '_');

			if (donneesDiffuse.size() == 3)
			{
				mat.kd[0] = stof(donneesDiffuse.at(0)) * (1.0f /255.0f);
				mat.kd[1] = stof(donneesDiffuse.at(1)) * (1.0f /255.0f);
				mat.kd[2] = stof(donneesDiffuse.at(2)) * (1.0f /255.0f);

			}
			else
			{
				cout << "Donnees invalides sur la composante diffuse de la sph�re , remplacement par un vec3(0,0,0)" << endl;
				mat.kd[0] = 0;
				mat.kd[1] = 0;
				mat.kd[2] = 0;
			}

			//R�cuperation donn�es composante sp�culaire
			vector<string> donneesSpeculaire = explode(donnees.at(7), '_');

			if (donneesSpeculaire.size() == 3)
			{
				mat.ks[0] = stof(donneesSpeculaire.at(0)) * (1.0f/255.0f);
				mat.ks[1] = stof(donneesSpeculaire.at(1)) * (1.0f/255.0f);
				mat.ks[2] = stof(donneesSpeculaire.at(2)) * (1.0f/255.0f);

			}
			else
			{
				cout << "Donnees invalides sur la composante sp�culaire de la sph�re , remplacement par un vec3(0,0,0)" << endl;
				mat.ks[0] = 0;
				mat.ks[1] = 0;
				mat.ks[2] = 0;
			}

			//R�cuperation donn�es Shininess
			vector<string> donneeShininess = explode(donnees.at(8), '_');

			if (donneeShininess.size() == 1)
			{
				mat.shininess = stof(donneeShininess.at(0));

			}
			else
			{
				cout << "Donnees invalides sur la composante shininess de la sph�re , remplacement par un 0" << endl;

				mat.shininess = 0.f;
			}

			Vec3 position;
			//si on a bien toutes les donn�es pour la position
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

			//r�cup�ration de la rotation
			vector<string> donneesRotation = explode(donnees.at(2), '_');

			Vec3 rotation;
			//si on a bien toutes les donn�es pour la position
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

			//r�cup�ration du rayon, sinon initialis� � 1 par d�faut
			if (!donnees.at(3).empty())
			{
				rayon = stof(donnees.at(3));
			}
			else rayon = 1.f;

			//cr�ation de la sph�re
			Sphere s(position, rotation, rayon, mat);

			//ajout de la sph�re � la liste des objets
			ajoutObjet(s);

			cout << "ajout d'une sphere de rayon " << s.GetRayon() << " a la position " << s.GetPosition() << " de rotation " << s.GetRotation() <<

				"avec le composante ka(" << mat.ka[0] * 255.0f << ", " << mat.ka[1] * 255.0f << ", " << mat.ka[2] * 255.0f << ")" <<
				"avec le composante kd(" << mat.kd[0] * 255.0f << ", " << mat.kd[1] * 255.0f << ", " << mat.kd[2] * 255.0f << ")"
				"avec le composante ks(" << mat.ks[0] * 255.0f << ", " << mat.ks[1] * 255.0f << ", " << mat.ks[2] * 255.0f << ")"
				" et de shininess " << mat.shininess << endl;
			cout << s.GetTrans() << endl;

			break;
		}

		//cr�ation d'un cube vert
		case str2int("cube"):
		{
			Material mat;
			//R�cuperation donn�es composante ambiante
			vector<string> donneesAmbiante = explode(donnees.at(5), '_');

			if (donneesAmbiante.size() == 3)
			{
				mat.ka[0] = stof(donneesAmbiante.at(0)) * (1.0f/255.0f);
				mat.ka[1] = stof(donneesAmbiante.at(1)) * (1.0f/255.0f);
				mat.ka[2] = stof(donneesAmbiante.at(2)) * (1.0f/255.0f);

			}
			else
			{
				cout << "Donnees invalides sur la composante ambiante de la sph�re , remplacement par un vec3(0,0,0)" << endl;
				mat.ka[0] = 0.0f;
				mat.ka[1] = 0.0f;
				mat.ka[2] = 0.0f;
			}

			//R�cuperation donn�es composante diffuse
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

			//R�cuperation donn�es composante sp�culaire
			vector<string> donneesSpeculaire = explode(donnees.at(7), '_');

			if (donneesSpeculaire.size() == 3)
			{
				mat.ks[0] = stof(donneesSpeculaire.at(0)) * (1.0f / 255.0f);
				mat.ks[1] = stof(donneesSpeculaire.at(1)) * (1.0f / 255.0f);
				mat.ks[2] = stof(donneesSpeculaire.at(2)) * (1.0f / 255.0f);

			}
			else
			{
				cout << "Donnees invalides sur la composante sp�culaire du cube , remplacement par un vec3(0,0,0)" << endl;
				mat.ks[0] = 0.0f;
				mat.ks[1] = 0.0f;
				mat.ks[2] = 0.0f;
			}

			//R�cuperation donn�es Shininess
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

			//r�cup�ration de la position
			vector<string> donneesPosition = explode(donnees.at(1), '_');

			Vec3 position;
			//si on a bien toutes les donn�es pour la position
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

			//r�cup�ration de la rotation
			vector<string> donneesRotation = explode(donnees.at(2), '_');

			Vec3 rotation;
			//si on a bien toutes les donn�es pour la position
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

			//r�cup�ration du cote, sinon initialis� � 1 par d�faut
			if (!donnees.at(3).empty())
			{
				cote = stof(donnees.at(3));
			}
			else cote = 1.f;

			//cr�ation du cube
			Cube c(position, rotation, cote, mat);

			//ajout du cube � la liste des objets
			ajoutObjet(c);

			cout << "ajout d'une cube de cote " << c.GetCote() << " a la position " << c.GetPosition() << " de rotation " << c.GetRotation() 
				<< "avec le materiau d'ambiant " << mat.ka * 255 << " de diffuse " << mat.kd * 255 << " de speculaire "
				<< mat.ks * 255 << " et de shininess " << mat.shininess <<endl;

			break;
		}

		//cr�ation d'un cylindre infini bleu
		case str2int("cylindre"):
		{
			Material mat;
			//R�cuperation donn�es composante ambiante
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

			//R�cuperation donn�es composante diffuse
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

			//R�cuperation donn�es composante sp�culaire
			vector<string> donneesSpeculaire = explode(donnees.at(7), '_');

			if (donneesSpeculaire.size() == 3)
			{
				mat.ks[0] = stof(donneesSpeculaire.at(0)) * (1.0f / 255.0f);
				mat.ks[1] = stof(donneesSpeculaire.at(1)) * (1.0f / 255.0f);
				mat.ks[2] = stof(donneesSpeculaire.at(2)) * (1.0f / 255.0f);

			}
			else
			{
				cout << "Donnees invalides sur la composante sp�culaire du cylindre , remplacement par un vec3(0,0,0)" << endl;
				mat.ks[0] = 0.0f;
				mat.ks[1] = 0.0f;
				mat.ks[2] = 0.0f;
			}

			//R�cuperation donn�es Shininess
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

			//r�cup�ration de la position
			vector<string> donneesPosition = explode(donnees.at(1), '_');

			Vec3 position;
			//si on a bien toutes les donn�es pour la position
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

			//r�cup�ration de la rotation
			vector<string> donneesRotation = explode(donnees.at(2), '_');

			Vec3 rotation;
			//si on a bien toutes les donn�es pour la position
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

			//r�cup�ration du rayon, sinon initialis� � 1 par d�faut
			if (!donnees.at(3).empty())
			{
				rayon = stof(donnees.at(3));
			}
			else rayon = 1.f;

			//cr�ation du cylindre
			CylindreInf c(position, rotation, rayon, mat);

			//ajout du cylindre � la liste des objets
			ajoutObjet(c);

			cout << "ajout d'un cylindre infini de rayon " << c.GetRayon() << " a la position " << c.GetPosition() << " de rotation " << c.GetRotation() <<
				"avec le composante ka(" << mat.ka[0] * 255.0f << ", " << mat.ka[1] * 255.0f << ", " << mat.ka[2] * 255.0f << ")" <<
				"avec le composante kd(" << mat.kd[0] * 255.0f << ", " << mat.kd[1] * 255.0f << ", " << mat.kd[2] * 255.0f << ")"
				"avec le composante ks(" << mat.ks[0] * 255.0f << ", " << mat.ks[1] * 255.0f << ", " << mat.ks[2] * 255.0f << ")"
				" et de shininess " << mat.shininess << endl;

			break;
		}

		//cr�ation d'un plan infini gris
		case str2int("plan"):
		{

			Material mat;
			//R�cuperation donn�es composante ambiante
			vector<string> donneesAmbiante = explode(donnees.at(4), '_');

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

			//R�cuperation donn�es composante diffuse
			vector<string> donneesDiffuse = explode(donnees.at(5), '_');

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

			//R�cuperation donn�es composante sp�culaire
			vector<string> donneesSpeculaire = explode(donnees.at(6), '_');

			if (donneesSpeculaire.size() == 3)
			{
				mat.ks[0] = stof(donneesSpeculaire.at(0)) * (1.0f / 255.0f);
				mat.ks[1] = stof(donneesSpeculaire.at(1)) * (1.0f / 255.0f);
				mat.ks[2] = stof(donneesSpeculaire.at(2)) * (1.0f / 255.0f);

			}
			else
			{
				cout << "Donnees invalides sur la composante sp�culaire du plan , remplacement par un vec3(0,0,0)" << endl;
				mat.ks[0] = 0.0f;
				mat.ks[1] = 0.0f;
				mat.ks[2] = 0.0f;
			}

			//R�cuperation donn�es Shininess
			vector<string> donneeShininess = explode(donnees.at(7), '_');

			if (donneeShininess.size() == 1)
			{
				mat.shininess = stof(donneeShininess.at(0));

			}
			else
			{
				cout << "Donnees invalides sur la composante shininess du plan , remplacement par un 0" << endl;

				mat.shininess = 0.f;
			}

			//r�cup�ration de la position
			vector<string> donneesPosition = explode(donnees.at(1), '_');

			Vec3 position;
			//si on a bien toutes les donn�es pour la position
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

			//r�cup�ration de la rotation
			vector<string> donneesRotation = explode(donnees.at(2), '_');

			Vec3 rotation;
			//si on a bien toutes les donn�es pour la position
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

			//cr�ation de la sph�re
			PlanInf p(position, rotation, mat);

			//ajout du cylindre � la liste des objets
			ajoutObjet(p);

			cout << "ajout d'un plan infini de rayon a la position " << p.GetPosition() << " de rotation " << p.GetRotation() <<
				"avec le composante ka(" << mat.ka[0] * 255.0f << ", " << mat.ka[1] * 255.0f << ", " << mat.ka[2] * 255.0f << ")" <<
				"avec le composante kd(" << mat.kd[0] * 255.0f << ", " << mat.kd[1] * 255.0f << ", " << mat.kd[2] * 255.0f << ")"
				"avec le composante ks(" << mat.ks[0] * 255.0f << ", " << mat.ks[1] * 255.0f << ", " << mat.ks[2] * 255.0f << ")"
				" et de shininess " << mat.shininess << endl;
			cout << "matrice de transformation : " << endl << p.GetTrans() << endl;
			break;
		}

		//création d'un cone infini
		case str2int("cone"):
		{
			//r�cup�ration de la position
			vector<string> donneesPosition = explode(donnees.at(1), '_');

			Vec3 position;
			//si on a bien toutes les donn�es pour la position
			if (donneesPosition.size() == 3)
			{
				position[0] = -stof(donneesPosition.at(0));
				position[1] = -stof(donneesPosition.at(1));
				position[2] = stof(donneesPosition.at(2));
			}
			else
			{
				cout << "Donnees invalides sur la position de l'objet de type cone, l'objet sera en 0 1 -10 par defaut" << endl;
				position[0] = 0.f;
				position[1] = 1.f;
				position[2] = -10.f;
			}

			//r�cup�ration de la rotation
			vector<string> donneesRotation = explode(donnees.at(2), '_');

			Vec3 rotation;
			//si on a bien toutes les donn�es pour la position
			if (donneesRotation.size() == 3)
			{
				rotation[0] = stof(donneesRotation.at(0));
				rotation[1] = stof(donneesRotation.at(1));
				rotation[2] = stof(donneesRotation.at(2));
			}
			else
			{
				cout << "Donnees invalides sur la rotation de l'objet de type cone, la rotation sera en 0 0 0 par defaut" << endl;
				rotation[0] = 0.f;
				rotation[1] = 0.f;
				rotation[2] = 0.f;
			}

			float angle;

			//r�cup�ration de l'angle, sinon initialis� � 40 par d�faut
			if (!donnees.at(3).empty())
			{
				angle = stof(donnees.at(3));
			}
			else angle = 40.f;

			Material mat;
			//R�cuperation donn�es composante ambiante
			vector<string> donneesAmbiante = explode(donnees.at(5), '_');

			if (donneesAmbiante.size() == 3)
			{
				mat.ka[0] = stof(donneesAmbiante.at(0)) * (1.0f / 255.0f);
				mat.ka[1] = stof(donneesAmbiante.at(1)) * (1.0f / 255.0f);
				mat.ka[2] = stof(donneesAmbiante.at(2)) * (1.0f / 255.0f);
			}
			else
			{
				cout << "Donnees invalides sur la composante ambiante du cone , remplacement par un vec3(0,0,0)" << endl;
				mat.ka[0] = 0.0f;
				mat.ka[1] = 0.0f;
				mat.ka[2] = 0.0f;
			}

			//R�cuperation donn�es composante diffuse
			vector<string> donneesDiffuse = explode(donnees.at(6), '_');

			if (donneesDiffuse.size() == 3)
			{
				mat.kd[0] = stof(donneesDiffuse.at(0)) * (1.0f / 255.0f);
				mat.kd[1] = stof(donneesDiffuse.at(1)) * (1.0f / 255.0f);
				mat.kd[2] = stof(donneesDiffuse.at(2)) * (1.0f / 255.0f);
			}
			else
			{
				cout << "Donnees invalides sur la composante diffuse du cone , remplacement par un vec3(0,0,0)" << endl;
				mat.kd[0] = 0.0f;
				mat.kd[1] = 0.0f;
				mat.kd[2] = 0.0f;
			}

			//R�cuperation donn�es composante sp�culaire
			vector<string> donneesSpeculaire = explode(donnees.at(7), '_');

			if (donneesSpeculaire.size() == 3)
			{
				mat.ks[0] = stof(donneesSpeculaire.at(0)) * (1.0f / 255.0f);
				mat.ks[1] = stof(donneesSpeculaire.at(1)) * (1.0f / 255.0f);
				mat.ks[2] = stof(donneesSpeculaire.at(2)) * (1.0f / 255.0f);
			}
			else
			{
				cout << "Donnees invalides sur la composante sp�culaire du cone , remplacement par un vec3(0,0,0)" << endl;
				mat.ks[0] = 0.0f;
				mat.ks[1] = 0.0f;
				mat.ks[2] = 0.0f;
			}

			//R�cuperation donn�es Shininess
			vector<string> donneeShininess = explode(donnees.at(8), '_');

			if (donneeShininess.size() == 1)
			{
				mat.shininess = stof(donneeShininess.at(0));
			}
			else
			{
				cout << "Donnees invalides sur la composante shininess du cone , remplacement par un 0" << endl;

				mat.shininess = 0.f;
			}

			ConeInf c(position, rotation, angle, mat);

			//ajout du cone � la liste des objets
			ajoutObjet(c);

			cout << "ajout d'un cone d'angle " << angle << " a la position " << c.GetPosition() << " de rotation " << c.GetRotation() <<
				"avec le composante ka(" << mat.ka[0] * 255.0f << ", " << mat.ka[1] * 255.0f << ", " << mat.ka[2] * 255.0f << ")" <<
				"avec le composante kd(" << mat.kd[0] * 255.0f << ", " << mat.kd[1] * 255.0f << ", " << mat.kd[2] * 255.0f << ")"
				"avec le composante ks(" << mat.ks[0] * 255.0f << ", " << mat.ks[1] * 255.0f << ", " << mat.ks[2] * 255.0f << ")"
				" et de shininess " << mat.shininess << endl;
			cout << c.GetTrans() << endl;

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

	//fonction pour d�finir la couleur du pixel correspondant au Ray donn� en param�tre
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
				//si l'objet est plus proche de la cam�ra que le dernier objet sur lequel on a eu un impact, c'est celui ci qui passe devant
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
			return SceneGetImpactColor(r, *listeObjets[indiceZMax], impactMax, indiceZMax);
		}
		else return ambiant;
	}

	//fonction pour d�terminer si un rayon vers une lumi�re intersectionne un objet
	bool IsShaded(outils::Point& impact, const int& indiceZMax, Vec3& vecToLight, Vec3 lightPosition, float& ratioExpo)
	{
		Vec3 vecLightToPoint;
		vecLightToPoint[0] = -vecToLight[0];
		vecLightToPoint[1] = -vecToLight[1];
		vecLightToPoint[2] = -vecToLight[2];
		vecLightToPoint.normalize();

		Ray rayToLight(lightPosition, vecLightToPoint);
		outils::Point impactOmbre(0.0f, 0.0f, 0.0f);

		//générer les rayons décalés pour traiter les soft shadows
		Ray shadowRays[3][3];

		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				Vec3 origin = lightPosition;

				float derivX;
				float derivY;
				float derivZ;

				if (i == 1) derivY = 0.0f;
				else
				{
					if (i == 0)
					{
						float r = -0.05f + static_cast<float> (rand()) / (static_cast <float>(RAND_MAX / (0.05f - (-0.05))));
						derivY = -0.05f + r;
					}
					else
					{
						float r = -0.05f + static_cast<float> (rand()) / (static_cast <float>(RAND_MAX / (0.05f - (-0.05))));
						derivY = +0.05f + r;
					}
				}

				if (j == 1) derivX = 0.0f;
				else
				{
					if (j == 0)
					{
						float r = -0.01f + static_cast<float> (rand()) / (static_cast <float>(RAND_MAX / (0.01f - -(0.01))));
						derivX = -0.05f + r;
					}
					else
					{
						float r = -0.01f + static_cast<float> (rand()) / (static_cast <float>(RAND_MAX / (0.01f - -(0.01))));
						derivX = +0.05f + r;
					}
				}

				float r = -0.01f + static_cast<float> (rand()) / (static_cast <float>(RAND_MAX / (0.01f - -(0.01))));
				derivZ = 0.05f + r;

				Vec3 deriv(derivX, derivY, derivZ);

				shadowRays[i][j] = Ray(origin + deriv, vecLightToPoint);
			}
		}

		bool inter = false;

		//traitement des ShadowRays
		for (int i = 0; i < listeObjets.size(); i++)
		{
			//ne pas traiter l'objet intercept� par le rayon initial
			if (i != indiceZMax)
			{
				//si on a une intersection
				if (listeObjets[i]->Intersection(rayToLight, impactOmbre))
				{
					if(impactOmbre[2] < impact[2]) inter = true;
				}
			}
		}

		//le point est ombragé, on nuance le shadowRay pour voir s'il est au bord de l'ombre ou pas
		if (inter)
		{
			float cptInter = 9.0f;
			outils::Point impactShadRay(0.0f, 0.0f, 0.0f);

			//pour chaque ShadowRay, on regarde s'il est intercepté par un objet
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					for (int l = 0; l < listeObjets.size(); l++)
					{
						if (l != indiceZMax)
						{
							if (listeObjets[l]->Intersection(shadowRays[i][j], impactShadRay))
							{
								cptInter -= 1.0f;
								break;
							}
						}
					}
				}
			}
			
			ratioExpo = cptInter / 9.0f;
			return true;
		}
		else
		{
			ratioExpo = 1.0f;
			return false;
		}
	}

	//�clairage de Phong
	color SceneGetImpactColor(Ray& ray, Entite& obj, outils::Point& impact, const int indiceObj)
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

			float ratio = 500.0f;
			if (ombre)
			{
				//v�rification si le point n'est cach� de la lumi�re courante
				if (!IsShaded(impact, indiceObj, vecteurLight, listeLumieres[l]->GetPosition(), ratio))
				{
					float a = vecteurLight.dot(normal.dir);

					if (a > 0)
					{
						color tmp = (ldif * (m.kd)) * a;
						col += tmp;
					}

					CylindreInf* test = dynamic_cast<CylindreInf*>(&obj);
					if (test != NULL)
					{
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
								col += tmp;
							}
						}
					}
					
					Vec3 rm = (2 * vecteurLight.dot(normal.dir)) * normal.dir - vecteurLight;
					rm.normalize();

					float beta = -(rm.dot(ray.dir));

					if (beta > 0)
					{
						color tmp = (m.ks) * pow(beta, m.shininess) * lspe;
						col += tmp;
					}
				}
				else
				{
					float a = vecteurLight.dot(normal.dir);

					if (a > 0)
					{
						color tmp = (ldif * (m.kd)) * a;
						col += tmp * ratio;
					}
				}
			}
			else
			{
				float a = vecteurLight.dot(normal.dir);

				if (a > 0)
				{
					color tmp = (ldif * (m.kd)) * a;
					col += tmp;
				}

				CylindreInf* test = dynamic_cast<CylindreInf*>(&obj);
				if (test != NULL)
				{
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
							col += tmp;
						}
					}
				}

				Vec3 rm = (2 * vecteurLight.dot(normal.dir)) * normal.dir - vecteurLight;
				rm.normalize();

				float beta = -(rm.dot(ray.dir));

				if (beta > 0)
				{
					color tmp = (m.ks) * pow(beta, m.shininess) * lspe;
					col += tmp;
				}
			}

			if (col[0] > 1.0f) col[0] = 1.0f;
			if (col[1] > 1.0f) col[1] = 1.0f;
			if (col[2] > 1.0f) col[2] = 1.0f;

			return col * 255;
		}	
	}

#pragma endregion
};