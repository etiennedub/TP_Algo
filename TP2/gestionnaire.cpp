//
// Created by etienned on 10/31/16.
//
#include "gestionnaire.h"

/**
 * \brief Constructeur de la class Gestionnaire. Lire et charger les
 * fichier gtfs: routes.txt, trips.txt, stop_times.txt, calendar_dates.txt
 *
 * \param string chemin_dossier: chemin d'acces vers le dossier gtfs
 */
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

/**
 * \brief destructeur de la class Gestionnaire.
 */
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


/**
 * \brief Permet de vérifier si une date existe dans l'ensemble des dates de "calendar.txt"
 * lors de la construction du gestionnaire.
 * \param date: la date d'intérêt
 * \return True ssi la date est prise en charge dans l'application
 */
bool Gestionnaire::date_est_prise_en_charge(const Date& date){
	return (m_voyages_date.find(date) != m_voyages_date.end());

}


/*!
* \brief Permet de vérifier si une ligne avec un certain numéro existe dans l’ensemble des
lignes chargées dans le constructeur.
* \param num_ligne: le numéro de la ligne d'intérêt
* \return True ssi le numéro est pris en charge
*/
bool Gestionnaire::bus_existe(std::string num_ligne){
		return (m_lignes.find(num_ligne) != m_lignes.end());
}

/*!
* \brief Permet de vérifier si un numéro de station existe dans l’ensemble des stations
chargées dans le constructeur.
* \param station_id: l'identifiant de la station d'intérêt
* \return True ssi la station est prise en charge
*/
bool Gestionnaire::station_existe(int station_id){
		return (m_stations.find(station_id) != m_stations.end());
}

/*!
* \brief Permet de trouver les voyages d'une ligne qui passe par une station
* \param station_id: l'identifiant de la station d'intérêt
* \param num_ligne: le numéro de la ligne d'intérêt
* \return un vecteur contenant des pointeurs vers les voyages trouvés
* \exception logic_error si la station est inexistante
* \exception logic_error si la ligne est inexistante
*/
std::vector<Voyage*> Gestionnaire::trouver_voyages(int station_id, std::string num_ligne){
    std::vector<Voyage*> resultat;
    std::vector<Voyage*> temporaire = m_stations.find(station_id)->second->getVoyagesPassants();
    for (auto it = temporaire.begin(); it != temporaire.end(); ++it){
        if((*it)->getLigne()->getNumero() == num_ligne){
            resultat.push_back((*it));
        }
    }
    return resultat;
}

/*!
* \brief Accès à une ligne à partir de son numéro
* \param num_ligne: le numéro de la ligne d'intérêt
* \return objet Ligne correspondant au numéro d'intérêt
* \exception Il n’existe pas de ligne ayant ce numéro
*/
Ligne Gestionnaire::getLigne(std::string num_ligne){
    return (*(m_lignes.at(num_ligne).first));
}

/*!
* \brief Accès à une station à partir de son id
* \param station_id: l'identifiant de la station d'intéret
* \return objet Station correspondant à l'id d'intérêt
* \exception Il n’existe pas de station ayant cet identifiant
*/
Station Gestionnaire::getStation(int station_id){
    return (*(m_stations.at(station_id)));
}

/*!
* \brief Permet d'obtenir les destinations des voyages d'une ligne s’arrêtant à une station.
* Notez qu'une ligne de bus ne peut pas avoir plus de deux destinations possibles: une pour
l'aller et l'autre pour le retour.
* Dans le cas de certains bus (ex: couche-tard), une seule destination est possible.
* \param num_ligne: numéro de la ligne d'intérêt
* \param station_id: numéro de la station d'intérêt
* \return Une paire de chaîne de caractères.
* Si le bus ne passe pas par la station, alors une paire de chaîne vide est retournée. \n
* Sinon Si le bus a deux destinations possibles les deux éléments de la paire doivent être
différents de la chaîne vide.
* Si le bus a une seule destination possible, le dernier élément de la paire seulement est
* égale à une chaîne vide.
*
*/
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

