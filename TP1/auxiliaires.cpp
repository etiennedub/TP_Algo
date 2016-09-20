/*
 * auxiliaires.cpp
 *
 *  Created on: 2016-09-14
 *      Author: etudiant
 */
#include "auxiliaires.h"

std::vector<std::string> split(const std::string &s, char delim){
	std::vector<std::string> resultat;
	std::string mot = "";

	for(int i = 0; i < s.length(); i++){
		if (char(s[i]) == delim){
			resultat.push_back(mot);
			mot = "";
		}
		else{
			mot += s[i];
		}
	}

	resultat.push_back(mot);
	return resultat;
}

void lireFichier(std::string nomFichier,
		std::vector<std::vector<std::string>>& resultats, char delimiteur, bool rm_entete){

	std::string ligne;
	std::ifstream fichier;
	fichier.open(nomFichier);

	if (fichier.is_open()){
		while ( getline(fichier, ligne)){
			resultats.push_back(split(ligne, delimiteur));
		}
		fichier.close();
	}

	else{
		// Exception ici  ***************
		std::cout << "Unable to open file";
	}



}


