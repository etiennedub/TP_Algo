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
#include <map>



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
	const clock_t tempsDebut = clock();
	std::ofstream textAEcrire;
	textAEcrire.open ("out.txt");
	std::vector<std::vector<std::string>> fichier;

	std::unordered_multimap <std::string, Arret*> mapArret;
	std::unordered_map <std::string, Ligne*> mapLigne; // Pour voyage
	std::map <std::string, Ligne*> ligneOrdre;
	std::multimap <Heure, Voyage*> mapVoyage;
	std::map <unsigned int, Station> mapStation;

	Heure debut = Heure(22,47,0);
	Heure fin = Heure(23,47,0);
	Date date = Date(2016,8,2);
	std::string serviceIdValide = "20162011multiint-1111100";

	std::cout << "1 : " << float( clock () - tempsDebut ) /  CLOCKS_PER_SEC<< std::endl;
	fichier = lireFichier("RTC/stops.txt");
	for (int i = 0; i < fichier.size(); i++){
			Station tempo = Station(fichier[i]);
			mapStation.insert({tempo.getId(), tempo});
	}
	std::cout << "2 : " << float( clock () - tempsDebut ) /  CLOCKS_PER_SEC<< std::endl;
	fichier = lireFichier("RTC/stop_times.txt");
	for (int i = 0; i < fichier.size(); i++){
			mapArret.insert({fichier[i][0],  new Arret(fichier[i])});
	}
	std::cout << "3 : " << float( clock () - tempsDebut ) /  CLOCKS_PER_SEC<< std::endl;
	fichier = lireFichier("RTC/routes.txt");
	for (int i = 0; i < fichier.size(); i++){
		Ligne* tempo = new Ligne(fichier[i]);
		ligneOrdre.insert(std::pair<std::string, Ligne*>(tempo->getNumero(), tempo));
		mapLigne.insert({fichier[i][0], tempo});
	}

	std::cout << "4 : " << float( clock () - tempsDebut ) /  CLOCKS_PER_SEC<< std::endl;
	fichier = lireFichier("RTC/trips.txt");
	for (int i = 0; i < fichier.size(); i++){
		if(fichier[i][1] == serviceIdValide){
			Voyage* tempo = new Voyage(fichier[i], mapLigne[fichier[i][0]]);
			auto range = mapArret.equal_range(fichier[i][2]);
			std::vector<Arret> tempoVec;
			for ( auto it = range.first ; it != range.second ; ++it){
				tempoVec.push_back((*it->second));
			}
			tempo->setArrets(tempoVec);
			mapVoyage.insert({tempo->getHeureDepart(), tempo});
		}
	}
	std::cout << "5 : " << float( clock () - tempsDebut ) /  CLOCKS_PER_SEC<< std::endl;

	// Section  texte
	std::string ligneTexte = "====================================== \n";
	textAEcrire << "Chargement des données terminé en " << float( clock () - tempsDebut ) /  CLOCKS_PER_SEC
			<<" secondes" << std::endl;
	textAEcrire << ligneTexte << "LIGNES DE LA RTC" << std::endl << "COMPTE = "
			<< ligneOrdre.size() << std::endl << ligneTexte;
	for ( std::map <std::string, Ligne*>::iterator it = ligneOrdre.begin(); it != ligneOrdre.end(); ++it ){
		textAEcrire << (*it->second) << std::endl;
//<<<<<<< HEAD
	}/*
	textAEcrire << ligneTexte << "STATIONS DE LA RTC" << std::endl << "COMPTE = "
				<< mapStation.size() << std::endl << ligneTexte;
	for ( std::map <unsigned int, Station>::iterator it = mapStation.begin(); it != mapStation.end(); ++it ){
			textAEcrire << it->second << std::endl;
		}
	textAEcrire << ligneTexte << "VOYAGES DE LA JOURNÉE DU " << date
			<< std::endl << debut << " - " << fin << std::endl
			<< "COMPTE = "<< mapVoyage.size() << std::endl << ligneTexte;
	for(std::multimap <Heure, Voyage*>::iterator it = mapVoyage.begin(); it != mapVoyage.end(); ++it){
		if(it->first > debut){
			textAEcrire << (*it->second);
		}
	}

	std::cout << float( clock () - tempsDebut ) /  CLOCKS_PER_SEC;
	// Section Delete :

	for ( std::unordered_map <std::string, Ligne*>::iterator it = mapLigne.begin(); it != mapLigne.end(); ++it ){
		delete it->second;
	}
=======
	}*/
	textAEcrire << ligneTexte << "STATIONS DE LA RTC" << std::endl << "COMPTE = "
				<< mapStation.size() << std::endl << ligneTexte;
	for ( std::map <unsigned int, Station>::iterator it = mapStation.begin(); it != mapStation.end(); ++it ){
			textAEcrire << it->second << std::endl;
		}
	textAEcrire << ligneTexte << "VOYAGES DE LA JOURNÉE DU " << date
			<< std::endl << debut << " - " << fin << std::endl
			<< "COMPTE = "<< mapVoyage.size() << std::endl << ligneTexte;
	for(std::multimap <Heure, Voyage*>::iterator it = mapVoyage.begin(); it != mapVoyage.end(); ++it){
		if(it->first > debut){
			textAEcrire << (*it->second);
		}
	}

	std::cout << float( clock () - tempsDebut ) /  CLOCKS_PER_SEC;
	// Section Delete :

	for ( std::unordered_map <std::string, Ligne*>::iterator it = mapLigne.begin(); it != mapLigne.end(); ++it ){
		delete it->second;
	}
//>>>>>>> 6689bd050ff2edf40a8b5b8bf6c61ec96c7631a5
	for ( std::unordered_multimap <std::string, Arret*>::iterator it = mapArret.begin(); it != mapArret.end(); ++it ){
		delete it->second;
	}
	for ( std::multimap <Heure, Voyage*>::iterator it = mapVoyage.begin(); it != mapVoyage.end(); ++it ){
		delete it->second;
	}
	textAEcrire.close();


}
