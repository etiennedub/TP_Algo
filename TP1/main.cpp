/*
 * main.cpp
 *
 *  Created on: 2016-09-20
 *      Author: etudiant
 */
#include "auxiliaires.h"
#include <iostream>

int main(){

	std::string file_p = "RTC/stops.txt";
	std::vector<std::vector<std::string>> resultats;
	lireFichier(file_p, resultats, ',' , true);
	for (int i = 0; i < resultats.size(); i++){
		for (int j = 0; j < resultats[i].size(); j++){
			std::cout << resultats[i][j] << "\n";
		}
	}
}


