/*************************************************************************
                           Catalogue  -  Contains the main library and the branch network.
                           Contains fonctions that allows users to interact with the information
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <Catalogue> (fichier Catalogue.h) ----------------
#if ! defined ( CATALOGUE_H )
#define CATALOGUE_H


//--------------------------------------------------- Interfaces utilisées
#include "Town.h"

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Catalogue>
//
//
//------------------------------------------------------------------------

class Catalogue
{
//----------------------------------------------------------------- PUBLIC
public:
//----------------------------------------------------- Méthodes publiques
	int findPath() const;
    // Mode d'emploi :
    //find a path
    // Contrat :
    //

    bool saveCatalogue(std::ostream& out)const;



	void addTrip(std::istream& input=std::cin,bool echo = true,char inputDelimiter = '\n');

	void showTrips()const;

//------------------------------------------------- Surcharge d'opérateurs



//-------------------------------------------- Constructeurs - destructeur

	Catalogue();
	virtual ~Catalogue();

//------------------------------------------------------------------ PRIVE


private:
//----------------------------------------------------- Méthodes protégées

	void addTrip(const char* startingPoint, const char* finishingPoint, const char* meansOfTransport);
	void addComplexeTrip(const char* startingPoint, const char* finishingPoint, const char* meansOfTransport,char** stops, char** stopMeans, int numStops);
    int findPath(const char* a, const char* b)const;
	Town* addOrGetTown(const char* townName);
    const Town* getConstTown(const char* townName)const ;

	void replaceCharacter(char* string,const char oldChar,const char newChar)const;
//----------------------------------------------------- Attributs protégés
	LinkedList<Town> allTowns;

};

//-------------------------------- Autres définitions dépendantes de <Catalogue>
#endif // CATALOGUE_H