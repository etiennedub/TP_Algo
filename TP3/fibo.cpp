//
// Created by etienned on 11/30/16.
//

#include "fibo.h"

Fibo::Fibo(){
    m_ptrMin = nullptr;
}

Fibo::~Fibo() {
    if (m_ptrMin != nullptr){
        supprimerTous(m_ptrMin);
    }
}

void Fibo::supprimerTous(Noeud *p_noeud) {
    if( p_noeud != nullptr){
        Noeud * a = p_noeud;
        do {
            Noeud * b = a;
            a = a->m_suivant;
            supprimerTous(b->m_enfant);
            delete b;
        } while(a != p_noeud);
    }
}

template<typename E, typename A>
Noeud* Fibo<E,A>::ajouter(A p_id, E p_valeur){
    Noeud* ptr = new Noeud(p_id, p_valeur);
    m_ptrMin = merge(m_ptrMin, ptr);
    return ptr;
}

Noeud * Fibo::merge(Noeud * a, Noeud * b){
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

    Noeud * aSuivant = a->m_suivant;
    Noeud * bPrecedent = b->m_precedent;
    a->m_suivant = b;
    b->m_precedent = a;
    aSuivant->m_precedent = bPrecedent;
    bPrecedent->m_suivant = aSuivant;

    return a;
}

