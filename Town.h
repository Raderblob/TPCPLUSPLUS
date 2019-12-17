#pragma once
#include "LinkedList.h"
#include <iostream>
class Trip;

enum typeSelection{ALL,SIMPLE,COMPLEXE};

class Town
{
public:

	int findPath(const LinkedList<const Town>& path, const Town& objective,const LinkedList<const Trip>& trips);

    int saveTrips(std::ostream & out,typeSelection& tripType);

	const char* getName()const;

	void showTrips();

	void addTrip(Trip* newTrip);

	bool isCalled(const char* tName)const;

	bool operator == (const Town& oTown)const;

	Town(const char* tName);

	virtual ~Town();
private:
	char* myName;
	int myId;
	LinkedList<Trip> outboundTrips;
};

