/*************************************************************************
                           TrajetCompose  -  Inheriting from Trip, It adds stop off points during the trip
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <TrajetCompose> (fichier TrajetCompose.h) ----------------
#if ! defined ( TRAJETCOMPOSE_H )
#define TRAJETCOMPOSE_H

//--------------------------------------------------- Interfaces utilisées
#include "Trip.h"
#include "LinkedList.h"
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types
struct stopOff{
    Town* t;
    char* method;
};
//------------------------------------------------------------------------
// Rôle de la classe <TrajetCompose>
//
//
//------------------------------------------------------------------------

class ComplexeTrip: public Trip
{
//----------------------------------------------------------------- PUBLIC
public:
//----------------------------------------------------- Méthodes publiques
	void showTrip() const;
    // Mode d'emploi :
    //Prints trip the console
    // Contrat :
    //

    bool writeToStream(ostream& out) const;
    // Mode d'emploi :
    //Write trip to ouput stream
    // Contrat :
    //out has to be valid

//------------------------------------------------- Surcharge d'opérateurs


//-------------------------------------------- Constructeurs - destructeur

	ComplexeTrip(Town* begin, Town* end, const char* how, Town** stops, char** stopMeans, int numStops);
	virtual ~ComplexeTrip();

//------------------------------------------------------------------ PRIVE
private:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
	stopOff* stopOffs;
	int numStopOffs;
};
//-------------------------------- Autres définitions dépendantes de <TrajetCompose>

#endif // TRAJETCOMPOSE_H
