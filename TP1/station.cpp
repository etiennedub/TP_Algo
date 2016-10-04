/*
 * station.cpp
 *
 *  Created on: 2016-09-14
 *      Author: etudiant
 */

#include "station.h"

Station::Station(const std::vector<std::string>& ligne_gtfs) :
		m_coords(std::stod(ligne_gtfs[3]),std::stod(ligne_gtfs[4])),
		m_id(std::stoi(ligne_gtfs[0])),
		m_nom(ligne_gtfs[1]),
		m_description(ligne_gtfs[2]),
		m_voyages_passants({}){
	m_description = m_description.substr(1, m_description.size()-2);
}

const Coordonnees& Station::getCoords() const{
	return m_coords;
}
void Station::setCoords(const Coordonnees& coords){
	m_coords = coords;
}
const std::string& Station::getDescription() const{
	return m_description;
}
void Station::setDescription(const std::string& description){
	m_description = description;
}
const std::string& Station::getNom() const{
	return m_nom;
}
void Station::setNom(const std::string& nom){
	m_nom = nom;
}
unsigned int Station::getId() const{
	return m_id;
}
void Station::setId(unsigned int stationId){
	m_id = stationId;
}
const std::vector<Voyage*> & Station::getVoyagesPassants() const{
	return m_voyages_passants;
}

void Station::addVoyage(Voyage* ptr_voyage){
	m_voyages_passants.push_back(ptr_voyage);
}
double Station::distance(const Station& p_station) const{
	return (m_coords - p_station.m_coords);
}

std::vector<Ligne*> Station::getLignesPassantes() const{
	return m_voyages_passants;
}

std::ostream& operator<<(std::ostream& flux, const Station& p_station){
	flux << p_station.m_id << " - " << p_station.m_description;
	return flux;
}
