#include <cstring>
#include <iostream>
#include "Trip.h"
#include "Town.h"

using namespace std;



void Trip::showTrip() const
{
	cout << "Simple trip from:" << start->getName() << " To:" << destination->getName()<< " using: " <<means<<endl;

}

bool Trip::writeToStream(ostream& out){
    out<<"0 " << start->getName()<<" "<<destination->getName()<<" "<< means<<endl;
}

Town& Trip::getEnd() const
{
	return *destination;
}

bool Trip::getIsSimple() const {
    return isSimple;
}

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
