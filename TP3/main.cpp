#include <iostream>
#include "coordonnees.h"
#include "reseau.h"
#include <vector>
#include "investigation.h"

using namespace std;



void testReseau(){
    Reseau monReseau;
    monReseau.ajouterSommet(1);
    monReseau.ajouterSommet(6);
    monReseau.ajouterSommet(2);
    monReseau.ajouterSommet(3);
    monReseau.ajouterSommet(4);
    monReseau.ajouterSommet(5);
    monReseau.ajouterArc(1,2,1);
    monReseau.ajouterArc(1,3,5);
    monReseau.ajouterArc(1,6,4);

    monReseau.ajouterArc(2,4,2);

    monReseau.ajouterArc(3,5,1);

    monReseau.ajouterArc(4,5,10);
    monReseau.ajouterArc(4,3,1);


    std::vector<unsigned int> chemin;
    monReseau.meilleurPlusCourtChemin(1, 5, chemin);
    cout << "fini" << endl;
}
int main() {
    testReseau();
   GestionnaireInvestigation rtc("RTC");

//    cout << "Temps moyen de dijsktra " << rtc.tester_n_paires_dijsktra(10) << endl;
//    cout << "Temps moyen de bellman " << rtc.tester_n_paires_bellman(10) << endl;
   cout << "Temps moyen de meilleur " << rtc.tester_n_paires_best(10) << endl;
    return 0;
}
