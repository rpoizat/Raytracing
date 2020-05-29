#pragma once

#include "Point4.hpp";
#include "Ray.hpp"

using namespace outils;

//classe mère Entite qui regroupe l'ensemble des objets disposables dans la scène
class Entite
{
	protected:
		Vec3 position;
		Mat trans;
		Mat inv;
	public:

		//Constructeurs
		Entite() {};
		Entite(Vec3 p)
		{
			position = p;

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

			//initialisation de la matrice inverse
			Inverse();
		}

		//destructeur
		~Entite() {};

		//chaque entité dispose d'une position
		Vec3 GetPosition()
		{
			return position;
		}

		//fonction virtuelle d'intersection
		virtual bool Intersection(const Ray& ray, outils::Point& impact) const
		{
			return true;
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
			Mat4f mrX﻿‌﻿;

			mrX﻿‌﻿(0, 0) = 1;
			mrX﻿‌﻿(0, 1) = 0;
			mrX﻿‌﻿(0, 2) = 0;
			mrX﻿‌﻿(0, 3) = 0;

			mrX﻿‌﻿(1, 0) = 0;
			mrX﻿‌﻿(1, 1) = cos(deg);
			mrX﻿‌﻿(1, 2) = -sin(deg);
			mrX﻿‌﻿(1, 3) = 0;

			mrX﻿‌﻿(2, 0) = 0;
			mrX﻿‌﻿(2, 1) = sin(deg);
			mrX﻿‌﻿(2, 2) = cos(deg);
			mrX﻿‌﻿(2, 3) = 0;

			mrX﻿‌﻿(3, 0) = 0;
			mrX﻿‌﻿(3, 1) = 0;
			mrX﻿‌﻿(3, 2) = 0;
			mrX﻿‌﻿(3, 3) = 1;

			trans = mrX﻿‌﻿ * trans;

			Inverse();
		}

		//rotation en Y
		void rotateY(float deg)
		{
			Mat4f mrY;

			mrY(0, 0) = cos(deg);
			mrY(0, 1) = 0;
			mrY(0, 2) = sin(deg);
			mrY(0, 3) = 0;

			mrY(1, 0) = 0;
			mrY(1, 1) = 1;
			mrY(1, 2) = 0;
			mrY(1, 3) = 0;

			mrY(2, 0) = -sin(deg);
			mrY(2, 1) = 0;
			mrY(2, 2) = cos(deg);
			mrY(2, 3) = 0;

			mrY(3, 0) = 0;
			mrY(3, 1) = 0;
			mrY(3, 2) = 0;
			mrY(3, 3) = 1;

			trans = mrY * trans;

			Inverse();
		}

		//rotation en Z
		void rotateZ(float deg)
		{
			Mat4f mrZ;

			mrZ(0, 0) = cos(deg);
			mrZ(0, 1) = -sin(deg);
			mrZ(0, 2) = 0;
			mrZ(0, 3) = 0;

			mrZ(1, 0) = sin(deg);
			mrZ(1, 1) = cos(deg);
			mrZ(1, 2) = 0;
			mrZ(1, 3) = 0;

			mrZ(2, 0) = 0;
			mrZ(2, 1) = 0;
			mrZ(2, 2) = 1;
			mrZ(2, 3) = 0;

			mrZ(3, 0) = 0;
			mrZ(3, 1) = 0;
			mrZ(3, 2) = 0;
			mrZ(3, 3) = 1;

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
		Ray LocalToGlobal(const Ray& r)
		{
			Ray res = r;

			res.dir = LocalToGlobal(res.dir);
			res.origin = LocalToGlobal(res.origin);

			return res;
		}const

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