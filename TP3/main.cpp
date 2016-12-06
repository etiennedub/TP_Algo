#include <iostream>
#include "coordonnees.h"
#include "reseau.h"
#include <vector>
#include "investigation.h"

using namespace std;

int main() {
    //testMonceau(10000); // Test monceau de fibonacii
    //testComplexite(10000); // Test complexité different algo
    GestionnaireInvestigation rtc("RTC");
	for( int i = 0; i < 20; i++ ){
		cout << i << endl;
		cout << "Temps moyen de dijsktra " << rtc.tester_n_paires_dijsktra(1000) << endl;
		cout << "Temps moyen de bellman " << rtc.tester_n_paires_bellman(1000) << endl;
		cout << "Temps moyen de meilleur " << rtc.tester_n_paires_best(1000) << endl;
	}
    return 0;
}
