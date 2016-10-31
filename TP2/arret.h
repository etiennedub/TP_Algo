/*!
 * \file arret.h
 * \brief Fichier contenant la classe arret
 * \author Prudencio Tossou
 * \version 0.1
 */

#ifndef RTC_ARRET_H
#define RTC_ARRET_H

#include "auxiliaires.h"


/*!
* \class Arret
* \brief Classe représentant un arret
*
*  Un arret est une composante d'un voyage, c'est une opération spatio-temporelle
*  (ex: la ligne 800 effectue un arrêt à la station du desjardin à 11h32).
*  Il est important de ne confondre la station et l'arret.
*
*/
class Arret {

public:

	 //constructeur de la classe Arret
	 //param un vecteur : ligne d'information présente dans stop_tmes
	Arret(const std::vector<std::string>& ligne_gtfs);

	const Heure& getHeureArrivee() const; //méthode qui permet de récupérer l'heure d'arrivée
	void setHeureArrivee(const Heure& p_heureArrivee);//méthode qui permet de fixer l'heure d'arriver
	const Heure& getHeureDepart() const; //méthode qui permet de récupérer l'heure de départ
	void setHeureDepart(const Heure& p_heureDepart); //méthode qui permet de fixer l'heure de départ
	unsigned int getNumeroSequence() const;//méthode qui permet de récupérer le numéro de station
	void setNumeroSequence(unsigned int p_numeroSequence);//méthode qui permet de fixer le numéro de séquence
	unsigned int getStationId() const;//méthode qui permet de récupérer l'identifiandt de la station
	void setStationId(unsigned int stationId);//méthode qui permet de fixer l'identifiandt de la station
	std::string getVoyageId() const;//méthode qui permet de récupérer m_voyage_id
	void setVoyageId(const std::string& voyageId);//méthode qui permet de fixer m_voyage_id

	bool operator< (const Arret & p_other) const;//fonction booléen qui compare les numéros de sequence, retourne True si plus petit
	bool operator> (const Arret & p_other) const;//fonction booléen qui compare les numéros de sequence, retourne True si plus grand

	friend std::ostream & operator<<(std::ostream & flux, const Arret & p_arret);


private:
	unsigned int m_station_id;
	Heure m_heure_arrivee; //paramètre heure d'arrivée
	Heure m_heure_depart;//paramètre heure de départ
	unsigned int m_numero_sequence;//paramètre numéro de sequence
	std::string m_voyage_id;//paramètre identifiant voyage
};


#endif //RTC_ARRET_H
