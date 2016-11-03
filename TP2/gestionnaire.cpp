//
// Created by etienned on 10/31/16.
//
#include "gestionnaire.h"

Gestionnaire::Gestionnaire(std::string chemin_dossier) {
//    // expemple lecture fichier
//    std::string file_p = path;
//    std::vector<std::vector<std::string>> resultats;
//    lireFichier(file_p, resultats, ',' , true);

    std::vector<std::vector<std::string>> fichierRoutes;
    std::vector<std::vector<std::string>> fichierTrips;
    std::vector<std::vector<std::string>> fichierStopTimes;
    std::vector<std::vector<std::string>> fichierStops;
    std::vector<std::vector<std::string>> fichierCalendarDates;

    lireFichier(chemin_dossier + "/routes.txt", fichierRoutes, ',', true);
    lireFichier(chemin_dossier + "/trips.txt", fichierTrips, ',', true);
    lireFichier(chemin_dossier + "/stop_times.txt", fichierStopTimes, ',', true);
    lireFichier(chemin_dossier + "/stops.txt", fichierStops, ',', true);
    lireFichier(chemin_dossier + "/calendar_dates.txt", fichierCalendarDates, ',', true);

    // Creation objets station
    for (int i = 0; i < fichierStops.size(); i++) {
        Station station = Station(fichierStops[i]);
        // mapStation.insert({tempo.getId(), tempo});
    }
}

bool Gestionnaire::date_est_prise_en_charge(const Date& date){
		//return (m_voyages_date.count(date) > 0);
}

bool Gestionnaire::bus_existe(std::string num_ligne){
		return (m_lignes.count(num_ligne) > 0);
}

bool Gestionnaire::station_existe(int station_id){

		return (m_stations.count(station_id) >0 );
}

Ligne Gestionnaire::getLigne(std::string num_ligne){

}

