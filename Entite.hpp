#pragma once

#include "Point4.hpp";
#include "Ray.hpp"
#include "Material.hpp"

using namespace outils;

//classe mère Entite qui regroupe l'ensemble des objets disposables dans la scène
class Entite
{
	protected:
		Vec3 position;
		Vec3 rotation;
		Mat trans;
		Mat inv;
		Material material;

		//attribut temporaire en attendant les matériaux
		color col;
	public:

		//Constructeurs
		Entite() {};
		Entite(Vec3 p, Vec3 r, color c)
		{
			position = p;
			rotation = r;
			col = c;
			

			trans = Mat(4, 4, CV_32F, 0.f);

			//initialiser la matrice de transformation
			for (int i = 0; i < trans.rows; i++)
			{
				for (int j = 0; j < trans.cols; j++)
				{
					if (j == i) trans.at<float>(i, j) = 1.f;
					else trans.at<float>(i, j) = 0.f;
				}
			}

			//ajout de la position
			trans.at<float>(0, 3) = position[0];
			trans.at<float>(1, 3) = position[1];
			trans.at<float>(2, 3) = position[2];

			//ajout de la rotation
			rotateX(r[0]);
			rotateY(r[1]);
			rotateZ(r[2]);
		}

		Entite(Vec3 p, Vec3 r, Material m)
		{
			position = p;
			rotation = r;
			material = m;

			trans = Mat(4, 4, CV_32F, 0.f);
			
			//initialiser la matrice de transformation
			for (int i = 0; i < trans.rows; i++)
			{
				for (int j = 0; j < trans.cols; j++)
				{
					if (j == i) trans.at<float>(i, j) = 1.f;
					else trans.at<float>(i,j) = 0.f;
				}
			}

			//ajout de la position
			trans.at<float>(0, 3) = position[0];
			trans.at<float>(1, 3) = position[1];
			trans.at<float>(2, 3) = position[2];

			//ajout de la rotation
			rotateX(r[0]);
			rotateY(r[1]);
			rotateZ(r[2]);
		}

		//destructeur
		~Entite() {};

		//chaque entité dispose d'une position
		Vec3 GetPosition()
		{
			return position;
		}

		//getteur sur la matrice de transformation
		Mat GetTrans()
		{
			return trans;
		}

		//chaque entité dispose d'une rotation
		Vec3 GetRotation()
		{
			return rotation;
		}

		//fonction temporaire pour afficher les couleurs
		color GetColor()
		{
			return col;
		}

		// fonction qui permet de récuperer le material
		Material GetMaterial()
		{
			return material;
		}

		//fonction virtuelle d'intersection
		virtual bool Intersection(const Ray& ray, outils::Point& impact) const
		{
			return true;
		}

		//fonction virtuelle permettant de récuperer la normale
		virtual Ray getNormal(const outils::Point& p, const outils::Point& o) const
		{
			return Ray();
		}

#pragma region Fonctions de transformation

		//mettre à jour la matrice inverse de l'objet
		void Inverse()
		{
			inv = trans.inv();
		}

		//fonction de translation
		void translate(Vec3 v)
		{
			trans.at<float>(0, 3) = v[0];
			trans.at<float>(1, 3) = v[1];
			trans.at<float>(2, 3) = v[2];

			Inverse();
		}

		//fonction de scale
		void scale(float f)
		{
			trans.at<float>(0, 0) = f;
			trans.at<float>(1, 1) = f;
			trans.at<float>(2, 2) = f;

			trans.at<float>(0, 3) = trans.at<float>(0, 3) * f;
			trans.at<float>(1, 3) = trans.at<float>(1, 3) * f;
			trans.at<float>(2, 3) = trans.at<float>(2, 3) * f;

			Inverse(); 
		}

		//rotation en X
		void rotateX(float deg)
		{
			Mat mrX﻿‌﻿ = Mat(4, 4, CV_32F, 0.f);;

			deg = (deg * 3.1415) / 180;

			mrX﻿‌﻿.at<float>(0, 0) = 1.f;
			mrX﻿‌﻿.at<float>(0, 1) = 0.f;
			mrX﻿‌﻿.at<float>(0, 2) = 0.f;
			mrX﻿‌﻿.at<float>(0, 3) = 0.f;

			mrX﻿‌﻿.at<float>(1, 0) = 0.f;
			mrX﻿‌﻿.at<float>(1, 1) = cos(deg);
			mrX﻿‌﻿.at<float>(1, 2) = -sin(deg);
			mrX﻿‌﻿.at<float>(1, 3) = 0.f;

			mrX﻿‌﻿.at<float>(2, 0) = 0.f;
			mrX﻿‌﻿.at<float>(2, 1) = sin(deg);
			mrX﻿‌﻿.at<float>(2, 2) = cos(deg);
			mrX﻿‌﻿.at<float>(2, 3) = 0.f;

			mrX﻿‌﻿.at<float>(3, 0) = 0.f;
			mrX﻿‌﻿.at<float>(3, 1) = 0.f;
			mrX﻿‌﻿.at<float>(3, 2) = 0.f;
			mrX﻿‌﻿.at<float>(3, 3) = 1.f;

			trans = mrX﻿‌﻿ * trans;

			Inverse();
		}

