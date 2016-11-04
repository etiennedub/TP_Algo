//
// Created by etienned on 10/31/16.
//
#include "gestionnaire.h"

Gestionnaire::Gestionnaire(std::string chemin_dossier) {
    std::unordered_multimap <std::string, Arret> mapArret;
    std::unordered_map <unsigned int, Ligne*> mapLigneID;
    std::unordered_map <std::string, Voyage*> mapVoyageServiceID;


    // Creation objets Station
    std::vector<std::vector<std::string>> fichier;
    lireFichier(chemin_dossier + "/stops.txt", fichier, ',', true);
    for (int i = 0; i < fichier.size(); i++) {
        Station station = Station(fichier[i]);
        m_stations.insert({station.getId(), station});
    }

    // Creation objets Arret
    fichier.clear();
    lireFichier(chemin_dossier + "/stop_times.txt", fichier, ',', true);
    for (int i = 0; i < fichier.size(); i++){
        Arret arret = Arret(fichier[i]);
        mapArret.insert({arret.getVoyageId(), arret});
    }

    // Creation objets Ligne
    fichier.clear();
    lireFichier(chemin_dossier + "/stops.txt", fichier, ',', true);
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


}

bool Gestionnaire::date_est_prise_en_charge(const Date& date){
<<<<<<< HEAD

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


std::vector<std::pair<double, Station*>>Gestionnaire::trouver_stations_environnantes(Coordonnees coord, double rayon){

}
