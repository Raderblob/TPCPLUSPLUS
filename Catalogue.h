#pragma once
#include "Town.h"
class Catalogue
{
public:

	int findPath();

    bool saveCatalogue(std::ostream& out);



	void addTrip(std::istream& input=std::cin,bool echo = true);

	void showTrips();

	Catalogue();
	virtual ~Catalogue();
private:
	void addTrip(const char* startingPoint, const char* finishingPoint, const char* meansOfTransport);
	void addComplexeTrip(const char* startingPoint, const char* finishingPoint, const char* meansOfTransport,char** stops, char** stopMeans, int numStops);
    int findPath(const char* a, const char* b);
	Town* addOrGetTown(const char* townName);

	LinkedList<Town> allTowns;

};