		//rotation en Y
		void rotateY(float deg)
		{
			Mat mrY = Mat(4, 4, CV_32F, 0.f);

			deg = (deg * 3.1415) / 180;

			mrY.at<float>(0, 0) = cos(deg);
			mrY.at<float>(0, 1) = 0.f;
			mrY.at<float>(0, 2) = sin(deg);
			mrY.at<float>(0, 3) = 0.f;

			mrY.at<float>(1, 0) = 0.f;
			mrY.at<float>(1, 1) = 1.f;
			mrY.at<float>(1, 2) = 0.f;
			mrY.at<float>(1, 3) = 0.f;

			mrY.at<float>(2, 0) = -sin(deg);
			mrY.at<float>(2, 1) = 0.f;
			mrY.at<float>(2, 2) = cos(deg);
			mrY.at<float>(2, 3) = 0.f;

			mrY.at<float>(3, 0) = 0.f;
			mrY.at<float>(3, 1) = 0.f;
			mrY.at<float>(3, 2) = 0.f;
			mrY.at<float>(3, 3) = 1.f;

			trans = mrY * trans;

			Inverse();
		}

		//rotation en Z
		void rotateZ(float deg)
		{
			Mat mrZ = Mat(4, 4, CV_32F, 0.f);

			deg = (deg * 3.1415) / 180;

			mrZ.at<float>(0, 0) = cos(deg);
			mrZ.at<float>(0, 1) = -sin(deg);
			mrZ.at<float>(0, 2) = 0.f;
			mrZ.at<float>(0, 3) = 0.f;

			mrZ.at<float>(1, 0) = sin(deg);
			mrZ.at<float>(1, 1) = cos(deg);
			mrZ.at<float>(1, 2) = 0.f;
			mrZ.at<float>(1, 3) = 0.f;

			mrZ.at<float>(2, 0) = 0.f;
			mrZ.at<float>(2, 1) = 0.f;
			mrZ.at<float>(2, 2) = 1.f;
			mrZ.at<float>(2, 3) = 0.f;

			mrZ.at<float>(3, 0) = 0.f;
			mrZ.at<float>(3, 1) = 0.f;
			mrZ.at<float>(3, 2) = 0.f;
			mrZ.at<float>(3, 3) = 1.f;

			trans = mrZ * trans;

			Inverse();
		}

#pragma endregion

#pragma region LocalToGlobal

		//transposition de local à global pour un point
		outils::Point LocalToGlobal(const outils::Point& p)const
		{
			Point4 p4(p);

			p4 = inv * p4;

			outils::Point res(p4[0], p4[1], p4[2]);

			return res;
		}

		//transposition de local à global pour un vec3
		Vec3 LocalToGlobal(const Vec3& v) const
		{
			Vec4 v4(v);

			v4 = inv * v4;

			Vec3 res(v4[0], v4[1], v4[2]);

			return res;
		}

		//transposition de local à global pour un Ray
		Ray LocalToGlobal(const Ray& r) const
		{
			Ray res = r;

			res.dir = LocalToGlobal(res.dir);
			res.origin = LocalToGlobal(res.origin);

			return res;
		}

#pragma endregion

#pragma region GlobalToLocal

		//transposition global à local pour un point
		outils::Point GlobalToLocal(const outils::Point& p) const
		{
			Point4 p4(p);

			p4 = trans * p4;

			outils::Point res(p4[0], p4[1], p4[2]);

			return res;
		}

		//transposition global à local pour un vec3
		Vec3 GlobalToLocal(const Vec3& v) const
		{
			Vec4 v4(v);

			v4 = trans * v4;

			Vec3 res(v4[0], v4[1], v4[2]);

			return res;
		}

		//transposition global à local pour un Ray
		Ray GlobalToLocal(const Ray& r)const
		{
			Ray res = r;

			res.dir = GlobalToLocal(res.dir);
			res.origin = GlobalToLocal(res.origin);

			return res;
		}



#pragma endregion
};