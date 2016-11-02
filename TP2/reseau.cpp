#include <set>
#include "reseau.h"

//
// Created by etienned on 10/31/16.
//

Reseau::Reseau(){
}

void Reseau::ajouterSommet(unsigned int numero) throw (std::logic_error){
    try {
        liste_arcs temporaire;
        m_sommets.insert({numero, temporaire});
    }
    catch (std::logic_error e){
        throw (e);
    }
}

void Reseau::enleverSommet(unsigned int numero) throw (std::logic_error){

    try {
        m_sommets.erase(numero);
    }
    catch (std::logic_error e){
        throw (e);
    }
}

void Reseau::ajouterArc(unsigned int numOrigine, unsigned int numDest,
                        unsigned int cout, unsigned int type) throw (std::logic_error){
    try {
        m_sommets[numOrigine].insert({numDest, std::pair<unsigned int, unsigned int>(cout, type)});
    }
    catch (std::logic_error e){
        throw (e);
    }
}

void Reseau::enleverArc(unsigned int numOrigine, unsigned int numDest) throw (std::logic_error){
    try {
        m_sommets[numOrigine].erase(numDest);
    }
    catch (std::logic_error e){
        throw (e);
    }
}

void Reseau::majCoutArc(unsigned int numOrigine, unsigned int numDest, unsigned int cout) throw (std::logic_error){
    try {
        m_sommets[numOrigine][numDest].first = cout;
    }
    catch (std::logic_error e){
        throw (e);
    }
}

int Reseau::nombreSommets() const{
    return m_sommets.size();
}

int Reseau::nombreArcs() const{
    int nbArcs = 0;
    for ( auto it = m_sommets.begin(); it != m_sommets.end(); ++it ){
        nbArcs += it->second.size();
    }
}

bool Reseau::estVide() const{
    return m_sommets.empty();
}

bool Reseau::sommetExiste(unsigned int numero) const{
    return (m_sommets.count(numero) != 0);
}

bool Reseau::arcExiste(unsigned int numOrigine, unsigned int numDest) const throw (std::logic_error){
    try {
        return(m_sommets.at(numOrigine).count(numDest) != 0);
    }
    catch (std::logic_error e){
        throw (e);
    }
}

int Reseau::getCoutArc(unsigned int numOrigine, unsigned int numDestination) const throw (std::logic_error){
    try {
        return(m_sommets.at(numOrigine).at(numDestination).first);
    }
    catch (std::logic_error e){
        throw (e);
    }
}

int Reseau::getTypeArc(unsigned int numOrigine, unsigned int numDestination) const throw (std::logic_error){
    try {
        return(m_sommets.at(numOrigine).at(numDestination).second);
    }
    catch (std::logic_error e){
        throw (e);
    }
}

int Reseau::dijkstra(unsigned int numOrigine, unsigned int numDest, std::vector<unsigned int> & chemin)
                        throw (std::logic_error){
    try {
        //                                          Distance_min, predeceseur
        std::unordered_map<unsigned int, std::pair<unsigned int, unsigned int>> information;
        for (auto it = m_sommets.begin(); it != m_sommets.end(); ++it ){
            information.insert({it->first,std::pair<unsigned  int, unsigned int>(INFINI, INFINI)});
        }
        std::set<unsigned int> visite;
        visite.insert(numOrigine);
        information[numOrigine] =  std::pair<unsigned int, unsigned int>(0, INFINI);
        while (visite.size() > 0) {
            //                                                  ID,     Distance
            std::pair<unsigned int, unsigned int> distance_min (INFINI,INFINI);
            for (auto it = visite.begin(); it != visite.end(); ++it ){
                if (information[(*it)].first < distance_min.second){
                    distance_min = std::pair<unsigned int, unsigned int> ((*it), information[(*it)].first);
                }
            }
            if (distance_min.first == numDest) break;
            // Minimun trouve
            visite.erase(distance_min.first);
            for (auto it = m_sommets[distance_min.first].begin(); it != m_sommets[distance_min.first].end(); ++it){
                visite.insert(it->first);
                int sommet_from = distance_min.first;
                int sommet_to_do = it->first;
                int ancienne_distance = information[it->first].first;
                int nouvelle_distance = it->second.first;
                if (information[it->first].first > distance_min.second + it->second.first) {
                    information[it->first].first =  distance_min.second + it->second.first;
                    information[it->first].second = distance_min.first;
                }
            }
        }
        auto it = information.at(numDest);
        while (it != information.at(numOrigine)){
            int predeceseur = it.second;
            chemin.push_back(it.second);
            it = information.at(predeceseur);
        }
        return information[numDest].first;

    }
    catch (std::logic_error e){
        throw (e);
    }
}

