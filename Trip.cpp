/*************************************************************************
                           Trip  -  A class holding start end and means of a trip
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <Trip> (fichier Trip.cpp) ------------

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




void Trip::ShowTrip() const
{
	cout << "Simple trip from:" << start->GetName() << " To:" << destination->GetName() << " using: " << means << endl;

}

bool Trip::WriteToStream(ostream& out) const
{

    if (out.fail())
    {
        cout << "invalid stream state for <WriteToStream>" << endl;
        return false;
    }

    out << "0 " << start->GetName() << " " << destination->GetName() << " " << means << endl;
	return out.good();
}

const Town& Trip::GetEnd() const
{
	return *destination;
}

bool Trip::GetIsSimple() const
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
#ifdef MAP
    cout << "Appel au constructeur de <Trip>" << endl;
#endif
}


Trip::~Trip()
{
#ifdef MAP
    cout << "Appel au destructeur de <Trip>" << endl;
#endif
	delete[] means;
}
//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées