/*************************************************************************
                           Town
			   Contains a list of all trips leaving from the town
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
	int findPath(const LinkedList<const Town>& path, const Town& objective, const LinkedList<const Trip>& trips) const;
	// Mode d'emploi :
	//Find path from this town to a certain town. Cannot go through same town twice
	// Contrat :
	//Path must be a valid list of towns already visited, objective a valid town and trips a valid list of previous trips

    int saveTrips(std::ostream & out,typeSelection tripType = ALL, int startIndex = 0, int endIndex = INT32_MAX,
            const Town* endTownSelect = nullptr) const;
	// Mode d'emploi :
	//Saves all trips from this town to stream
	// Contrat :
	//out must be valid

	const char* getName() const;
	// Mode d'emploi :
	//Returns name of Town
	// Contrat :
	//

	void showTrips() const;
	// Mode d'emploi :
	//Prints all trips from this town to console
	// Contrat :
	//

	void addTrip(Trip* newTrip);
	// Mode d'emploi :
	//Adds a trip to this town
	// Contrat :
	//Trip must be valid and from this town


	bool isCalled(const char* tName) const;
	// Mode d'emploi :
	//Checks if Town is called tName
	// Contrat :
	//

	int getNumTrips() const;
	// Mode d'emploi :
	//Returns number of trips leaving from this town
	// Contrat :
	//
//------------------------------------------------- Surcharge d'opérateurs
    bool operator == (const Town& oTown) const;

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
