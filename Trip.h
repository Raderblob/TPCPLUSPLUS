/*************************************************************************
                           Trip  -  A class holding start end and means of a trip
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <Trip> (fichier Trip.h) ----------------
#if ! defined ( TRIP_H )
#define TRIP_H


//--------------------------------------------------- Interfaces utilisées
#include <iostream>
using namespace std;
class Town;
//------------------------------------------------------------- Constantes
const char DELIMITER = ' ';
//------------------------------------------------------------------ Types


class Trip
{
//----------------------------------------------------------------- PUBLIC
public:
//----------------------------------------------------- Méthodes publiques
	virtual void ShowTrip() const;
	// Mode d'emploi :
	//Print trip to console
	// Contrat :
	//

	virtual bool WriteToStream(ostream& out) const;
	// Mode d'emploi :
	//Write trip to ostream
	// Contrat :
	//out must be valid

	const Town& GetEnd() const;
	// Mode d'emploi :
	//Returns the destination of the trip (read only)
	// Contrat :
	//

	bool GetIsSimple() const;
	// Mode d'emploi :
	//Returns if the trip is Simple, returns false if complex
	// Contrat :
	//

//------------------------------------------------- Surcharge d'opérateurs



//-------------------------------------------- Constructeurs - destructeur
	Trip(Town* begin, Town* end, const char* how);

	virtual ~Trip();

//------------------------------------------------------------------ PRIVE
protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
	Town* destination;
	Town* start;
	char* means;
	bool isSimple;
};
//-------------------------------- Autres définitions dépendantes de <TrajetSimple>
#endif // TRIP_H