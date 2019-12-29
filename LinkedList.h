/*************************************************************************
                           LinkedList  -
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <LinkedList> (fichier LinkedList.h) ----------------
#if ! defined ( LINKEDLIST_H )
#define LINKEDLIST_H
//--------------------------------------------------- Interfaces utilisées
#include "Iterator.h"
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types



//------------------------------------------------------------------------
//
//
//
//------------------------------------------------------------------------



template<class T>
class LinkedList
{
    friend class Iterator<T>;
//----------------------------------------------------------------- PUBLIC
public:
//----------------------------------------------------- Méthodes publiques
	void addItem(T* newItem);
	void removeItem(const T& selectItem);
	T* getNextItem() ;
	T* resetCursor();
	bool contains(const T& val)const;

	const Item<T>* getIterator()const;

//------------------------------------------------- Surcharge d'opérateurs


//-------------------------------------------- Constructeurs - destructeur
	LinkedList(bool ClearOnDeletion = true);
	LinkedList(const LinkedList<T>& oList);
	virtual ~LinkedList();
//------------------------------------------------------------------ PRIVE

private:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
	Item<T>* root;
	int numItems;
	Item<T>* cursor;
	bool deleteContentsOnDeletion;
};
//-------------------------------- Autres définitions dépendantes de <TrajetCompose>
template<class T>
inline void LinkedList<T>::addItem(T* newItem) {
	Item<T>* newCell = new Item<T>;
	newCell->nextItem = nullptr;
	newCell->thisItem = newItem;
	++numItems;

	Item<T>* currSelected = root;
	
	if (currSelected == nullptr) {
		root = newCell;
		return;
	}

	while (currSelected->nextItem != nullptr) {
		currSelected = currSelected->nextItem;
	}
	currSelected->nextItem = newCell;


}

template<class T>
inline void LinkedList<T>::removeItem(const T& selectItem) {
	if (*(root->thisItem) == selectItem) {
		Item<T>* temp = root;
		root = root->nextItem;
		delete temp->thisItem;
		delete temp;
		return;
	}

	Item<T>* currSelected = root;

	while (currSelected->nextItem != nullptr) {
		if (*(currSelected->nextItem->thisItem) == selectItem) {
			Item<T>* temp = currSelected->nextItem;
			currSelected->nextItem = temp->nextItem;
			delete temp->thisItem;
			delete temp;
			return;
		}

		currSelected = currSelected->nextItem;
		
	}

}

template<class T>
inline T* LinkedList<T>::getNextItem() {
	T* res = nullptr;
	
	if (cursor != nullptr) {
		res = cursor->thisItem;
		cursor = cursor->nextItem;
	}
	return res;
}

template<class T>
inline T* LinkedList<T>::resetCursor() {
	cursor = root;
	if(cursor != nullptr)
		return cursor->thisItem;
	return nullptr;
}

template<class T>
inline bool LinkedList<T>::contains(const T& val)const
{


	for (Item<T>* i = root; i != nullptr; i = i->nextItem) {
		if (*(i->thisItem) == val) {
			return true;
		}
	}
	return false;
}

template<class T>
inline const Item<T>* LinkedList<T>::getIterator() const
{
    Iterator<T>* res = new Iterator<T>(*this);
    delete res;
	return root;
}


template<class T>
inline LinkedList<T>::LinkedList(bool clearOnDeletion) {
	root = nullptr;
	numItems = 0;
	cursor = nullptr;
	deleteContentsOnDeletion = clearOnDeletion;
}

template<class T>
inline LinkedList<T>::LinkedList(const LinkedList<T>& oList)
{
	root = nullptr;
	numItems = 0;
	cursor = nullptr;
	deleteContentsOnDeletion = false;

	Item<T>* i;
	for (i = oList.root; i != nullptr; i = i->nextItem) {
		this->addItem(i->thisItem);
	}


}

template<class T>
inline LinkedList<T>::~LinkedList()
{
	
		Item<T>* first = root;
		Item<T>* next;

		while (first != nullptr) {
			next = first->nextItem;
			if (deleteContentsOnDeletion) {
				delete first->thisItem;
			}
			delete first;
			first = next;
		}
	
}
#endif // LINKED_LIST_H