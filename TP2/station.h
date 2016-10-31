//
// Created by prtos on 29/04/16.
//

#ifndef RTC_STATION_H
#define RTC_STATION_H

#include <string>
#include <vector>
#include <iostream>
#include "coordonnees.h"
#include "ligne.h"
#include "voyage.h"

class Voyage;
class Ligne;
class Coordonnees;

/*!
 * \class Station
 * \brief Classe représentant une station. Une station est un emplacement physique où un bus effectue des arrêts.
 * \note Sa déclaration nécessite la déclaration partielle des classe Ligne et Voyage, en raison de références circulaires avec ces classes.
 */
class Station {

private:
    unsigned int m_id;// parametre m_id
    std::string m_nom;// parametre m_nom
    std::string m_description;// parametre m_description
    Coordonnees m_coords;// parametre m_coordonees
    std::vector<Voyage* > m_voyages_passants;// initialisation d'un vecteur

public:
    //constructeur de la classe Station
 	//param un vecteur : ligne d'information présente dans stop.txt
    Station(const std::vector<std::string>& ligne_gtfs);
    friend std::ostream& operator<<(std::ostream& flux, const Station& p_station);
	const Coordonnees& getCoords() const; //méthode qui permet de récupérer les coordonnées
	void setCoords(const Coordonnees& coords);//méthode qui permet de fixer les coordonnées
	const std::string& getDescription() const;//méthode qui permet de récupérer les descriptions
	void setDescription(const std::string& description);//méthode qui permet de fixer la description
	std::vector<Ligne*> getLignesPassantes() const;
	const std::string& getNom() const;//méthode qui permet de récupérer le nom
	void setNom(const std::string& nom);//méthode qui permet de fixer le nom
	unsigned int getId() const;//méthode qui permet de récupérer l'identifiant
	void setId(unsigned int stationId);//méthode qui permet de fixer l'identifiant
	const std::vector<Voyage*> & getVoyagesPassants() const; // méthode qui retourne m_voyages_passants
	void addVoyage(Voyage* ptr_voyage); //méthode qui permet de remplir un vecteur (m_voyaged_passants)
	double distance(const Station& p_station) const;// fonction qui retourne la distance entre deux coordonnees
};


#endif //RTC_STATION_H
