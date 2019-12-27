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

	virtual bool writeToStream(ostream& out)const;

	const Town& getStart()const;
	const Town& getEnd() const;
	bool getIsSimple() const;
//------------------------------------------------- Surcharge d'opérateurs



//-------------------------------------------- Constructeurs - destructeur
	Trip(Town* begin,Town* end,const char* how);

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