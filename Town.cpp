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

int Town::findPath(const LinkedList<const Town>& path, const Town& objective, const LinkedList<const Trip>& trips) const
{
	int res=0;
	const Item<Trip>* iterator = outboundTrips.getIterator();
	if (iterator == nullptr) {
		return res;
	}

	for (Trip* i = iterator->thisItem; iterator != nullptr;iterator = iterator->nextItem) {
		i = iterator->thisItem;
		if (!path.contains(i->getEnd())) {
			LinkedList<const Trip>* newTrips = new LinkedList<const Trip>(trips);
			LinkedList<const Town>* newPath = new LinkedList<const Town>(path);
			newTrips->addItem(i);
			newPath->addItem(&(i->getEnd()));
			if (i->getEnd() == objective) {
				newPath->resetCursor();
				for (const Town* o = newPath->getNextItem(); o != nullptr; o = newPath->getNextItem()) {
					cout << o->getName() << " ";
				}
				cout << endl;
				newTrips->resetCursor();
				for (const Trip* o = newTrips->getNextItem(); o != nullptr; o = newTrips->getNextItem()) {
					o->showTrip();
				}
				cout << endl;
				res++;
			}
			else {
				res += i->getEnd().findPath(*newPath, objective,*newTrips);
				
			}
			delete newPath;
			delete newTrips;
		}
	
	}

	return res;
}

int Town::saveTrips(ostream& out,typeSelection tripType,int startIndex, int endIndex,const Town* endTownSelect) {
    int res = 0;
    int indexChecker = 0;
    outboundTrips.resetCursor();
    for (Trip* i = outboundTrips.getNextItem();  i!=nullptr; i=outboundTrips.getNextItem()) {
        if(tripType==ALL || (tripType == SIMPLE && i->getIsSimple()) || (tripType == COMPLEXE && !i->getIsSimple())){
            if(endTownSelect== nullptr||i->getEnd()==(*endTownSelect)) {
                if (indexChecker >= startIndex && indexChecker <= endIndex) {
                    i->writeToStream(out);
                    res++;
                }
                indexChecker++;
            }
        }
        if(indexChecker>endIndex){
            return res;
        }
    }
    return res;
}

const char* Town::getName() const
{
	return myName;
}

void Town::showTrips()
{
	outboundTrips.resetCursor();
	for (Trip* i = outboundTrips.getNextItem(); i != nullptr; i = outboundTrips.getNextItem()) {
		i->showTrip();
	}
}

void Town::addTrip(Trip* newTrip)
{
	outboundTrips.addItem(newTrip);
	++numTrips;
}

bool Town::isCalled(const char* tName)const {
	return !strcmp(myName, tName);
}
int Town::getNumTrips() const {
    return numTrips;
}

//------------------------------------------------- Surcharge d'opérateurs
bool Town::operator==(const Town& oTown)const
{
    return myId==oTown.myId;
}


//-------------------------------------------- Constructeurs - destructeur
Town::Town(const char* tName) {
	static int idCounter = 0;
	myName = new char[strlen(tName)+1];
	strcpy(myName, tName);
	myId = idCounter++;
	numTrips=0;
}


Town::~Town() {
	delete[] myName;
}


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées