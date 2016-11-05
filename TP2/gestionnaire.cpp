//
// Created by etienned on 10/31/16.
//
#include "gestionnaire.h"

Gestionnaire::Gestionnaire(std::string chemin_dossier) {
    std::unordered_map <unsigned int, Ligne*> mapLigneID;
    std::unordered_multimap <std::string, Voyage*> mapVoyageServiceID;
    std::unordered_map <std::string, Voyage*> mapVoyageTripID;
    //                  stopID,      tripID
    std::unordered_map <unsigned int, std::vector<std::string>> stopIDtoTripID;
    std::vector<std::vector<std::string>> fichier;

    // Creation objets Arret
    fichier.clear();
    lireFichier(chemin_dossier + "/stop_times.txt", fichier, ',', true);
    for (int i = 0; i < fichier.size(); i++){
        Arret* arret = new Arret(fichier[i]);
        m_arrets.insert({arret->getVoyageId(), arret});
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
        Ligne* ligne = new Ligne(fichier[i]);
        auto ligneExiste = m_lignes.find(ligne->getNumero());
        if (ligneExiste != m_lignes.end()) {
            // Numero present
            ligneExiste->second.second.push_back(ligne->getId());
            mapLigneID.insert({ligne->getId(), ligneExiste->second.first});
        }
        else{
            // Numero non present
            std::vector<unsigned int> vectorID;
            vectorID.push_back(ligne->getId());
            m_lignes.insert({ligne->getNumero(), std::pair<Ligne *, std::vector<unsigned int>>
                    (ligne, vectorID)});
            mapLigneID.insert({ligne->getId(), ligne});
        }

    }

    // Creation objets Voyage
    fichier.clear();
    lireFichier(chemin_dossier + "/trips.txt", fichier, ',', true);
    for (int i = 0; i < fichier.size(); i++){
        unsigned int routeID = std::stoi(fichier[i][0]);

        Ligne* ligneVoyage = mapLigneID[routeID];
        Voyage * voyage =  new Voyage(fichier[i], ligneVoyage);

        auto range = m_arrets.equal_range(fichier[i][2]);
        std::vector<Arret> vecArret;
        for ( auto it = range.first ; it != range.second; ++it){
            vecArret.push_back(*(it->second));
        }
        voyage->setArrets(vecArret);
        m_voyages.insert({std::stoi(voyage->getId()), voyage});
        mapVoyageServiceID.insert({fichier[i][1], voyage});
        mapVoyageTripID.insert({fichier[i][2], voyage});
    }

    // Lien avec les Dates
    fichier.clear();
    lireFichier(chemin_dossier + "/calendar_dates.txt", fichier, ',', true);
    for (int i = 0; i < fichier.size(); i++){
        std::string serviceID = fichier[0][0];
        unsigned int an = std::stoi(fichier[i][1].substr(0,4));
        unsigned int mois = std::stoi(fichier[i][1].substr(4,2));
        unsigned int jour = std::stoi(fichier[i][1].substr(6,2));
        Date date = Date(an, mois, jour);
        auto range = mapVoyageServiceID.equal_range(serviceID);
        for ( auto it = range.first ; it != range.second; ++it) {
            m_voyages_date.insert({date, it->second});
        }
    }

    // Creation objets Station
    fichier.clear();
    lireFichier(chemin_dossier + "/stops.txt", fichier, ',', true);
    for (int i = 0; i < fichier.size(); i++) {
        Station* station = new Station(fichier[i]);
        unsigned int stopID = std::stoi(fichier[i][0]);
        std::vector<Voyage*> vecVoyage;
        for ( auto itTripID = stopIDtoTripID[stopID].begin(); itTripID != stopIDtoTripID[stopID].end(); itTripID++){
            station->addVoyage(mapVoyageTripID[(*itTripID)]);
        }
        m_stations.insert({station->getId(), station});
    }
}

Gestionnaire::~Gestionnaire(){
    for(auto it = m_lignes.begin(); it != m_lignes.end(); ++it){
        delete it->second.first;
    }

    for(auto it = m_stations.begin(); it != m_stations.end(); ++it){
        delete it->second;
    }

    for(auto it = m_voyages.begin(); it != m_voyages.end(); ++it){
        delete it->second;
    }

    for(auto it = m_arrets.begin(); it != m_arrets.end(); ++it){
        delete it->second;
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
    return (*(m_lignes.at(num_ligne).first));
}

<<<<<<< HEAD

std::vector<std::pair<double, Station*>>Gestionnaire::trouver_stations_environnantes(Coordonnees coord, double rayon){

}

Station Gestionnaire::getStation(int station_id){
    return (*(m_stations.at(station_id)));
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

std::vector<std::pair<double, Station*>> Gestionnaire::trouver_stations_environnantes(Coordonnees coord, double rayon){
    std::vector<std::pair<double, Station*>> resultat;
    for (auto it = m_stations.begin(); it != m_stations.end(); ++it){
        double distance = it->second->getCoords() - coord;
        if (distance <= rayon){
            resultat.push_back(std::pair<double, Station*>(distance, it->second));
        }
    }
    return resultat;
};
std::vector< unsigned int > Gestionnaire::plus_court_chemin(Date date, Heure heure_depart, Coordonnees depart, Coordonnees destination){
    initialiser_reseau(date, heure_depart, Heure(29,59,59), depart, destination);
    std::vector< unsigned int > chemin;
    int coutTotal = m_reseau.bellmanFord(0,1,chemin);
    return chemin;
}

std::vector<Heure> Gestionnaire::trouver_horaire(Date date, Heure heure, std::string numero_ligne,
                                   int station_id, std::string destination){
    std::vector<Heure> resultat;
    auto range = m_voyages_date.equal_range(date);
    for ( auto it = range.first ; it != range.second; ++it){
        if(it->second->getLigne()->getNumero() == numero_ligne){
            try {
                Arret arret = it->second->arretDeLaStation(station_id);
                if (arret.getHeureDepart() < heure) {
                    resultat.push_back(arret.getHeureDepart());
                }
            }
            catch (std::logic_error e){

            }
        }
    }
    std::sort(resultat.begin(), resultat.end());
    return (resultat);
}

void Gestionnaire::initialiser_reseau(Date date, Heure heure_depart, Heure heure_fin, Coordonnees depart, Coordonnees dest,
                        double dist_de_marche, double dist_transfert){

    auto rangeDateValide = m_voyages_date.equal_range(date);
    for ( auto itVoyage = rangeDateValide.first ; itVoyage != rangeDateValide.second; ++itVoyage){
        if (itVoyage->second->getHeureDepart() > heure_depart){
            std::vector<Arret> arretDuJour = itVoyage->second->getArrets();
            auto itArret = arretDuJour.begin();
            Arret derniereArret  = (*(itArret));
            m_reseau.ajouterSommet(derniereArret.getStationId());
            itArret++;
            for (; itArret != arretDuJour.end(); ++itArret){
                if (itArret->getHeureDepart() < heure_fin) {
                    int cout = itArret->getHeureDepart() - derniereArret.getHeureDepart();
                    m_reseau.ajouterArc(derniereArret.getStationId(), itArret->getStationId(), cout);
                    if (!m_reseau.sommetExiste(itArret->getStationId())) {
                        m_reseau.ajouterSommet(itArret->getStationId());
                    }
                    derniereArret = (*(itArret));
                }
                else{ break;}
            }
        }
    }

    // Ajout station depart
    m_reseau.ajouterSommet(0);
    std::vector<std::pair<double, Station*>> stationAProximite = trouver_stations_environnantes(depart, dist_de_marche);
    for (auto itStation = stationAProximite.begin(); itStation != stationAProximite.end(); ++itStation) {
        if (!m_reseau.sommetExiste(itStation->second->getId())){
            m_reseau.ajouterSommet(itStation->second->getId());
        }
        double cout = (itStation->first / vitesse_de_marche) * 3600;
        m_reseau.ajouterArc(0, itStation->second->getId(), cout);
    }

    // Ajout station destination
    m_reseau.ajouterSommet(1);
    stationAProximite = trouver_stations_environnantes(dest, dist_de_marche);
    for (auto itStation = stationAProximite.begin(); itStation != stationAProximite.end(); ++itStation) {
        if (!m_reseau.sommetExiste(itStation->second->getId())){
            m_reseau.ajouterSommet(itStation->second->getId());
        }
        double cout = (itStation->first / vitesse_de_marche) * 3600;
        m_reseau.ajouterArc(itStation->second->getId(), 1, cout);
    }
}
