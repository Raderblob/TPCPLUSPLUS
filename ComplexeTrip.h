/*************************************************************************
                           TrajetCompose  -  Inheriting from TrajetSimple, It adds stop off points during the trip
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
    bool writeToStream(ostream& out) const;


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