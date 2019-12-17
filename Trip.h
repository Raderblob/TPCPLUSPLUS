#pragma once
#include <iostream>
using namespace std;

const char DELIMITER = ' ';

class Town;

class Trip
{
public:

	virtual void showTrip() const;

	virtual bool writeToStream(ostream& out);

	Town& getStart()const;
	Town& getEnd() const;
	bool getIsSimple() const;

	Trip(Town* begin,Town* end,const char* how);

	virtual ~Trip();
protected:
	Town* destination;
	Town* start;
	char* means;
	bool isSimple;
};

