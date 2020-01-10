/*************************************************************************
                           TOWN
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <Town> (fichier Town.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
#include <cstring>
//------------------------------------------------------ Include personnel
#include "Town.h"
#include "Trip.h"

using namespace std;
//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

int Town::FindPath(const LinkedList<const Town>& path, const Town& objective, const LinkedList<const Trip>& trips) const
{
	int res=0;
    Iterator<Trip> myIterator(outboundTrips);
	for (Trip* i; !myIterator.AtEnd(); ++myIterator)
	{
		i = myIterator.GetContents();
		if (!path.Contains(i->GetEnd()))
		{
			LinkedList<const Trip>* newTrips = new LinkedList<const Trip>(trips);
			LinkedList<const Town>* newPath = new LinkedList<const Town>(path);
            newTrips->AddItem(i);
            newPath->AddItem(&(i->GetEnd()));
			if (i->GetEnd() == objective)
			{
                newPath->ResetCursor();
				for (const Town* o = newPath->GetNextItem(); o != nullptr; o = newPath->GetNextItem())
				{
					cout << o->GetName() << " ";
				}
				cout << endl;
                newTrips->ResetCursor();
				for (const Trip* o = newTrips->GetNextItem(); o != nullptr; o = newTrips->GetNextItem())
				{
                    o->ShowTrip();
				}
				cout << endl;
				res++;
			}
			else {
				res += i->GetEnd().FindPath(*newPath, objective, *newTrips);
				
			}
			delete newPath;
			delete newTrips;
		}
	
	}

	return res;
}

int Town::SaveTrips(ostream& out, typeSelection tripType, int startIndex, int endIndex, const Town* endTownSelect) const
{
    int res = 0;
    int indexChecker = 0;

    Iterator<Trip> myIterator(outboundTrips);
    for (Trip* i; !myIterator.AtEnd(); ++myIterator)
    {
        i= myIterator.GetContents();
        if(tripType==ALL || (tripType == SIMPLE && i->GetIsSimple()) || (tripType == COMPLEXE && !i->GetIsSimple()))
        {
            if(endTownSelect== nullptr|| i->GetEnd() == (*endTownSelect))
            {
                if (indexChecker >= startIndex && indexChecker <= endIndex)
                {
                    i->WriteToStream(out);
                    res++;
                }
                indexChecker++;
            }
        }
        if(indexChecker>endIndex)
        {
            return res;
        }
    }
    return res;
}

const char* Town::GetName() const
{
	return myName;
}

void Town::ShowTrips() const
{
    Iterator<Trip> myIterator(outboundTrips);
    for (Trip* i; !myIterator.AtEnd(); ++myIterator)
    {
        i= myIterator.GetContents();
        i->ShowTrip();
    }
}

void Town::AddTrip(Trip* newTrip)
{
    outboundTrips.AddItem(newTrip);
	++numTrips;
}

bool Town::IsCalled(const char* tName) const
{
	return !strcmp(myName, tName);
}

int Town::GetNumTrips() const
{
    return numTrips;
}

//------------------------------------------------- Surcharge d'opérateurs
bool Town::operator==(const Town& oTown) const
{
    return myId==oTown.myId;
}


//-------------------------------------------- Constructeurs - destructeur
Town::Town(const char* tName)
{
	static int idCounter = 0;
	myName = new char[strlen(tName)+1];
	strcpy(myName, tName);
	myId = idCounter++;
	numTrips=0;
#ifdef MAP
    cout << "Appel au constructeur de <Town>" << endl;
#endif
}


Town::~Town()
{
#ifdef MAP
    cout << "Appel au destructeur de <Town>" << endl;
#endif
	delete[] myName;
}


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées