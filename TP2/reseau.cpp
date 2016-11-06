#include <set>
#include "reseau.h"
#include <algorithm>

//
// Created by etienned on 10/31/16.
//


/** \brief Constructeur de la classe Reseau.
 *
 * un objet est créer et mémorisé.
 *
 */
Reseau::Reseau(){
}

/**
 * \brief Ajouter un nouveau sommet au graphe.
 *
 * \param numero: numero du sommet.
 *
 * \exception logic_error : lorsque le sommet existe déjà dans le graphe
 */
void Reseau::ajouterSommet(unsigned int numero) throw (std::logic_error){
    try {
        liste_arcs temporaire;
        m_sommets.insert({numero, temporaire});
    }
    catch (std::logic_error e){
        throw (e);
    }
}

/**
 * \brief Enleve un sommet du graphe.
 *
 * \param  numero: numero du sommet.
 *
 * \exception logic_error : lorsque le sommet n'est pas dans le graphe.
 */
void Reseau::enleverSommet(unsigned int numero) throw (std::logic_error){

    try {
        m_sommets.erase(numero);
    }
    catch (std::logic_error e){
        throw (e);
    }
}

/**
 * \brief Ajouter un arc au graphe.
 *
 * \param numOrigine: numero du sommet d'origine.
 * \param numDest: numero du sommet de la destination.
 * \param cout: le coût de l'arc.
 * \param type: le type d'arc (traversé par un bus ou parcour à pied).
 *
 * \exception logic_error: lorsque l'arc existe ou qu'un sommet n'existe pas
 */
void Reseau::ajouterArc(unsigned int numOrigine, unsigned int numDest,
                        unsigned int cout, unsigned int type) throw (std::logic_error){
    try {
        m_sommets[numOrigine].insert({numDest, std::pair<unsigned int, unsigned int>(cout, type)});
    }
    catch (std::logic_error e){
        throw (e);
    }
}

/**
 * \brief Supprimer un arc au graphe.
 *
 * \param numOrigine: numero du sommet d'origine.
 * \param numDest: numero du sommet de la destination.
 *
 * \exception logic_error: lorsque l'arc n'est pas dans le graphe.
 */
void Reseau::enleverArc(unsigned int numOrigine, unsigned int numDest) throw (std::logic_error){
    try {
        m_sommets[numOrigine].erase(numDest);
    }
    catch (std::logic_error e){
        throw (e);
    }
}

/**
 * \brief Mise à jour du coût d'un arc.
 *
 * \param numOrigine: numero du sommet d'origine.
 * \param numDest: numero du sommet de la destination.
 * \param cout: le nouveau coût de l'arc.
 *
 * \exception logic_error: lorsque l'arc n'est pas dans le graphe.
 */
void Reseau::majCoutArc(unsigned int numOrigine, unsigned int numDest, unsigned int cout) throw (std::logic_error){
    try {
        m_sommets[numOrigine][numDest].first = cout;
    }
    catch (std::logic_error e){
        throw (e);
    }
}

/**
 * \brief Le nombre de sommets.
 * \return le nombres de sommets.
 */
int Reseau::nombreSommets() const{
    return m_sommets.size();
}

/**
 * \brief Le nombre d'arc.
 * \return le nombres d'arc.
 */
int Reseau::nombreArcs() const{
    int nbArcs = 0;
    for ( auto it = m_sommets.begin(); it != m_sommets.end(); ++it ){
        nbArcs += it->second.size();
    }
}

/**
 * \brief Vérifier si un graphe est vide.
 * \return vrai si vide.
 */
bool Reseau::estVide() const{
    return m_sommets.empty();
}

/**
 * \brief Vérifie si un sommet existe dans le graphe.
 *
 * \param numero: numero du sommet.
 *
 * \return vrai si le sommet existe.
 */
bool Reseau::sommetExiste(unsigned int numero) const{
    return (m_sommets.find(numero) != m_sommets.end());
}

/**
 * \brief Vérifie si un arc existe dan le graphe.
 *
 * \param numOrigine: numéro d'origine de l'arc.
 * \param numDest: numéro de la destination de l'arc.
 *
 * \return vrai si l'arc existe.
 */
bool Reseau::arcExiste(unsigned int numOrigine, unsigned int numDest) const throw (std::logic_error){
    try {
        return(m_sommets.at(numOrigine).count(numDest) != 0);
    }
    catch (std::logic_error e){
        throw (e);
    }
}

/**
 * \brief avoir le coût d'un arc.
 *
 * \param numOrigine: le numéro d'origine de l'arc.
 * \param numDest: le numéro de la destination de l'arc.
 *
 * \exception logic_error: lorsque l'arc n'existe pas.
 *
 * \return le coût de l'arc.
 */
