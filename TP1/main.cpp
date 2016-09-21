/*
 * main.cpp
 *
 *  Created on: 2016-09-20
 *      Author: etudiant
 */
#include "auxiliaires.h"
#include "ligne.h"
#include <iostream>
#include <ctime>

void testLigne();
int main(){
	testLigne();
}


std::vector<std::vector<std::string>> lireFichier(std::string path){
	std::string file_p = path;
	std::vector<std::vector<std::string>> resultats;
	lireFichier(file_p, resultats, ',' , true);
	return resultats;
}

void testLigne(){
	std::vector<std::vector<std::string>> file;
	file = lireFichier("RTC/routes.txt");
	std::vector<Ligne> ligneVec;
	std::cout << "Ceci est un test \n";
	for (int i = 0; i < file.size(); i++){
		Ligne object(file[i]);
		std::cout << object << "\n";

	}
/*
	std::cout << "Ceci est un test \n";
	for (int i = 0; i < ligneVec.size(); i++){
		std::cout << ligneVec[i] << "\n";
	}
*/
}
