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
	E getValue() {return m_valeur;}
	A getKey() {return m_id;}
};

template <typename E, typename A> class Fibo {
public:
    /**
	 * \brief Constructeur de la classe Fibo
	 * \post Une structure de donnée fibonacci typique est intialisé
	 */
    Fibo()
	{
    	m_min = nullptr;
    	m_size = 0;
	}

    /**
     * \brief Destructeur de la classe Fibo
     * \post Tous les noeuds créés sont supprimer
     */
   ~Fibo()
   {
	   if (m_size != 0){
	           supprimerTous(m_min);
	       }
   }

   /**
    * \brief Permet de savoir si le m_min est vide
    * \return un bool dit dit si le m_min est vide
    */
   bool estVide()
   {
	   return m_size == 0;
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
    	m_min = unir(m_min, ptr);
    	m_size++;
    	return ptr;
    }

    /**
	 * \brief Supprime le noeud minimal
	 * \return La valeur du noeud minimal
	 */
    E supprimerMin()
    {
    	Noeud<E,A>* n = m_min;
    	m_min = extraireMin(m_min);
    	E val = n->m_valeur;
    	delete n;
    	return val;
    }

	Noeud<E,A> * getMin()
	{
		return m_min;
	};

    /**
	 * \brief Permet de diminuer la veleur d'un noeud existant
     * \param p_noeud est un pointeur sur le noeud à modifier
	 * \param p_valeur est la nouvelle valeur du noeud
	 * \pre p_valeur > p_noeud->m_valeur
	 */
   void diminuer(Noeud<E,A>* p_noeud, E p_valeur)
   {
	   // La valeur doit être plus petite que la valeur du noeud actuelle
	   if(p_valeur > p_noeud->m_valeur)
	   {
		   return;
	   }

	   p_noeud->m_valeur = p_valeur;
	   Noeud<E,A>* parent = p_noeud->m_parent;
	   // le noeud est une racine alors rien à faire
       if(parent == nullptr)
       {
    	   return;
       }

       // On coupe le noeud de son père si la propriété du tas est violée
	   if(p_noeud->m_valeur < parent->m_valeur)
	   {
		   Noeud<E,A>* n = couper(p_noeud,parent);
		   m_min = unir(m_min,n);
		   // si les parents sont marqués on les coupent aussi
		   while(parent != nullptr && parent->m_marque)
		   {
			   p_noeud = parent;
			   parent = p_noeud->m_parent;
			   n = couper(p_noeud,parent);
			   m_min = unir(m_min,n);
		   }

		   // On marque le noeud parent si nécessaire
		   if(parent != nullptr && parent->m_parent != nullptr)
		   {
			   parent->m_marque = true;
		   }
	   }
   }

private:
   Noeud<E,A>* m_min;
   unsigned int m_size;

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

   Noeud<E,A>* unir(Noeud<E,A> * a, Noeud<E,A> * b)
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
	   parent->m_enfant = unir(parent->m_enfant, enfant);
   }

   Noeud<E,A>* extraireMin(Noeud<E,A>* n)
   {
	   // Si le noeud min a des enfants on retire leur parenté et leur marque
	   if(n->m_enfant != nullptr)
	   {
		   Noeud<E,A>* temp = n->m_enfant;
	   	   do{
	   		   temp->m_marque = false;
	   		   temp->m_parent = nullptr;
	   		   temp = temp->m_suivant;
	   		 }while(temp != n->m_enfant);
	   }

	   m_size--; // On réduit la taille de 1 puisqu'on retire 1 noeud

	  // On affecte n à un nouveau noeud racine
	  if(n->m_suivant == n)
	  {
		  n = n->m_enfant;
	  }
	  else{
		  n->m_suivant->m_precedent = n->m_precedent;
		  n->m_precedent->m_suivant = n->m_suivant;
		  n = unir(n->m_suivant,n->m_enfant);
	  }

	  if(n == nullptr)
	  {
		  return n;
	  }

	  // On veut avoir un arbre de chaque degré différent
	  int tailleMax = ceil(log2(m_size)/log2(1.618))+1;
	  Noeud<E,A>* arbres[tailleMax]={nullptr};
	  while(true)
	  {
		  // l'arbre de ce degré existe alors on lui ajoute un noeud
		  if(arbres[n->m_degree]!=nullptr)
		  {
			  Noeud<E,A>* a=arbres[n->m_degree];
			  if(a==n)
			  {
				  break;
			  }
			  arbres[n->m_degree]=nullptr;
			  if(n->m_valeur<a->m_valeur)
			  {
				  a->m_precedent->m_suivant=a->m_suivant;
				  a->m_suivant->m_precedent=a->m_precedent;
				  ajouterEnfant(n,a);
			  }
			  else
			  {
				  a->m_precedent->m_suivant=a->m_suivant;
				  a->m_suivant->m_precedent=a->m_precedent;
				  if(n->m_suivant==n)
				  {
					  a->m_suivant=a->m_precedent=a;
					  ajouterEnfant(a,n);
					  n=a;
				  }
				  else
				  {
					  n->m_precedent->m_suivant=a;
					  n->m_suivant->m_precedent=a;
					  a->m_suivant=n->m_suivant;
					  a->m_precedent=n->m_precedent;
					  ajouterEnfant(a,n);
					  n=a;
				  }
			  }
			  continue;
		  }
		  else
		  {
			  // on crée un nouvel arbre à partir du noeud racine
			  arbres[n->m_degree]=n;
		  }
		  n=n->m_suivant;
	  }
	  // On évalue le minimum parmi les noeuds racines
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

   Noeud<E,A>* couper(Noeud<E,A>* e, Noeud<E,A>* p)
   {
	   // l'enfant n'a plus de parent il devient donc un noeud racine
	   if(e->m_suivant==e)
	   {
		   p->m_enfant = nullptr;
	   }
	   else
	   {
		   e->m_suivant->m_precedent = e->m_precedent;
		   e->m_precedent->m_suivant = e->m_suivant;
		   p->m_enfant = e->m_suivant;
	   }

	   e->m_suivant = e->m_precedent = e; // crée un tas d'un élément soit l'élément coupé
	   e->m_marque = false;
	   e->m_parent = nullptr;
	   p->m_degree--;
	   return e;
   }
};






#endif /* FIBO_HPP_ */
