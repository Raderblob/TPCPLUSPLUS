/*************************************************************************
                           Catalogue  -  Contains the main library and the branch network.
                           Contains fonctions that allows users to interact with the information
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/
//---------- Interface de la classe <Iterator> (fichier Iterator.h) ----------------
#ifndef TP3_ITERATOR_H
#define TP3_ITERATOR_H


//--------------------------------------------------- Interfaces utilisées
template<class T>
class LinkedList;
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types
template<class T>
struct Item {
    struct Item* nextItem;
    T* thisItem;
};

//------------------------------------------------------------------------
// Rôle de la classe <Iterator>
//
//
//------------------------------------------------------------------------
template<class T>
class Iterator {
//----------------------------------------------------------------- PUBLIC
public:
//----------------------------------------------------- Méthodes publiques
    T* getContents() const;
    // Mode d'emploi :
    //Return contents of iterator
    // Contrat :
    //

    bool atEnd() const;
    // Mode d'emploi :
    //Check if iterator is at the end of the list
    // Contrat :
    //

//------------------------------------------------- Surcharge d'opérateurs
    Iterator<T>& operator ++();


//-------------------------------------------- Constructeurs - destructeur
    explicit Iterator(const LinkedList<T>& aList);

    virtual ~Iterator();

//------------------------------------------------------------------ PRIVE
private:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
    Item<T>* myData;
};


//-------------------------------- Autres définitions dépendantes de <Iterator>
template<class T>
inline Iterator<T>::Iterator(const LinkedList<T>& aList)
{
    myData = aList.root;
}

template<class T>
inline Iterator<T>::~Iterator()
{

}

template<class T>
Iterator<T>& Iterator<T>::operator++()
{
    if(myData != nullptr)
    {
        myData = myData->nextItem;
    }
    return *this;
}

template<class T>
T* Iterator<T>::getContents() const
{
    return (myData->thisItem);
}

template<class T>
bool Iterator<T>::atEnd() const
{
    return myData== nullptr;
}


#endif //TP3_ITERATOR_H
