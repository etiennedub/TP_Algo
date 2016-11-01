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
//    try {
//        //                                          Distance_min, predeceseur
//        std::unordered_map<unsigned int, std::pair<unsigned int, unsigned int>> information;
//        std::vector<unsigned int> visite;
//        visite.push_back(numOrigine);
//        information.insert({numOrigine, std::pair<unsigned int, unsigned int>(0, INFINI)});
//        while (visite.size() > 0){
//            //                                                  ID,     Distance
//            std::pair<unsigned int, unsigned int> distance_min (INFINI,INFINI);
//            for (auto it = information.begin(); it != information.end(); ++it ){
//                if (it->second.first < distance_min.second){
//                    distance_min = std::pair<unsigned int, unsigned int> (it->second.second, it->second.first);
//                }
//            }
//        }
//
//    }
//    catch (std::logic_error e){
//        throw (e);
//    }
}