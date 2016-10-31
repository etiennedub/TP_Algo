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


