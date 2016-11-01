//
// Created by prtos on 29/04/16.
//

#include <iostream>
#include <vector>
#include <unordered_map>

#ifndef Reseau__H
#define Reseau__H

#define INFINI 999999
#define DEFAULT_TYPE 0


typedef std::unordered_map<unsigned int, std::pair<unsigned int, unsigned int> > liste_arcs;
typedef std::unordered_multimap< unsigned int, liste_arcs > liste_sommets;

/*!
 * \class Reseau
 * \brief Classe réprésentant un graphe orienté valué. Les sommets du graphe sont tous identifiés par des nombres entiers positifs distincts.
 * Les entre les sommets arcs sont tous identifiés par poids positif ou nul, et un type qui est aussi un entier positif.
 *
 */
class Reseau
{
public:

	Reseau();


	void ajouterSommet(unsigned int numero) throw (std::logic_error);
	void enleverSommet(unsigned int numero) throw (std::logic_error);
	void ajouterArc(unsigned int numOrigine, unsigned int numDest, unsigned int cout, unsigned int type=DEFAULT_TYPE)
				throw (std::logic_error);
	void enleverArc(unsigned int numOrigine, unsigned int numDest) throw (std::logic_error);
	void majCoutArc(unsigned int numOrigine, unsigned int numDest, unsigned int cout) throw (std::logic_error);

	int nombreSommets() const;
	int nombreArcs() const;
	bool estVide() const;

	bool sommetExiste(unsigned int numero) const;
	bool arcExiste(unsigned int numOrigine, unsigned int numDest) const throw (std::logic_error);
	int getCoutArc(unsigned int numOrigine, unsigned int numDestination) const throw (std::logic_error);
	int getTypeArc(unsigned int numOrigine, unsigned int numDestination) const throw (std::logic_error);

	int dijkstra(unsigned int numOrigine, unsigned int numDest, std::vector<unsigned int> & chemin)
				throw (std::logic_error);
	int bellmanFord(unsigned int numOrigine, unsigned int numDest, std::vector<unsigned int> & chemin)
				throw (std::logic_error);
	bool estFortementConnexe() const;
    // égal au nombre de composantes fortement connexe
	int getComposantesFortementConnexes(std::vector<std::vector<unsigned int> > & composantes) const;

private:
    // Vector des sommets qui contient les arcs sortant
    std::unordered_map< unsigned int, liste_arcs> m_sommets;

};

#endif
