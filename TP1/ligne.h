//
// Created by prtos on 29/04/16.
//

#ifndef RTC_LIGNE_H
#define RTC_LIGNE_H

#include <string>
#include <vector>
#include "voyage.h"
#include "station.h"
#include "auxiliaires.h"

/*!
 * \enum CategorieBus
 * \brief Représente les différentes catégories de bus
 *
 */
enum class CategorieBus {METRO_BUS, LEBUS, EXPRESS, COUCHE_TARD};

class Voyage;


/*!
 * \class Ligne
 * \brief Cette classe représente une ligne d'autobus du réseau de transport contenues dans le fichier routes.txt
 * Par exemple, la "800", la "801" et la "13A" sont toutes des lignes différentes.
 * \note Sa déclaration nécessite la déclaration partielle des classe Voyage, en raison de référence circulaire avec cette classe.
 */
class Ligne {

private:
    unsigned int m_id;// parametre m_id
    std::string m_numero;//paramètre m_numéto
    std::string m_description;// parametre m_description
    CategorieBus m_categorie;//paramètre m_catégorie
    std::vector<Voyage*> m_voyages;//vecteur m_voyages

public:
	Ligne(const std::vector<std::string>& ligne_gtfs);
	static CategorieBus couleurToCategorie(std::string couleur);
	static std::string categorieToString(CategorieBus c);
	CategorieBus getCategorie() const;//méthode qui permet de récupérer la catégorie du bus
	void setCategorie(CategorieBus categorie);//méthode qui permet de fixer la catégorie
	std::pair<std::string, std::string> getDestinations() const; //méthode qui permet de récupérer la destination
	unsigned int getId() const;//méthode qui permet de récupérer l'identifiant
	void setId(unsigned int id);//méthode qui permet de fixer l'identifiant
	const std::string& getNumero() const;//méthode qui permet de récupérer le numéro
	void setNumero(const std::string& numero);//méthode qui permet de fixer le numéro
	const std::vector<Voyage*>& getVoyages() const;
	void setVoyages(const std::vector<Voyage*>& voyages);//méthode qui permet de fixer m_voyages
	void addVoyage(Voyage* ptr_voyage);//méthode qui permet de remplir un vecteur (m_voyages)
	const std::string& getDescription() const;//méthode qui permet de récupérer la description
	void setDescription(const std::string& description);//méthode qui permet de fixer la description
	friend std::ostream& operator <<(std::ostream& f, const Ligne& p_ligne);
};


#endif //RTC_LIGNE_H
