//
// Created by etienned on 11/30/16.
//

#ifndef TP3_FIBO_H
#define TP3_FIBO_H

    /**
     * \class Noeud
     *
     * \brief classe interne représentant un noeud typique de l'arbre
     *
     *  La classe représente un noeud typique
     */
template<typename E, typename A> class Noeud<E, A> {
public:
    /**
     * \brief Constructeur de la classe Noeud
     * \post Un noeud typique est intialisé
     * \param p_id est l'ID de la station
     * \param p_valeur est la distance (utlisé pour le tri)
     */
    Noeud(const A & p_id, const E & p_valeur) :
            m_valeur(p_valeur), m_enfant(nullptr), m_parent(nullptr), m_id(p_id)
            , m_degree(0), m_marked(false), m_suivant(nullptr), m_precedent(nullptr){}
    /**
     * \brief Accesseur de l'ID
     * \return m_id
     */
    A getId() {return m_id;}
    /**
     * \brief Accesseur de la valeur
     * \return m_valeur
     */
    E getValeur(){return m_valeur;}
private:
    friend class Fibo;
    A m_id; /*!< ID de la station */
    E m_valeur; /*!< La donnée dans l'arbre*/
    Noeud * m_suivant; /*!< Pointeur du noeud suivant */
    Noeud * m_precedent; /*!< Pointeur du noeud precedent */
    Noeud * m_enfant; /*!< Pointeur du noeud enfant */
    Noeud * m_parent; /*!< Pointeur du noeud parent */
    int m_degree; /*!< la valeur du degree */
    bool m_marked; /*!< booleen marked */
};

template <typename E, typename A> class Fibo {
public:
    /**
     * \brief Constructeur de la classe Fibo
     * \post Une structure de donnée fibonacci typique est intialisé
     */
    Fibo();
    /**
     * \brief Destructeur de la classe Fibo
     * \post Tous les noeuds créés sont supprimer
     */
    ~Fibo();
    /**
     * \brief Permet d'ajouter un noeud
     * \param p_id est l'ID de la station
     * \param p_valeur est la distance (utlisé pour le tri)
     * \return un pointeur sur l'objet noeud créé
     */
    Noeud * ajouter(A p_id, E p_valeur);
    /**
     * \brief Supprime le noeud minimal
     * \return La valeur du noeud minimal
     */
    E supprimerMin();
    /**
     * \brief Permet de diminuer la veleur d'un noeud existant
     * \param p_noeud est un pointeur sur le noeud à modifier
     * \param p_valeur est la nouvelle valeur du noeud
     * \pre p_valeur > p_noeud->m_valeur
     */
    void diminuer(Noeud * p_noeud, E p_valeur);
private:
    Noeud * m_ptrMin; /*!< Pointeur sur le noeud minimal */

    void supprimerTous(Noeud * p_noeud);
    Noeud * merge(Noeud * a, Noeud * b);
};



#endif //TP3_FIBO_H
