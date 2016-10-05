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
#include <unordered_map>

void testVoyage();
int main(){
	testVoyage();
}


std::vector<std::vector<std::string>> lireFichier(std::string path){
	std::string file_p = path;
	std::vector<std::vector<std::string>> resultats;
	lireFichier(file_p, resultats, ',' , true);
	return resultats;
}

void testVoyage(){
	std::vector<std::vector<std::string>> fichierLigne;
	std::vector<std::vector<std::string>> fichierArret;
	std::vector<std::vector<std::string>> fichierVoyage;

	std::unordered_map <std::string, std::vector<Arret>> mapArret;
	std::unordered_map <std::string, Ligne> mapLigne;
	std::unordered_map <unsigned int, Voyage> mapVoyage;



	fichierArret = lireFichier("RTC/stop_times.txt");
	for (int i = 0; i < fichierArret.size(); i++){
		  std::unordered_map<std::string, std::vector<Arret>>::const_iterator it = mapArret.find (fichierArret[i][0]);
		if(it != mapArret.end()){
			mapArret[fichierArret[i][0]].push_back(Arret(fichierArret[i]));
		}
		else{
			std::vector<Arret> tempo = {Arret(fichierArret[i])};
			mapArret.insert({fichierArret[i][0], tempo});
		}
	}


	fichierLigne = lireFichier("RTC/routes.txt");
	for (int i = 0; i < fichierLigne.size(); i++){
			mapLigne.insert({fichierLigne[i][0], Ligne(fichierLigne[i])});
	}

	fichierVoyage = lireFichier("RTC/trips.txt");
		for (unsigned int i = 0; i < fichierVoyage.size(); i++){
			std::vector<Ligne> tempoLigne = {Ligne(fichierLigne[0]), Ligne(fichierLigne[1])};
			Voyage tempo = Voyage(fichierVoyage[i], &tempoLigne[1]);
			tempo.setArrets(mapArret[fichierVoyage[i][1]]);
			mapVoyage.insert({i, tempo});
	}

/*
	std::cout << "Ceci est un test \n";
	for (int i = 0; i < ligneVec.size(); i++){
		std::cout << ligneVec[i] << "\n";
	}
*/
}