int Reseau::bellmanFord(unsigned int numOrigine, unsigned int numDest, std::vector<unsigned int> & chemin)
throw (std::logic_error){
    bool relachement;
    //                  ID,                     Distance,   Predeceseur
    std::unordered_map<unsigned int, std::pair<unsigned int, unsigned int>> information;
    for (auto it = m_sommets.begin(); it != m_sommets.end(); ++it ){
        information.insert({it->first,std::pair<unsigned  int, unsigned int>(INFINI, INFINI)});
    }
    information[numOrigine] =  std::pair<unsigned int, unsigned int>(0, INFINI);

    // NbSommet - 1 fois
    for (int i = 0; i < m_sommets.size() - 1; i++){
        relachement = false;
        // NbArc
        for (auto itSommet = m_sommets.begin(); itSommet != m_sommets.end(); ++itSommet ){
            for (auto itArc = itSommet->second.begin(); itArc != itSommet->second.end(); ++itArc ){
                unsigned int destination = itArc->first;
                unsigned int source = itSommet->first;
                unsigned int coutInit = information[destination].first;
                unsigned int coutNouveau = information[source].first + itArc->second.first;
                if (coutNouveau < coutInit){
                    relachement = true;
                    // Cout
                    information[destination].first = coutNouveau;
                    // Predeceseur
                    information[destination].second = source;
                }

            }
        }
        if (relachement == false) break;
    }
    auto it = information.at(numDest);
    while (it != information.at(numOrigine)){
        int predeceseur = it.second;
        chemin.push_back(it.second);
        it = information.at(predeceseur);
    }
    return information[numDest].first;
}

int Reseau::getComposantesFortementConnexes(std::vector<std::vector<unsigned int> > & composantes) const{
    Reseau sommet_inverse;
    std::vector<unsigned int> pile;
    std::set<unsigned int> nonVisite;
    for (auto itSommet = m_sommets.begin(); itSommet != m_sommets.end(); ++itSommet ) {
        nonVisite.insert(itSommet->first);
        for (auto itArc = itSommet->second.begin(); itArc != itSommet->second.end(); ++itArc) {
            // inverse sommet
            sommet_inverse.ajouterSommet(itArc->first);
            sommet_inverse.ajouterArc(itArc->first, itSommet->first, INFINI);


        }
    }

//    pile.push_back(m_sommets.begin()->first);
//    auto itSommetPile = pile.begin(); // debut de la pile
//    while(nonVisite.size() != 0) {
//
//        while (itSommetPile != pile.end()) {
//            const unsigned int sommetCourant = (*itSommetPile);
//            nonVisite.insert(sommetCourant);
//            for (auto itArc = m_sommets.find(sommetCourant)->second.begin();
//                 itArc != m_sommets.find(sommetCourant)->second.end(); ++itArc) {
//                unsigned int destination = itArc->first;
//                // O(log n) contrairement vector O(n)
//                if (nonVisite.find(destination) != nonVisite.end()) {
//                    pile.push_back(destination);
//                }
//            }
//            itSommetPile++;
//        }
//    }
//    return 1;
}

bool Reseau::estFortementConnexe() const{
    std::vector<std::vector<unsigned int> > composantes;
    return (this->getComposantesFortementConnexes(composantes) == 1);
}