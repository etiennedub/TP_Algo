//
// Created by prtos on 29/04/16.
//

#ifndef RTC_COORDONNEES_H
#define RTC_COORDONNEES_H

#include <stdexcept>
#include <iostream>
#include <sstream>
#include <cmath>

/*!
 * \class Coordonnees
 * \brief Cette classe permet de représenter les coordonnées GPS d'un endroit
 */
class Coordonnees {

public:
	//constructeur de la clase coordonnees
    Coordonnees(double latitude, double longitude);

    double getLatitude() const ;//méthode qui permet de récupérer la latitude

    void setLatitude(double latitude) ;//méthode qui permet de fixer la latitude

    double getLongitude() const ;//méthode qui permet de récupérer la longitude

    void setLongitude(double longitude) ;//méthode qui permet de fixer la longitude

    static bool is_valide_coord(double p_latitude, double p_longitude) ;//fonction qui valide les coordonnées

    double operator- (const Coordonnees & other) const;

    friend std::ostream & operator<<(std::ostream & flux, const Coordonnees & p_coord); //fonction qui affiche les coordonnees

private:
    double m_latitude;//param de la latitude
    double m_longitude;//param de la longétude
};


#endif //RTC_COORDONNEES_H
