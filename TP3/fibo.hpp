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
    int m_degree; /*!< le nombre d'enfant */
    bool m_marque; /*!< boolean marqué */
public:
    friend class Fibo<E,A>;
	Noeud<E,A>* getPrecedent() {return m_precedent;}
	Noeud<E,A>* getSuivant() {return m_suivant;}
	Noeud<E,A>* getEnfant() {return m_enfant;}
	Noeud<E,A>* getParent() {return m_parent;}
	E getValue() {return m_valeur;}
	A getKey() {return m_id;}
	bool isMarked() {return m_marque;}

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
    	monceau = nullptr;
	}

    /**
     * \brief Destructeur de la classe Fibo
     * \post Tous les noeuds créés sont supprimer
     */
   ~Fibo()
   {
	   if (monceau != nullptr){
	           supprimerTous(monceau);
	       }
   }

   /**
    * \brief Permet de savoir si le monceau est vide
    * \return un bool dit dit si le monceau est vide
    */
   bool estVide()
   {
	   return monceau == nullptr;
   }

   /**
	 * \brief Permet d'ajouter un noeud
	 * \param p_id est l'ID de la station
	 * \param p_valeur est la distance (utlisé pour le tri)
	 * \return un pointeur sur l'objet noeud créé
	 */
    Noeud<E,A> * ajouter(A p_id, E p_valeur)
    {
    	Noeud<E,A>* ptr = new Noeud<E,A>;
		ptr->m_precedent = ptr;
		ptr->m_suivant = ptr;
		ptr->m_enfant = nullptr;
		ptr->m_parent = nullptr;
		ptr->m_degree = 0;
		ptr->m_marque = false;
		ptr->m_id = p_id;
		ptr->m_valeur = p_valeur;
    	monceau = merge(monceau, ptr);
    	return ptr;
    }

    /**
	 * \brief Supprime le noeud minimal
	 * \return La valeur du noeud minimal
	 */
    E supprimerMin()
    {
    	Noeud<E,A>* n = monceau;
    	monceau = extraireMin(monceau);
    	E val = n->m_valeur;
    	delete n;
    	return val;
    }

	Noeud<E,A> * getMin()
	{
		return monceau;
	};

    /**
	 * \brief Permet de diminuer la veleur d'un noeud existant
     * \param p_noeud est un pointeur sur le noeud à modifier
	 * \param p_valeur est la nouvelle valeur du noeud
	 * \pre p_valeur > p_noeud->m_valeur
	 */
   void diminuer(Noeud<E,A>* p_noeud, E p_valeur)
   {
	   if(p_noeud->m_valeur < p_valeur)
	   {
		   return;
	   }

	   p_noeud->m_valeur = p_valeur;
       if(p_noeud->m_parent == nullptr) return;

	   if(p_noeud->m_valeur < p_noeud->m_parent->m_valeur)
	   {
		   monceau = cut(monceau,p_noeud);
		   Noeud<E,A>* parent = p_noeud->m_parent;
		   p_noeud->m_parent = nullptr;
		   while(parent != nullptr && parent->m_marque)
		   {
			   monceau = cut(monceau,parent);
			   p_noeud = parent;
			   parent = p_noeud->m_parent;
			   p_noeud->m_parent = nullptr;
		   }

		   if(parent != nullptr && parent->m_parent != nullptr)
		   {
			   parent->m_marque = true;
		   }
	   }
   }

private:

   void supprimerTous(Noeud<E,A>* p_noeud)
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
			Noeud<E,A>* tempoPtr = a;
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

   void ajouterEnfant(Noeud<E,A>* parent, Noeud<E,A>* enfant)
   {
	   enfant->m_precedent=enfant->m_suivant=enfant;
	   enfant->m_parent=parent;
	   parent->m_degree++;
	   parent->m_enfant = merge(parent->m_enfant, enfant);
   }

   void retirerMarquesEtParente(Noeud<E,A>* n)
   {
	   if(n == nullptr)
	   {
		   return;
	   }
	   else
	   {
		   Noeud<E,A>* temp = n;
		   do{
			   temp->m_marque = false;
			   temp->m_parent = nullptr;
			   temp = temp->m_suivant;
		   }while(temp != n);
	   }
   }

   Noeud<E,A>* extraireMin(Noeud<E,A>* n)
   {
	  retirerMarquesEtParente(n->m_enfant);

	  if(n->m_suivant == n)
	  {
		  n = n->m_enfant;
	  }
	  else{
		  n->m_suivant->m_precedent = n->m_precedent;
		  n->m_precedent->m_suivant = n->m_suivant;
		  n = merge(n->m_suivant,n->m_enfant);
	  }

	  if(n == nullptr)
	  {
		  return n;
	  }

	  Noeud<E,A>* trees[64]={nullptr};
	  while(true)
	  {
		  if(trees[n->m_degree]!=nullptr)
		  {
			  Noeud<E,A>* t=trees[n->m_degree];
			  if(t==n)break;
			  trees[n->m_degree]=nullptr;
			  if(n->m_valeur<t->m_valeur)
			  {
				  t->m_precedent->m_suivant=t->m_suivant;
				  t->m_suivant->m_precedent=t->m_precedent;
				  ajouterEnfant(n,t);
			  }
			  else
			  {
				  t->m_precedent->m_suivant=t->m_suivant;
				  t->m_suivant->m_precedent=t->m_precedent;
				  if(n->m_suivant==n)
				  {
					  t->m_suivant=t->m_precedent=t;
					  ajouterEnfant(t,n);
					  n=t;
				  }
				  else
				  {
					  n->m_precedent->m_suivant=t;
					  n->m_suivant->m_precedent=t;
					  t->m_suivant=n->m_suivant;
					  t->m_precedent=n->m_precedent;
					  ajouterEnfant(t,n);
					  n=t;
				  }
			  }
			  continue;
		  }
		  else
		  {
			  trees[n->m_degree]=n;
		  }
		  n=n->m_suivant;
	  }
	  Noeud<E,A>* min=n;
	  do
	  {
		  if(n->m_valeur<min->m_valeur)
		  {
			  min=n;
		  }
		  n=n->m_suivant;
	  } while(n!=n);

	  return min;
   }

   Noeud<E,A>* cut(Noeud<E,A>* monceau, Noeud<E,A>* n)
   {
	   if(n->m_suivant==n)
	   {
		   n->m_parent->m_enfant = nullptr;
	   }
	   else
	   {
		   n->m_suivant->m_precedent = n->m_precedent;
		   n->m_precedent->m_suivant = n->m_suivant;
		   n->m_parent->m_enfant = n->m_suivant;
	   }

	   n->m_suivant = n->m_precedent = n;
	   n->m_marque = false;
	   return merge(monceau,n);
   }
};






#endif /* FIBO_HPP_ */
