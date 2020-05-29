#pragma once

#include <math.h>;
#include "Vec3.hpp";
#include <opencv2/opencv.hpp>

using namespace cv;

class Vec4
{
	private:
		float x, y, z, w;

	public:

#pragma region Constructeurs

		//constructeur vide
		Vec4()
		{
			x, y, z, w = 0.f;
		};

		//constructeur avec paramètres
		Vec4(float x1, float y1, float z1, float w1)
		{
			x = x1;
			y = y1;
			z = z1;
			w = w1;
		}

		Vec4(Vec3 v)
		{
			x = v[0];
			y = v[1];
			z = v[2];
			w = 0.f;
		}

#pragma endregion

#pragma region Operateurs

		//accès en lecture
		float operator[](int i) const
		{
			switch (i)
			{
			case 0:
				return x;

			case 1:
				return y;

			case 2:
				return z;

			case 3:
				return w;
			default:
				return NULL;
			}
		}

		//accès en écriture aux coordonnées du point
		float& operator[](int i)
		{
			switch (i)
			{
			case 0:
				return x;

			case 1:
				return y;

			case 2:
				return z;

			case 3:
				return w;

			default:
				return x;
			}
		}

		//affectation
		inline Vec4& operator=(const Vec4& v)
		{
			x = v.x;
			y = v.y;
			z = v.z;
			w = v.w;

			return *this;
		}

		//addition
		inline Vec4 operator+=(const Vec4& v)
		{
			x += v.x;
			y += v.y;
			z += v.z;
			w += v.w;

			return *this;
		}

		//soustraction
		inline Vec4 operator-=(const Vec4& v)
		{
			x -= v.x;
			y -= v.y;
			z -= v.z;
			w -= v.w;

			return *this;
		}

		//soustraction
		inline Vec4 operator*=(const Vec4& v)
		{
			x *= v.x;
			y *= v.y;
			z *= v.z;
			w *= v.w;

			return *this;
		}

#pragma endregion

#pragma region fonctions

		//produit scalaire
		inline float dot(const Vec4& v2) const
		{
			return x * v2.x + y * v2.y + z * v2.z + w * v2.w;
		}

		//fonction de normalisation
		inline Vec4& normalize()
		{
			float inv_length = 1.f / sqrt(x*x + y * y + z * z + w * w);
			x *= inv_length;
			y *= inv_length;
			z *= inv_length;
			w *= inv_length;
			return *this;
		}

#pragma endregion
};

#pragma region operateurs externes

//soustraction entre vecteurs
inline Vec4 operator-(Vec4 v1, const Vec4& v2)
{
	v1 -= v2;
	return v1;
}

//addition en vecteurs
inline Vec4 operator+(Vec4 v1, const Vec4& v2)
{
	v1 += v2;
	return v1;
}

//multiplication avec un autre vecteur
inline Vec4 operator*(Vec4 v1, const Vec4& v2)
{
	return Vec4(v1[0] * v2[0], v1[1] * v2[1], v1[2] * v2[2], v1[3] * v2[3]);
}

//multiplication entre mat4 et Vec4
Vec4 operator*(cv::Mat4f mat4, const Vec4& p)
{
	float x = p[0] * mat4.at<float>(0, 0) + p[1] * mat4.at<float>(0, 1) + p[2] * mat4.at<float>(0, 2) + p[3] * mat4.at<float>(0, 3);
	float y = p[0] * mat4.at<float>(1, 0) + p[1] * mat4.at<float>(1, 1) + p[2] * mat4.at<float>(1, 2) + p[3] * mat4.at<float>(1, 3);
	float z = p[0] * mat4.at<float>(2, 0) + p[1] * mat4.at<float>(2, 1) + p[2] * mat4.at<float>(2, 2) + p[3] * mat4.at<float>(2, 3);
	float w = p[0] * mat4.at<float>(3, 0) + p[1] * mat4.at<float>(3, 1) + p[2] * mat4.at<float>(3, 2) + p[3] * mat4.at<float>(3, 3);

	return Vec4(x, y, z, w);
}

//operateur de flux
inline ostream& operator<<(ostream& o, const Vec4& v)
{
	o << "(" << v[0] << ", " << v[1] << ", " << v[2] << ", " << v[3] << ")";
	return o;
}
#pragma endregion
