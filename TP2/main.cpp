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
#include "reseau.h"


int main(){
	Reseau test;
	test.ajouterSommet(1);
    test.ajouterArc(1,2,4);
    bool teste = test.sommetExiste(1);
    teste = test.sommetExiste(2);
    teste = test.arcExiste(3,2);
    int chose = 1;
}
