#pragma once
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <utility>
using namespace std;

//Fichiers de fonctions utilitaires
//fonction pour diviser une chaine en une liste selon le délimiteur défini
vector<string> explode(string const & s, char delim)
{
	vector<string> result;
	istringstream iss(s);

	for (string token; getline(iss, token, delim); )
	{
		result.push_back(move(token));
	}

	return result;
}

//fonction pour convertir une chaine en int pour pouvoir faire des switch dessus
constexpr unsigned int str2int(const char* str, int h = 0)
{
	return !str[h] ? 5381 : (str2int(str, h + 1) * 33) ^ str[h];
}