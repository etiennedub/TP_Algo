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
#include "gestionnaire.h"


int main(){
	Reseau test;

	test.ajouterSommet(1);
    test.ajouterArc(1,2,1);
    test.ajouterArc(1,3,5);

    test.ajouterSommet(2);
    test.ajouterArc(2,3,2);
    test.ajouterArc(2,4,5);

    test.ajouterSommet(3);
    test.ajouterArc(3,5,1);

    test.ajouterSommet(4);
    test.ajouterArc(4,5,5);

    test.ajouterSommet(5);

    std::vector<std::vector<unsigned int> > chemin;
    int teste = test.getComposantesFortementConnexes(chemin);
    int chose = 3;

    Gestionnaire allo = Gestionnaire("RTC");
}
