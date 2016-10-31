//
// Created by prtos on 29/04/16.
//

#ifndef RTC_VOYAGE_H
#define RTC_VOYAGE_H

#include <string>
#include <algorithm>
#include "arret.h"
#include "ligne.h"
#include "station.h"
#include "auxiliaires.h"


class Ligne;
class Station;

/*!
 * \class Voyage
 * \brief Classe permettant de décrire un voyage
 * \note Sa déclaration nécessite la déclaration partielle des classe Ligne et Station, en raison de références circulaires avec ces classes.
 */
class Voyage {

public:
	//constructeur de la class Voyage
	Voyage(const std::vector<std::string>& ligne_gtfs, Ligne* p_ligne);
	Arret & arretDeLaStation(unsigned int p_num_station); // A FAIRE !!!!!
	std::vector<Arret> getArrets() const; //méthode qui permet de récupérer le vecteur
	const std::string& getDestination() const;//méthode qui permet de récupérer la destination
	void setDestination(const std::string& p_destination);//méthode qui permet de fixer la destination
	std::string getId() const;//méthode qui permet de récupérer l'identifiant
	void setId(std::string p_id);//méthode qui permet de fixer l'identifiant
	Ligne* getLigne() const; // méthode qui permet de récupérer le parametre m_ligne
	void setLigne(Ligne* p_ligne);//méthode qui permet de fixer les paramètre de ligne
	std::string getServiceId() const;//méthode qui permet de récupérer m_service_id
	void setServiceId(std::string p_service_id);
	Heure getHeureDepart() const;//méthode qui permet de récupérer heure de départ
	Heure getHeureFin() const;//méthode qui permet de récupérer l'heure d'arriver
	void setArrets(std::vector<Arret>& resultat);
	bool operator< (const Voyage & p_other) const;//fonction booléen qui compare Voyage, retourne True si plus petit
	bool operator> (const Voyage & p_other) const;//fonction booléen qui compare Voyage, retourne True si plus grand
	friend std::ostream & operator<<(std::ostream & flux, const Voyage & p_voyage); //méthode d'affichage

private:
	std::string m_id; // paramètre m_id
	Ligne* m_ligne;// paramètre m_ligne
	std::string m_service_id;// paramètre m_service_id
	std::string m_destination;//paramètre m_destination
	std::vector<Arret> m_arrets; //vecteur m_arrets
};


#endif //RTC_VOYAGE_H
