/*************************************************************************
                           TrajetSimple  -  A class holding start end and means of a trip
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <TrajetSimple> (fichier TrajetSimple.h) ----------------
#if ! defined ( TRAJETSIMPLE_H )
#define TRAJETSIMPLE_H


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
	virtual void showTrip() const;
	// Mode d'emploi :
	//Print trip to console
	// Contrat :
	//

	virtual bool writeToStream(ostream& out) const;
	// Mode d'emploi :
	//Write trip to ostream
	// Contrat :
	//out must be valid

	const Town& getEnd() const;
	// Mode d'emploi :
	//Returns the destination of the trip (read only)
	// Contrat :
	//

	bool getIsSimple() const;
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
#endif // TRAJETSIMPLE_H