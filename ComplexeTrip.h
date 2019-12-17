#pragma once
#include "Trip.h"
#include "LinkedList.h"

struct stopOff {
	Town* t;
	char* method;
};
class ComplexeTrip :public Trip
{
public:
	virtual void showTrip() const;
    virtual bool writeToStream(ostream& out);

	ComplexeTrip(Town* begin, Town* end, const char* how,Town** stops,char** stopMeans,int numStops);
	virtual ~ComplexeTrip();

private:
	stopOff* stopOffs;
	int numStopOffs;
};

