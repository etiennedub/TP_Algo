/*
 * coordonnees.cpp
 *
 *  Created on: 2016-09-14
 *      Author: etudiant
 */

#include "coordonnees.h"

Coordonnees::Coordonnees(double latitude, double longitude){
	if (!is_valide_coord(latitude, longitude)){
		throw std::invalid_argument("Coordonnees non valide");
	}
	else{
		m_latitude = latitude;
		m_longitude = longitude;
	}
}

double Coordonnees::getLatitude() const {
	return m_latitude;
}

void Coordonnees::setLatitude(double latitude) {
	m_latitude = latitude;
}

double Coordonnees::getLongitude() const {
	return m_longitude;
}

void Coordonnees::setLongitude(double longitude) {
	m_longitude = longitude;
 }

bool Coordonnees::is_valide_coord(double p_latitude, double p_longitude) {
	return(p_latitude < 80 && -180 < p_longitude && 180 > p_longitude);
 }

double Coordonnees::operator- (const Coordonnees & other) const{
	const double pi = std::acos(-1);
	double lat1 = (m_latitude * 180) / pi;
	double lon1 = (m_longitude * 180) / pi;
	double lat2 = (other.m_latitude * 180) / pi;
	double lon2 = (other.m_longitude * 180) / pi;
	double rayonTerreKm = 6371;

	return( rayonTerreKm * std::acos(std::sin(lat1)*std::sin(lat2)
			+std::cos(lat1)*std::cos(lat2)*std::cos(lon2-lon1)));
 }
