//
// Created by etienned on 10/31/16.
//
#include "gestionnaire.h"

Gestionnaire::Gestionnaire(std::string chemin_dossier){


}

bool Gestionnaire::date_est_prise_en_charge(const Date& date){
	std::unordered_map<std::string,int>::iterator it;
	for(it = m_voyages.begin(); it != m_voyages.end(); it++){
		if(m_voyages_date.count(date)>0)
			return true;
		else
			return false;
	}
}

bool Gestionnaire::bus_existe(std::string num_ligne){
	std::unordered_map<std::string,int>::iterator it;
	for(it = m_lignes.begin(); it != m_lignes.end(); it++){
		if(m_lignes.count(num_ligne)>0)
			return true;
		else
			return false;
	}
}

bool Gestionnaire::station_existe(int station_id){
	std::unordered_map<std::string,int>::iterator it;
	for(it = m_stations.begin(); it != m_stations.end(); it++){
		if(m_stations.count(station_id)>0)
			return true;
		else
			return false;
	}
}

Ligne Gestionnaire::getLigne(std::string num_ligne){

}

Station Gestionnaire::getStation(int station_id){

}

std::pair<std::string, std::string> get_bus_destinations(int station_id, std::string num_ligne){

}

std::vector<std::pair<double, Station*>> trouver_stations_environnantes(Coordonnees coord, double rayon){

}

std::vector<Heure> trouver_horaire(Date date, Heure heure, std::string numero_ligne, int station_id, std::string destination){

}

/*bool Gestionnaire::reseau_est_fortement_connexe(Date date, Heure heure_debut, bool considerer_transfert=true){

}

void Gestionnaire::composantes_fortement_connexes(Date date, Heure heure_debut,
			std::vector< std::vector<unsigned int> >& composantes, bool considerer_transfert=true){

}*/

std::vector< unsigned int > plus_court_chemin(Date date, Heure heure_depart, Coordonnees depart, Coordonnees destination){

}
