#include <iostream>
#include <cstring>
#include "Town.h"
#include "Trip.h"

using namespace std;

int Town::findPath(const LinkedList<const Town>& path, const Town& objective, const LinkedList<const Trip>& trips)
{
	int res=0;
	outboundTrips.resetCursor();
	for (Trip* i = outboundTrips.getNextItem(); i != nullptr; i = outboundTrips.getNextItem()) {
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

int Town::saveTrips(ostream& out,typeSelection& tripType) {
    int res = 0;
    outboundTrips.resetCursor();
    for (Trip* i = outboundTrips.getNextItem();  i!=nullptr; i=outboundTrips.getNextItem()) {
        if(tripType==ALL || (tripType == SIMPLE && i->getIsSimple()) || (tripType == COMPLEXE && !i->getIsSimple())){
            i->writeToStream(out);
            res++;
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
}

bool Town::isCalled(const char* tName)const {
	return !strcmp(myName, tName);
}

bool Town::operator==(const Town& oTown)const
{
	return myId==oTown.myId;
}

Town::Town(const char* tName) {
	static int idCounter = 0;
	myName = new char[strlen(tName)+1];
	strcpy(myName, tName);
	myId = idCounter++;
}


Town::~Town() {
	delete[] myName;
}
