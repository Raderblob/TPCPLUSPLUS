/*************************************************************************
                           TrajetSimple  -  A class holding start end and means of a trip
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <TrajetSimple> (fichier TrajetSimple.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <cstring>
#include <iostream>
using namespace std;

//------------------------------------------------------ Include personnel
#include "Trip.h"
#include "Town.h"
//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques




void Trip::showTrip() const
{
	cout << "Simple trip from:" << start->getName() << " To:" << destination->getName()<< " using: " <<means<<endl;

}

bool Trip::writeToStream(ostream& out) const
{
    out<<"0 " << start->getName()<<" "<<destination->getName()<<" "<< means<<endl;
	return out.good();
}

const Town& Trip::getEnd() const
{
	return *destination;
}

bool Trip::getIsSimple() const
{
    return isSimple;
}

//------------------------------------------------- Surcharge d'opérateurs


//-------------------------------------------- Constructeurs - destructeur

Trip::Trip(Town* begin, Town* end, const char* how)
{
	start = begin;
	destination = end;
	means = new char[strlen(how) + 1];
	strcpy(means, how);
	isSimple=true;
}


Trip::~Trip()
{
	delete[] means;
}
//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées