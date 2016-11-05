//
// Created by etienned on 10/31/16.
//
#include "gestionnaire.h"

Gestionnaire::Gestionnaire(std::string chemin_dossier) {
    std::unordered_multimap <std::string, Arret> mapArret;
    std::unordered_map <unsigned int, Ligne*> mapLigneID;
    std::unordered_map <std::string, Voyage*> mapVoyageServiceID;
    std::unordered_map <std::string, Voyage*> mapVoyageTripID;
    //                  stopID,      tripID
    std::unordered_map <unsigned int, std::vector<std::string>> stopIDtoTripID;
    std::vector<std::vector<std::string>> fichier;

    // Creation objets Arret
    fichier.clear();
    lireFichier(chemin_dossier + "/stop_times.txt", fichier, ',', true);
    for (int i = 0; i < fichier.size(); i++){
        Arret arret = Arret(fichier[i]);
        mapArret.insert({arret.getVoyageId(), arret});
        unsigned int stopID = std::stoi(fichier[i][3]);
        std::string tripID = fichier[i][0];
        auto itExiste = stopIDtoTripID.find(stopID);
        if ( itExiste != stopIDtoTripID.end()){
            // Existe
            itExiste->second.push_back(tripID);
        }
        else{
            // Nouveau stopID
            std::vector<std::string> vecTripID;
            vecTripID.push_back(tripID);
            stopIDtoTripID.insert({stopID, vecTripID});
        }

    }

    // Creation objets Ligne
    fichier.clear();
    lireFichier(chemin_dossier + "/routes.txt", fichier, ',', true);
    for (int i = 0; i < fichier.size(); i++){
        Ligne ligne = Ligne(fichier[i]);
        auto ligneExiste = m_lignes.find(ligne.getNumero());
        if (ligneExiste != m_lignes.end()) {
            // Ligne existe
            ligneExiste->second.second.push_back(ligne.getId());
            mapLigneID.insert({ligneExiste->second.first.getId(), &ligneExiste->second.first});
        }
        else{
            // Ligne non presente
            std::vector<unsigned int> vectorID;
            vectorID.push_back(ligne.getId());
            m_lignes.insert({ligne.getNumero(), std::pair<Ligne, std::vector<unsigned int>>
                    (ligne, vectorID)});
            mapLigneID.insert({ligne.getId(), &ligne});
        }
    }

    // Creation objets Voyage
    fichier.clear();
    lireFichier(chemin_dossier + "/trips.txt", fichier, ',', true);
    for (int i = 0; i < fichier.size(); i++){
        unsigned int routeID = std::stoi(fichier[i][0]);
        Ligne* ligneVoyage = mapLigneID[routeID];
        Voyage voyage = Voyage(fichier[i], ligneVoyage);

        auto range = mapArret.equal_range(fichier[i][2]);
        std::vector<Arret> vecArret;
        for ( auto it = range.first ; it != range.second; ++it){
            vecArret.push_back(it->second);
        }
        voyage.setArrets(vecArret);
        m_voyages.insert({std::stoi(voyage.getId()), voyage});
        mapVoyageServiceID.insert({fichier[i][0], &voyage});
        mapVoyageTripID.insert({fichier[i][2], &voyage});
    }

    // Lien avec les Dates
    fichier.clear();
    lireFichier(chemin_dossier + "/calendar_dates.txt", fichier, ',', true);
    for (int i = 0; i < fichier.size(); i++){
        std::string serviceID = fichier[0][1];
        unsigned int an = std::stoi(fichier[i][0,4]);
        unsigned int mois = std::stoi(fichier[i][4,6]);
        unsigned int jour = std::stoi(fichier[i][6,8]);
        Date date = Date(an, mois, jour);
        m_voyages_date.insert({date, mapVoyageServiceID[serviceID]});


    }

    // Creation objets Station
    fichier.clear();
    lireFichier(chemin_dossier + "/stops.txt", fichier, ',', true);
    for (int i = 0; i < fichier.size(); i++) {
        Station station = Station(fichier[i]);
        unsigned int stopID = std::stoi(fichier[i][0]);
        std::vector<Voyage*> vecVoyage;
        for ( auto itTripID = stopIDtoTripID[stopID].begin(); itTripID != stopIDtoTripID[stopID].end(); itTripID++){
            station.addVoyage(mapVoyageTripID[(*itTripID)]);
        }
        m_stations.insert({station.getId(), station});
    }
}

bool Gestionnaire::date_est_prise_en_charge(const Date& date){
	return (m_voyages_date.find(date) != m_voyages_date.end());

}


Station Gestionnaire::getStation(int station_id){
	auto itr = m_stations.find(station_id);
	//if(m_stations.find(station_id) == m_stations.end()){
	if(itr != end(m_stations)){
		return itr->second;
	}
	else{
		throw "Il n'existe pas de station ayant cet identifiant";

	}
}

/*std::pair<std::string, std::string> get_bus_destinations(int station_id, std::string num_ligne){

		//return (m_voyages_date.count(date) > 0);
=======
		return (m_voyages_date.find(date) != m_voyages_date.end());
>>>>>>> bccbf289d2644e5f35953abfd0e917cada4ac409
}*/

bool Gestionnaire::bus_existe(std::string num_ligne){
		return (m_lignes.find(num_ligne) != m_lignes.end());
}

bool Gestionnaire::station_existe(int station_id){
		return (m_stations.count(station_id) >0 );
}

std::vector<Voyage*> Gestionnaire::trouver_voyages(int station_id, std::string num_ligne){
		return (m_stations.find(station_id) != m_stations.end());
}

Ligne Gestionnaire::getLigne(std::string num_ligne){
    return m_lignes.at(num_ligne).first;
}

<<<<<<< HEAD

std::vector<std::pair<double, Station*>>Gestionnaire::trouver_stations_environnantes(Coordonnees coord, double rayon){

}

Station Gestionnaire::getStation(int station_id){
    return m_stations.at(station_id);
}

std::pair<std::string, std::string> Gestionnaire::get_bus_destinations(int station_id, std::string num_ligne){
    std::vector<Ligne*> vecLigne = getStation(station_id).getLignesPassantes();
    std::pair<std::string, std::string> resultat = std::pair<std::string, std::string> ("","");
    for (auto it  = vecLigne.begin(); it != vecLigne.end(); it++){
        if ( (*it)->getNumero() == num_ligne){
            resultat = (*it)->getDestinations();
            break;
        }
    }
    return resultat;
}