int Reseau::getCoutArc(unsigned int numOrigine, unsigned int numDestination) const throw (std::logic_error){
    try {
        return(m_sommets.at(numOrigine).at(numDestination).first);
    }
    catch (std::logic_error e){
        throw (e);
    }
}

/**
 * \brief Retourne le type d'un arc.
 *
 * \param numOrigine: le numéro d'origine de l'arc.
 * \param numDest: le numéro de la destination de l'arc.
 *
 * \exception logic_error: lorsque l'arc n'existe pas.
 *
 * \return le type de l'arc.
 */
int Reseau::getTypeArc(unsigned int numOrigine, unsigned int numDestination) const throw (std::logic_error){
    try {
        return(m_sommets.at(numOrigine).at(numDestination).second);
    }
    catch (std::logic_error e){
        throw (e);
    }
}

/**
 * \brief algorithmes de Dijkstra.
 *
 * \param numOrigine: le numéro d'origine de l'arc.
 * \param numDest: le numéro de la destination de l'arc.
 *\param vector chemin: vecteur de sommet
 * \exception logic_error: lorsque le sommet n'existe pas.
 *
 * \return sommets.
 */
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
            chemin.insert(chemin.begin(),it.second);
            it = information.at(predeceseur);
        }
        return information[numDest].first;

    }
    catch (std::logic_error e){
        throw (e);
    }
}

/**
 * \brief algorithmes de bellmanford.
 *
 * \param numOrigine: le numéro d'origine de l'arc.
 * \param numDest: le numéro de la destination de l'arc.
 *\param vector chemin: vecteur de sommet
 * \exception logic_error: lorsque le sommet n'existe pas.
 *
 * \return sommets.
 */
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
        chemin.insert(chemin.begin(),it.second);
        it = information.at(predeceseur);
    }
    return information[numDest].first;
}


/**
 * \brief obtenir la composantes fortements connexes
 *
 *\param vector composantes
 *
 * \return la taille de composante.
 */

int Reseau::getComposantesFortementConnexes(std::vector<std::vector<unsigned int> > & composantes) const{
    Reseau sommet_inverse;

    std::set<unsigned int> dejaVisite;
    std::vector<unsigned int> pile;
    std::vector<unsigned int> composanteTemporaire;

    for (auto itSommet = m_sommets.begin(); itSommet != m_sommets.end(); ++itSommet) {
        sommet_inverse.ajouterSommet(itSommet->first);
        visite(itSommet->first, dejaVisite, pile);
        for (auto itArc = itSommet->second.begin(); itArc != itSommet->second.end(); ++itArc) {
            // inverse sommet
            sommet_inverse.ajouterSommet(itArc->first);
            sommet_inverse.ajouterArc(itArc->first, itSommet->first, INFINI);
        }
    }

    dejaVisite.clear();
    std::vector<unsigned int> vide;
    for (auto itSommet = pile.begin(); itSommet != pile.end(); ++itSommet) {
        assigne((*itSommet), sommet_inverse.m_sommets, dejaVisite, composanteTemporaire);
        if(composanteTemporaire != vide){
            composantes.push_back(composanteTemporaire);
        }
        composanteTemporaire = vide;
    }
    return composantes.size();
}

/**
 * \brief vérifie si la compoposante est fortements connexes
 *
 *\param vector composantes
 *
 * \return return vrai si la composante est fortement connexe.
 */
bool Reseau::estFortementConnexe() const{
    std::vector<std::vector<unsigned int> > composantes;
    return (this->getComposantesFortementConnexes(composantes) == 1);
}


void Reseau::visite(unsigned int sommet, std::set<unsigned int> &dejaVisite, std::vector<unsigned int> &pile) const{
    if (dejaVisite.find(sommet) == dejaVisite.end()){
        dejaVisite.insert(sommet);
        liste_arcs arcsSuivant = m_sommets.find(sommet)->second;
        for(auto it = arcsSuivant.begin(); it != arcsSuivant.end(); ++it){
            visite(it->first, dejaVisite, pile);
        }
        pile.push_back(sommet);
    }
}

void Reseau::assigne(unsigned int sommet, std::unordered_map< unsigned int, liste_arcs> grapheInverse,
                     std::set<unsigned int> &dejaVisite, std::vector<unsigned int> &composanteTemporaire) const{
    if (dejaVisite.find(sommet) == dejaVisite.end()){
        dejaVisite.insert(sommet);
        composanteTemporaire.push_back(sommet);
        liste_arcs arcsSuivant = grapheInverse.find(sommet)->second;
        for(auto it = arcsSuivant.begin(); it != arcsSuivant.end(); ++it){
            assigne(it->first, grapheInverse, dejaVisite, composanteTemporaire);
        }
    }

}



