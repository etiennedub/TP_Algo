/*
 * fibo.hpp
 *
 *  Created on: 2016-11-30
 *      Author: etudiant
 */

#ifndef FIBO_HPP_
#define FIBO_HPP_


template <typename E, typename A> class Fibo;

template <typename E, typename A> struct Noeud {
private:
    A m_id; /*!< ID de la station */
    E m_valeur; /*!< La donnée dans l'arbre*/
    Noeud<E,A>* m_suivant; /*!< Pointeur du noeud suivant */
    Noeud<E,A>* m_precedent; /*!< Pointeur du noeud precedent */
    Noeud<E,A>* m_enfant; /*!< Pointeur du noeud enfant */
    Noeud<E,A>* m_parent; /*!< Pointeur du noeud parent */
    int m_degree; /*!< la valeur du degree */
    bool m_marked; /*!< booleen marked */
public:
    friend class Fibo<E,A>;
	Noeud<E,A>* getPrecedent() {return m_precedent;}
	Noeud<E,A>* getSuivant() {return m_suivant;}
	Noeud<E,A>* getEnfant() {return m_enfant;}
	Noeud<E,A>* getParent() {return m_parent;}
	E getValue() {return m_valeur;}
	A getKey() {return m_id;}
	bool isMarked() {return m_marked;}

	bool hasChildren() {return m_enfant;}
	bool hasParent() {return m_parent;}
};

template <typename E, typename A> class Fibo {

protected:
	Noeud<E,A>* monceau;
public:
    /**
	 * \brief Constructeur de la classe Fibo
	 * \post Une structure de donnée fibonacci typique est intialisé
	 */
    Fibo()
	{
    	m_ptrMin = nullptr;
	}

    /**
     * \brief Destructeur de la classe Fibo
     * \post Tous les noeuds créés sont supprimer
     */
   ~Fibo()
   {
	   if (m_ptrMin != nullptr){
	           supprimerTous(m_ptrMin);
	       }
   }

   /**
	 * \brief Permet d'ajouter un noeud
	 * \param p_id est l'ID de la station
	 * \param p_valeur est la distance (utlisé pour le tri)
	 * \return un pointeur sur l'objet noeud créé
	 */
    Noeud<E,A> * ajouter(A p_id, E p_valeur)
    {
    	Noeud<E,A>* ptr = new Noeud(p_id, p_valeur);
    	m_ptrMin = merge(m_ptrMin, ptr);
    	return ptr;
    }

    /**
	 * \brief Supprime le noeud minimal
	 * \return La valeur du noeud minimal
	 */
    E supprimerMin()
    {

    }

    /**
	 * \brief Permet de diminuer la veleur d'un noeud existant
     * \param p_noeud est un pointeur sur le noeud à modifier
	 * \param p_valeur est la nouvelle valeur du noeud
	 * \pre p_valeur > p_noeud->m_valeur
	 */
   void diminuer(Noeud * p_noeud, E p_valeur)
   {

   }
private:
   Noeud<E,A>* m_ptrMin; /*!< Pointeur sur le noeud minimal */

   void supprimerTous(Noeud * p_noeud)
   {
	    if( p_noeud != nullptr){
	        Noeud<E,A>* a = p_noeud;
	        do {
	            Noeud<E,A>* b = a;
	            a = a->m_suivant;
	            supprimerTous(b->m_enfant);
	            delete b;
	        } while(a != p_noeud);
	    }
   }

   Noeud<E,A>* merge(Noeud<E,A> * a, Noeud<E,A> * b)
   {
	    if( a == nullptr ){
	        return b;
	    }
	    if( b == nullptr ){
	        return a;
	    }
	    if( a->m_valeur > b->m_valeur){ // Inverse a et b
	        Noeud * tempoPtr = a;
	        a = b;
	        b = tempoPtr;
	    }

	    Noeud<E,A> * aSuivant = a->m_suivant;
	    Noeud<E,A> * bPrecedent = b->m_precedent;
	    a->m_suivant = b;
	    b->m_precedent = a;
	    aSuivant->m_precedent = bPrecedent;
	    bPrecedent->m_suivant = aSuivant;

	    return a;
   }
};






#endif /* FIBO_HPP_ */
