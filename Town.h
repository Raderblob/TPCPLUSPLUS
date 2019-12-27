/*************************************************************************
                           Town
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <Town> (fichier Town.h) ----------------
#if ! defined ( TOWN_H )
#define TOWN_H
//--------------------------------------------------- Interfaces utilisées
#include "LinkedList.h"
#include <iostream>
class Trip;
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types
enum typeSelection{ALL,SIMPLE,COMPLEXE};
//------------------------------------------------------------------------
//
//
//
//------------------------------------------------------------------------





class Town
{
//----------------------------------------------------------------- PUBLIC
public:
//----------------------------------------------------- Méthodes publiques
	int findPath(const LinkedList<const Town>& path, const Town& objective,const LinkedList<const Trip>& trips) const;

    int saveTrips(std::ostream & out,typeSelection tripType = ALL, int startIndex = 0, int endIndex = INT32_MAX);

	const char* getName()const;

	void showTrips();

	void addTrip(Trip* newTrip);

	bool isCalled(const char* tName)const;

	int getNumTrips()const;
//------------------------------------------------- Surcharge d'opérateurs
    bool operator == (const Town& oTown)const;

//-------------------------------------------- Constructeurs - destructeur


	Town(const char* tName);

	virtual ~Town();

//------------------------------------------------------------------ PRIVE
private:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
	char* myName;
	int myId;
	int numTrips;
	LinkedList<Trip> outboundTrips;
};
//-------------------------------- Autres définitions dépendantes de <TrajetCompose>
#endif // TOWN_H