
/*
 * voyage.cpp
 *
 *  Created on: 2016-09-14
 *      Author: etudiant
 */
#include "voyage.h"

Voyage::Voyage(const std::vector<std::string>& ligne_gtfs, Ligne* p_ligne){
	m_id = ligne_gtfs[0];
	m_ligne = p_ligne;
	m_service_id = ligne_gtfs[1];
	m_destination = ligne_gtfs[3].substr(1, ligne_gtfs[3].size() -2);
	m_arrets = {};
}


std::vector<Arret> Voyage::getArrets() const{
	return m_arrets;
 }
const std::string& Voyage::getDestination() const{
	return m_destination;
 }
void Voyage::setDestination(const std::string& p_destination){
	m_destination = p_destination;
 }
std::string Voyage::getId() const{
	return m_id;
 }
void Voyage::setId(std::string p_id){
	m_id = p_id;
 }
Ligne* Voyage::getLigne() const{
	return m_ligne;
 }
void Voyage::setLigne(Ligne* p_ligne){
	m_ligne = p_ligne;
 }
std::string Voyage::getServiceId() const{
	return m_service_id;
 }
void Voyage::setServiceId(std::string p_service_id){
	m_service_id = p_service_id;
 }
Heure Voyage::getHeureDepart() const{
	if(m_arrets.size() > 0){
		return m_arrets[0].getHeureDepart();
	}
	else {
		// Pas d'objet arret
	}
 }
Heure Voyage::getHeureFin() const{
	if(m_arrets.size() > 0){
			return m_arrets[-1].getHeureArrivee();
		}
		else {
			// Pas d'objet arret
		}
 }
void Voyage::setArrets(std::vector<Arret>& resultat){
	m_arrets = resultat;

	Heure derniereHeure;
	std::sort(m_arrets.begin(), m_arrets.end());
	for(auto it = m_arrets.begin(); it < m_arrets.end(); ++it){
		Heure actuelHeure = it->getHeureDepart();
		if(actuelHeure == derniereHeure){
			actuelHeure.add_secondes(30);
			it->setHeureDepart(actuelHeure);
			std::sort(m_arrets.begin(), m_arrets.end());
			it--;
		}
		else{
			derniereHeure = actuelHeure;
		}
	}
 }

bool Voyage::operator< (const Voyage & p_other) const{
	return(this->getHeureDepart() < p_other.getHeureDepart());
}
bool Voyage::operator> (const Voyage & p_other) const{
	return(this->getHeureDepart() > p_other.getHeureDepart());
}


Arret & Voyage::arretDeLaStation(unsigned int p_num_station){
	Arret* resultat;
	bool trouve = false;
	for(int i = 0; i < m_arrets.size(); i++){
		if(m_arrets[i].getStationId() == p_num_station){
			resultat = &m_arrets[i];
			trouve = true;
			break;
		}
	}
	return (*resultat);
}

std::ostream & operator<<(std::ostream & flux, const Voyage & p_voyage){
	flux << p_voyage.getLigne()->getNumero() << ": Vers ";
	flux << p_voyage.m_destination << "\n";
	for( int i = 0; i < p_voyage.getArrets().size(); i++){
		flux << p_voyage.getArrets()[i];
	}
}
