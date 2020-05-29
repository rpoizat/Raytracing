#include "pch.h"
#include <iostream>
#include <string>
#include <Windows.h>
#include <shobjidl.h>
#include <opencv2/core.hpp>
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "Scene.hpp"

using namespace std;
using namespace cv;

//fonction pour ouvrir une boîte de dialogue pour choisir le fichier de la scène
string GetNomFicherScene()
{
	char* res;
	string strRes;

	HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
	if (SUCCEEDED(hr))
	{
		IFileOpenDialog *selectionFichier;

		// Création de la fenêtre de choix de fichier
		hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL,
			IID_IFileOpenDialog, reinterpret_cast<void**>(&selectionFichier));

		if (SUCCEEDED(hr))
		{
			// Affichage de la fenêtre de dialogue
			hr = selectionFichier->Show(NULL);

			// Récupérer le nom du fichier sélectionné.
			if (SUCCEEDED(hr))
			{
				IShellItem *choix;
				hr = selectionFichier->GetResult(&choix);
				if (SUCCEEDED(hr))
				{
					PWSTR nomFichier;
					hr = choix->GetDisplayName(SIGDN_FILESYSPATH, &nomFichier);

					// Display the file name to the user.
					/*if (SUCCEEDED(hr))
					{
						MessageBox(NULL, nomFichier, L"File Path", MB_OK);
						CoTaskMemFree(nomFichier);
					}*/
					
					//convertion du résultat
					int taille = 0;
					taille = WideCharToMultiByte(CP_ACP, 0, nomFichier, (int)wcslen(nomFichier), 0, 0, NULL, NULL);

					if (taille > 0)
					{
						res = new char[taille + 1];
						WideCharToMultiByte(CP_ACP, 0, nomFichier, taille, res, taille + 1, NULL, NULL);
						res[taille] = '\0';

						strRes = res;
					}

					CoTaskMemFree(nomFichier);
					choix->Release();
				}
			}
			selectionFichier->Release();
		}
		CoUninitialize();
	}
	
	return strRes;
}

int main()
{
	//paramètres
	string nomFichier = GetNomFicherScene();
	int largeur = 0;
	int hauteur = 0;
	string nomImage;
	bool ombre;

	//choix des options
#pragma region Choix des options

	//choix du fichier de la scène
	cout << "Fichier scene choisi : " << nomFichier << endl;

	//choix des dimensions de l'image
	cout << "Largeur de l'image ?" << endl;
	cin >> largeur;
	while (cin.fail() || largeur <= 0)
	{
		cout << "Largeur invalide, doit etre un nombre superieur a 0" << endl << "Largeur de l'image ?" << endl;
		std::cin.clear();
		std::cin.ignore(256, '\n');
		cin >> largeur;
	}

	cout << "Hauteur de l'image ?" << endl;
	cin >> hauteur;
	while (cin.fail() || hauteur <= 0)
	{
		cout << "Hauteur invalide, doit etre un nombre superieur a 0" << endl << "Hauteur de l'image ?" << endl;
		std::cin.clear();
		std::cin.ignore(256, '\n');
		cin >> hauteur;
	}

	//choix des ombres
	string choix;
	cout << "Voulez-vous activer les ombres ? (y/n)" << endl;
	cin >> choix;

	while (choix != "y" && choix != "n")
	{
		cout << "Reponse invalide, (y) pour activer les ombres, (n) pour les desactiver" << endl;
		std::cin.clear();
		std::cin.ignore(256, '\n');
		cin >> choix;
	}

	if (choix == "y")
	{
		ombre = true;
		cout << "Ombres activees" << endl;
	}
	else
	{
		ombre = false;
		cout << "Ombres desactivees" << endl;
	}

	//choix du nom de l'image à rendre
	cout << "Choisissez le nom de l'image finale (sans extension) :" << endl;
	cin >> nomImage;

	nomImage += ".jpg";

#pragma endregion

	//création de l'image à rendre
	Mat rendu(hauteur, largeur, CV_8UC3, Scalar(0, 0, 0));

	//définition du ratio de l'image
	float aspectRatio = float(largeur) / float(hauteur);

	//lecture de la configuration de la scène
	Scene scene;
	scene.LectureConfiguration(nomFichier);

	//traitement des pixels
	for (int j = 0; j < hauteur; j++)
	{
		for (int i = 0; i < largeur; i++)
		{
			// calcul des coordonnees monde des pixels
			float x =  2.f * (float(i - largeur / 2) + 0.5f) / largeur;
			float y = -2.f * (float(j - hauteur / 2) + 0.5f) / hauteur;

			// Generation du rayon primaire
			Ray ray(0.f, 0.f, 0.f, x, y, 1);
			ray.dir.normalize();

			//définir la couleur du pixel
			color couleurPix = scene.RayTrace(ray);

			int b = (int)couleurPix[0];
			int g = (int)couleurPix[1];
			int r = (int)couleurPix[2];

			//appliquer la couleur au pixel
			rendu.at<Vec3b>(j, i)[0] = r;
			rendu.at<Vec3b>(j, i)[1] = g;
			rendu.at<Vec3b>(j, i)[2] = b;
		}
	}

	//sauvegarde de l'image à rendre sous forme de fichier
	imwrite(nomImage, rendu);

	cout << "Fin de traitement" << endl;
	return 0;
}