/*!
* \brief Trouver des stations environnantes étant donnée une coordonnée gps et un rayon
* \param coord: Coordonnée gps d'intérêt
* \param rayon: cette distance défini la circonférence a l'intérieure de laquelle on se trouve
les stations que l'on cherche
* \return un vecteur de paires (distance, pointeur vers une station) trié par distance
*/
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

/*!
* \brief Trouver le plus court chemin en autobus pour aller d'un point A vers un point B
dans l’interval de temps défini par interval_planification_en_secondes
* à partir d'une heure de départ et pour une date donnée
* Pour ce faire, il faut initialiser le réseau, puis faire appel à ses routines de plus courts
chemin
* \param date: la date de planification
* \param heure_depart: l'heure de début de planification
* \param depart: coordonnées gps du point de départ de votre déplacement
* \param destination: coordonnées gps du point de d'arrivée de votre déplacement
* \return Un vecteur contenant les stations du chemin trouvé, le vecteur est vide si aucun
chemin n’est trouvé
*/
std::vector< unsigned int > Gestionnaire::plus_court_chemin(Date date, Heure heure_depart, Coordonnees depart, Coordonnees destination){
    initialiser_reseau(date, heure_depart, Heure(29,59,59), depart, destination);
    std::vector< unsigned int > chemin;
    int coutTotal = m_reseau.bellmanFord(0,1,chemin);
    return chemin;
}

/*!
* \brief trouver l'horaire d'un bus à une station
* \param date: la date d'intérêt
* \param heure: l'heure à partir de laquelle on veut l'horaire
* \param numero_ligne: numéro de la ligne dont on cherche l'horaire
* \param station_id: l'identifiant de la station où on veut connaitre l'horaire de passage du
bus
* \param destination: permet de spécifier dans quelle direction on veut l'horaire.
* Ceci est pertinent car à certaines stations, la même ligne de bus peut passer dans les deux
sens.
* \return un vecteur contenant les heures d'arrivée (en ordre croissant) du bus à la station
d'intérêt
* \exception logic_error si la station est inexistante
* \exception logic_error si la ligne est inexistante
*/
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


/*!
* \brief initialiser ou réinitialiser l'attribut m_reseau en fonction des paramètres.
* La date et l'interval de temps spécifié par l'utilisateur servent à trouver les arcs empruntés
par les bus dans le réseau.
* Les coordonnées de départ et de destination servent à ajouter des stations fictives ayant
respectivement les numéros 0 et 1.
La dist_de_marche sert à ajouter les arcs entre ces stations fictives et toutes les autres
stations dans un rayon de dist_de_marche.
* La dist_transfert permet d'ajouter des arcs de transfert entre les stations qui sont à une
distance l'une de l'autre inférieure à dist_transfert
* \param date: la date d'intérêt
* \param heure_depart: l'heure de début.
* \param heure_fin: l'heure de fin.
* \param depart: coordonnées gps du point de départ du déplacement pour lequel on
initialise le réseau
* \param dest: coordonnées gps du point de d'arrivée du déplacement pour lequel on
initialise le réseau
* \param dist_de_marche: permet de spécifier qu’on ne veut pas marcher plus de cette
distance avant de prendre le bus à partir du point de départ, ou pour se rendre au point de
destination à partir de la sortie du bus.
* \param dist_transfert: distance maximale de marche pour un transfert de bus
*/
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

bool Gestionnaire::reseau_est_fortement_connexe(Date date, Heure heure_debut, bool considerer_transfert){
    int dist_transfert = 0;
    if (considerer_transfert) dist_transfert = INFINI;
    initialiser_reseau(date, heure_debut, Heure(29,59,59), Coordonnees(46.760074, -71.319867),
                       Coordonnees(46.778398, -71.2685), INFINI, dist_transfert);
    return m_reseau.estFortementConnexe();
}

void Gestionnaire::composantes_fortement_connexes(Date date, Heure heure_debut,
                                    std::vector< std::vector<unsigned int> >& composantes, bool considerer_transfert){
    int dist_transfert = 0;
    if (considerer_transfert) dist_transfert = INFINI;
    initialiser_reseau(date, heure_debut, Heure(29,59,59), Coordonnees(46.760074, -71.319867),
                       Coordonnees(46.778398, -71.2685), INFINI, dist_transfert);
    m_reseau.getComposantesFortementConnexes(composantes);
}