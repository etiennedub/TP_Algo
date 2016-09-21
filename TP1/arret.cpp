/*
 * arret.cpp
 *
 *  Created on: 2016-09-14
 *      Author: etudiant
 */
#include "arret.h"

Arret::Arret(const std::vector<std::string>& ligne_gtfs){
	m_station_id = std::stoi(ligne_gtfs[3]);
	std::vector<std::string> heureTempo = split(ligne_gtfs[1],':');
	Heure m_heure_arrivee(std::stoi(heureTempo[0]), std::stoi(heureTempo[1]), std::stoi(heureTempo[2]));
	heureTempo = split(ligne_gtfs[2],':');
	Heure m_heure_depart(std::stoi(heureTempo[0]), std::stoi(heureTempo[1]),
			std::stoi(heureTempo[2]));
	m_numero_sequence = std::stoi(ligne_gtfs[4]);;
	m_voyage_id = ligne_gtfs[0];
}


const Heure& Arret::getHeureArrivee() const{
	return m_heure_arrivee;
 }
void Arret::setHeureArrivee(const Heure& p_heureArrivee){
	m_heure_arrivee = p_heureArrivee;
 }
const Heure& Arret::getHeureDepart() const{
	return m_heure_depart;
 }
void Arret::setHeureDepart(const Heure& p_heureDepart){
	m_heure_depart = p_heureDepart;
 }
unsigned int Arret::getNumeroSequence() const{
	return m_numero_sequence;
 }
void Arret::setNumeroSequence(unsigned int p_numeroSequence){
	m_numero_sequence = p_numeroSequence;
 }
unsigned int Arret::getStationId() const{
	return m_station_id;
 }
void Arret::setStationId(unsigned int stationId){
	m_station_id = stationId;
 }
std::string Arret::getVoyageId() const{
	return m_voyage_id;
 }
void Arret::setVoyageId(const std::string& voyageId){
	m_voyage_id = voyageId;
 }

bool Arret::operator< (const Arret & p_other) const{
	return( m_numero_sequence < p_other.m_numero_sequence);
}
bool Arret::operator> (const Arret & p_other) const{
	return( m_numero_sequence > p_other.m_numero_sequence);
}
std::ostream & operator<<(std::ostream & flux, const Arret & p_arret){
	// A faire
}
