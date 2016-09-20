/*
 * main.cpp
 *
 *  Created on: 2016-09-20
 *      Author: etudiant
 */
#include "auxiliaires.h"
#include <iostream>
#include <ctime>


int main(){
	Heure test;
	Heure test2;
	time_t now = time(0);
	tm *ltm = localtime(&now);

	int testHeure = ltm->tm_hour;
	std::cout << test - test2 << "\n";
	if (test == test2){
		std::cout << "true" << "\n";
	}
	else{
		std::cout << "false" << "\n";
	}
	Date testDate(1999,1,1);
	std::cout << testDate;
	Date testDate2(1998,2,31);
}


void testLireFichier(){
	std::string file_p = "RTC/stops.txt";
	std::vector<std::vector<std::string>> resultats;
	lireFichier(file_p, resultats, ',' , true);
	for (int i = 0; i < resultats.size(); i++){
		for (int j = 0; j < resultats[i].size(); j++){
			std::cout << resultats[i][j] << "\n";
		}
	}
}
