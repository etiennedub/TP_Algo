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

void testvoyage();
int main(){
	testvoyage();
}


std::vector<std::vector<std::string>> lireFichier(std::string path){
	std::string file_p = path;
	std::vector<std::vector<std::string>> resultats;
	lireFichier(file_p, resultats, ',' , true);
	return resultats;
}

void testVoyage(){
	std::vector<std::vector<std::string>> file;
	file = lireFichier("RTC/routes.txt");
	Ligne ligneObj(file[0]);
	std::cout << ligneObj << std::endl;

	file = lireFichier("RTC/trips.txt");
	Voyage voyageObj(file[75], ligneObj);

	file = lireFichier("RTC/stop_times.txt");
	std::vector<Arret> arretVec;
	for (int i = 0; i < 10; i++){
		Arret arretObj(file[i]);
		arretVec.push_back(arretObj);
	}

	voyageObj.setArrets(arretVec);

	std::cout << voyageObj;
/*
	std::cout << "Ceci est un test \n";
	for (int i = 0; i < ligneVec.size(); i++){
		std::cout << ligneVec[i] << "\n";
	}
*/
}
