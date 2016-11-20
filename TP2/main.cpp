/*
 * main.cpp
 *
 *  Created on: 2016-09-20
 *      Author: etudiant
 */
#include "auxiliaires.h"
#include "ligne.h"
#include <iostream>
#include <sstream>
#include <string>
#include <ctime>
#include <unordered_map>
#include <map>
#include "reseau.h"
#include "gestionnaire.h"

int main(){

    const clock_t tempsDebut = clock();

    // Chargement des donnees
    Gestionnaire gestion = Gestionnaire("RTC");
    std::cout << "Chargement des données en " << float( clock () - tempsDebut ) /  CLOCKS_PER_SEC
            << " secondes" << std::endl;

    std::stringstream stream;
    std::string choixUtilisateur = "";
    std::cout << "Menu" << std::endl << "1 - Stations à proximité" << std::endl
            << "2 - Consulter horaire du bus " << std::endl
            << "3 - Itinéraire " << std::endl
            << "4 - Stats de connectivité " << std:: endl;

    int option = 0;
    std::cout << "Sélectionner une option en indiquant un chiffre ou autre chose pour quitter : ";
    std::getline(std::cin, choixUtilisateur, '\n');
    stream = std::stringstream(choixUtilisateur);
    std::cout << std::endl;
    stream >> option;
    if(option == 1){
        std::cout << "Entrez vos coordonnées GPS" << std::endl;
        double latitude;
        double longitude;
        unsigned int limite;

        std::cout << "Latitude : ";
        std::getline(std::cin, choixUtilisateur, '\n');
        stream = std::stringstream(choixUtilisateur);
        stream >> latitude;

        std::cout << std::endl << "Longitude : ";
        std::getline(std::cin, choixUtilisateur, '\n');
        stream = std::stringstream(choixUtilisateur);
        stream >> longitude;

        std::cout << std::endl << "Entrez un rayon (en Km) pour la recherche : ";
        std::getline(std::cin, choixUtilisateur, '\n');
        stream = std::stringstream(choixUtilisateur);
        stream >> limite;

        std::cout << std::endl;
        std::vector<std::pair<double, Station*>> stationProximite
                = gestion.trouver_stations_environnantes(Coordonnees(latitude,longitude), limite);
        for (auto it = stationProximite.begin(); it != stationProximite.end(); ++it){
            std::cout << "À une distance de " << it->first << "km : " << std::endl;
            std::cout << (*it->second);
        }
    }
    else if(option == 2){
        int an = 2016;
        int mois = 10;
        int jour = 5;
        int heure = 20;
        int minutes = 20;
        int secondes = 44;
        std::string busID;
        int stationID;
        std::cout << "Entrez la date qui vous intéresse!"  << std::endl;

        std::cout << "annee [défaut=2016] : ";
        std::getline(std::cin, choixUtilisateur, '\n');
        if ( !choixUtilisateur.empty() ) {
            stream = std::stringstream(choixUtilisateur);
            stream >> an;
        }


        std::cout << std::endl << "mois [défaut=10] : ";
        std::getline(std::cin, choixUtilisateur, '\n');
        if ( !choixUtilisateur.empty() ) {
            stream = std::stringstream(choixUtilisateur);
            stream >> mois;
        }

        std::cout << std::endl << "jour [défaut=5] : ";
        std::getline(std::cin, choixUtilisateur, '\n');
        if ( !choixUtilisateur.empty() ) {
            stream = std::stringstream(choixUtilisateur);
            stream >> jour;
        }

        std::cout << std::endl << "Entrez l'heure de début de l'horaire!" << std::endl << "heure [défaut=20] :";
        std::getline(std::cin, choixUtilisateur, '\n');
        if ( !choixUtilisateur.empty() ) {
            stream = std::stringstream(choixUtilisateur);
            stream >> heure;
        }

        std::cout << std::endl << "minutes [défaut=20] :";
        std::getline(std::cin, choixUtilisateur, '\n');
        if ( !choixUtilisateur.empty() ) {
            stream = std::stringstream(choixUtilisateur);
            stream >> minutes;
        }

        std::cout << std::endl << "secondes [défaut=44] :";
        std::getline(std::cin, choixUtilisateur, '\n');
        if ( !choixUtilisateur.empty() ) {
            stream = std::stringstream(choixUtilisateur);
            stream >> secondes;
        }

        std::cout << std::endl << "Entrez le numéro du bus: ";
        std::getline(std::cin, choixUtilisateur, '\n');
        stream = std::stringstream(choixUtilisateur);
        stream >> busID;

        std::cout << std::endl << "Entrez le numéro de la station: ";
        std::getline(std::cin, choixUtilisateur, '\n');
        stream = std::stringstream(choixUtilisateur);
        stream >> stationID;

        Date date(an, mois, jour);
        std::vector<Heure> heurePassage =
                gestion.trouver_horaire(Date(an, mois, jour), Heure(heure, minutes, secondes), busID, stationID, "");
        std::cout << gestion.getLigne(busID) << gestion.getStation(stationID);
        for (auto it = heurePassage.begin(); it != heurePassage.end(); ++it){
            std::cout << (*it) << std::endl;
        }

    }
    else if(option == 3){
        //                      lon, lat
        std::vector<std::pair<double,double>> carnet;
        carnet.push_back(std::pair<double, double>(46.760074, -71.319867));
        carnet.push_back(std::pair<double, double>(46.778398, -71.26853));
        carnet.push_back(std::pair<double, double>(46.785923, -71.354046));
        carnet.push_back(std::pair<double, double>(46.776635, -71.270671));
        carnet.push_back(std::pair<double, double>(46.857245, -71.206804));
        carnet.push_back(std::pair<double, double>(46.778808, -71.270014));

        int an = 2016;
        int mois = 10;
        int jour = 5;
        int heure = 20;
        int minutes = 22;
        int secondes = 29;
        int indexDestination;
        int indexDepart;

        std::cout << "Choisir  votre point de départ" << std::endl << "Carnets d'adresse" << std::endl
                  << "1 - 3475 avenue maricourt, Québec: (46.760074, -71.319867) " << std::endl
                  << "2 - 2325 vie étudiante, Québec: (46.778398, -71.26853)" << std::endl
                  << "3 - Cineplex odéon sainte-foy: (46.785923, -71.354046)" << std::endl
                  << "4 - Pavillon pouliot: (46.776635, -71.270671)" << std::endl
                  << "5 - 2476, avenue de lisieux, québec: (46.857245, -71.206804)" << std::endl
                  << "6 - Pavillon desjardin: (46.778808, -71.270014)" << std::endl;

        std::cout << "Sélectionner une adresse en indiquant un chiffre:";
        std::getline(std::cin, choixUtilisateur, '\n');
        if ( !choixUtilisateur.empty() ) {
            stream = std::stringstream(choixUtilisateur);
            stream >> indexDepart;
        }

        std::cout << std::endl << "Choisir  votre point de d'arrivé" << std::endl << "Carnets d'adresse" << std::endl
                  << "1 - 3475 avenue maricourt, Québec: (46.760074, -71.319867) " << std::endl
                  << "2 - 2325 vie étudiante, Québec: (46.778398, -71.26853)" << std::endl
                  << "3 - Cineplex odéon sainte-foy: (46.785923, -71.354046)" << std::endl
                  << "4 - Pavillon pouliot: (46.776635, -71.270671)" << std::endl
                  << "5 - 2476, avenue de lisieux, québec: (46.857245, -71.206804)" << std::endl
                  << "6 - Pavillon desjardin: (46.778808, -71.270014)" << std::endl;

        std::cout << "Sélectionner une adresse en indiquant un chiffre:";
        std::getline(std::cin, choixUtilisateur, '\n');
        if ( !choixUtilisateur.empty() ) {
            stream = std::stringstream(choixUtilisateur);
            stream >> indexDestination;
        }

        std::cout << std::endl << "Entrez la date qui vous intéresse!"  << std::endl;

        std::cout << "annee [défaut=2016] : ";
        std::getline(std::cin, choixUtilisateur, '\n');
        if ( !choixUtilisateur.empty() ) {
            stream = std::stringstream(choixUtilisateur);
            stream >> an;
        }


        std::cout << std::endl << "mois [défaut=10] : ";
        std::getline(std::cin, choixUtilisateur, '\n');
        if ( !choixUtilisateur.empty() ) {
            stream = std::stringstream(choixUtilisateur);
            stream >> mois;
        }

        std::cout << std::endl << "jour [défaut=5] : ";
        std::getline(std::cin, choixUtilisateur, '\n');
        if ( !choixUtilisateur.empty() ) {
            stream = std::stringstream(choixUtilisateur);
            stream >> jour;
        }

        std::cout << std::endl << "Entrez l'heure de début de l'horaire!" << std::endl << "heure [défaut=20] :";
        std::getline(std::cin, choixUtilisateur, '\n');
        if ( !choixUtilisateur.empty() ) {
            stream = std::stringstream(choixUtilisateur);
            stream >> heure;
        }

        std::cout << std::endl << "minutes [défaut=22] :";
        std::getline(std::cin, choixUtilisateur, '\n');
        if ( !choixUtilisateur.empty() ) {
            stream = std::stringstream(choixUtilisateur);
            stream >> minutes;
        }

        std::cout << std::endl << "secondes [défaut=29] :";
        std::getline(std::cin, choixUtilisateur, '\n');
        if ( !choixUtilisateur.empty() ) {
            stream = std::stringstream(choixUtilisateur);
            stream >> secondes;
        }

        std::cout << std::endl << "Initialisation du réseau .... " << std::endl
                  << "Recherche du plus court chemin " << std::endl;
        indexDepart -= 1;
        indexDestination -= 1;
        Coordonnees depart(carnet[indexDepart].first, carnet[indexDepart].second);
        Coordonnees destination(carnet[indexDestination].first, carnet[indexDestination].second);
        std::vector< unsigned int > stationChemin =
                gestion.plus_court_chemin(Date(an, mois, jour), Heure(heure, minutes, secondes), depart, destination);
        std::cout << "0 - Départ" << std::endl;
        for(auto it = stationChemin.begin() + 1; it != stationChemin.end() - 1; ++it){
            std::cout << gestion.getStation((*it));
        }
        std::cout << "1 - Arrivée" << std::endl;
    }
    else if(option == 4){
        int an = 2016;
        int mois = 10;
        int jour = 5;
        int heure = 20;
        int minutes = 22;
        int secondes = 29;

        std::cout << "Entrez la date qui vous intéresse!"  << std::endl;

        std::cout << "annee [défaut=2016] : ";
        std::getline(std::cin, choixUtilisateur, '\n');
        if ( !choixUtilisateur.empty() ) {
            stream = std::stringstream(choixUtilisateur);
            stream >> an;
        }


        std::cout << std::endl << "mois [défaut=10] : ";
        std::getline(std::cin, choixUtilisateur, '\n');
        if ( !choixUtilisateur.empty() ) {
            stream = std::stringstream(choixUtilisateur);
            stream >> mois;
        }

        std::cout << std::endl << "jour [défaut=5] : ";
        std::getline(std::cin, choixUtilisateur, '\n');
        if ( !choixUtilisateur.empty() ) {
            stream = std::stringstream(choixUtilisateur);
            stream >> jour;
        }

        std::cout << std::endl << "Entrez l'heure de début de l'horaire!" << std::endl << "heure [défaut=20] :";
        std::getline(std::cin, choixUtilisateur, '\n');
        if ( !choixUtilisateur.empty() ) {
            stream = std::stringstream(choixUtilisateur);
            stream >> heure;
        }

        std::cout << std::endl << "minutes [défaut=20] :";
        std::getline(std::cin, choixUtilisateur, '\n');
        if ( !choixUtilisateur.empty() ) {
            stream = std::stringstream(choixUtilisateur);
            stream >> minutes;
        }

        std::cout << std::endl << "secondes [défaut=44] :";
        std::getline(std::cin, choixUtilisateur, '\n');
        if ( !choixUtilisateur.empty() ) {
            stream = std::stringstream(choixUtilisateur);
            stream >> secondes;
        }
        bool avecTranfert = gestion.reseau_est_fortement_connexe(Date(an, mois, jour),
                                                                 Heure(heure, minutes, secondes), true);
        bool sansTranfert = gestion.reseau_est_fortement_connexe(Date(an, mois, jour),
                                                                 Heure(heure, minutes, secondes), false);
        std::cout<< "Avec les arêtes de transfert, ";
        if (avecTranfert == true){
            std::cout << "le réseau est fortement connexe." << std::endl;
        }
        else{
            std::cout << "le réseau n'est pas fortement connexe." << std::endl;
        }

        std::cout<< "Sans les arêtes de transfert, ";
        if (sansTranfert == true){
            std::cout << "le réseau est fortement connexe." << std::endl;
        }
        else{
            std::cout << "le réseau n'est pas fortement connexe." << std::endl;
        }

    }

}

