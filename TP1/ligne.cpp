/*
 * ligne.cpp
 *
 *  Created on: 2016-09-14
 *      Author: etudiant
 */
#include "ligne.h"

Ligne::Ligne(const std::vector<std::string>& ligne_gtfs){
    m_id = std::stoi(ligne_gtfs[0]);
    m_numero = ligne_gtfs[2];
    m_numero = m_numero.substr(1, m_numero.size() - 2);
    m_description = ligne_gtfs[4];
    m_description = m_description.substr(1, m_description.size() - 2);
    m_voyages = {};
    m_categorie = couleurToCategorie(ligne_gtfs[7]);
}

CategorieBus Ligne::couleurToCategorie(std::string couleur){
	if (couleur == "97BF0D")
		return CategorieBus::METRO_BUS;
	else if (couleur == "013888")
		return CategorieBus::LEBUS;
	else if (couleur == "E04503")
		return CategorieBus::EXPRESS;
	else if (couleur == "1A171B" || couleur == "003888")
		return CategorieBus::COUCHE_TARD;
	else{
		//Exception here

	}
}

std::string Ligne::categorieToString(CategorieBus c){
	 switch (c)
	        {
	        case CategorieBus::METRO_BUS:
	        	return "MetroBus";
	        case CategorieBus::LEBUS:
	        	return "LeBus";
	        case CategorieBus::EXPRESS:
	        	return "Express";
	        case CategorieBus::COUCHE_TARD:
	        	return "CoucheTard";
	        }
}

CategorieBus Ligne::getCategorie() const{
	return m_categorie;
}

void Ligne::setCategorie(CategorieBus categorie){
	m_categorie = categorie;
}


unsigned int Ligne::getId() const{
	return m_id;
}
void Ligne::setId(unsigned int id){
	m_id = id;
}
const std::string& Ligne::getNumero() const{
	return m_numero;
}
void Ligne::setNumero(const std::string& numero){
	m_numero = numero;
}
const std::vector<Voyage*>& Ligne::getVoyages() const{
	return m_voyages;
}
void Ligne::setVoyages(const std::vector<Voyage*>& voyages){
	m_voyages = voyages;
}

const std::string& Ligne::getDescription() const{
	return m_description;
}
void Ligne::setDescription(const std::string& description){
	m_description = description;
}

void Ligne::addVoyage(Voyage* ptr_voyage){
	m_voyages.push_back(ptr_voyage);
}

//std::pair<std::string, std::string> Ligne::getDestinations() const{
//	std::vector<std::string> resultat = split(m_description, '-');
//	try{
//		return std::pair<std::string, std::string> (resultat[0],resultat[1]);
//	}
//	catch(const std::out_of_range& e){
//		return std::pair<std::string, std::string> ("","");
//	}
//}

std::pair<std::string, std::string> Ligne::getDestinations() const{
	std::vector<std::string> resultat = split(m_description, '-');
	try{
		return std::pair<std::string, std::string> (resultat[0],resultat[1]);
	}
	catch(const std::out_of_range& e){
		return std::pair<std::string, std::string> (resultat[0],"");
	}
}

std::ostream& operator <<(std::ostream& f, const Ligne& p_ligne){
	f << p_ligne.categorieToString(p_ligne.m_categorie) << " " << p_ligne.m_numero << " : "
			<< p_ligne.m_description;
	return f;
}
