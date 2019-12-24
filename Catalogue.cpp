/*************************************************************************
                           Catalogue  -  Contains the main library and the branch network.
                           Contains fonctions that allows users to interact with the information
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <Catalogue> (fichier Catalogue.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
#include <sstream>
#include <cstring>

//------------------------------------------------------ Include personnel
#include "Catalogue.h"
#include "Trip.h"
#include "ComplexeTrip.h"

using namespace std;

//------------------------------------------------------------- Constantes
const int INPUTBUFFER = 100;

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

int Catalogue::findPath()
{
	char buffer1[INPUTBUFFER],buffer2[INPUTBUFFER];
	cout << "From: ";
	cin >> buffer1;
	cout << " To: ";
	cin >> buffer2;
	return findPath(buffer1, buffer2);
}
bool Catalogue::saveCatalogue(ostream& out) {
    typeSelection tripType = ALL;
    char buffer[INPUTBUFFER];
    cout<<"save all?(yes/no)"<<endl;
    cin>>buffer;
    if(strcmp(buffer,"yes")){
        cout<<"simple or complexe?"<<endl;
        cin>>buffer;
        if(strcmp(buffer,"simple")==0){
            tripType = SIMPLE;
        }else{
            tripType = COMPLEXE;
        }
    }

    stringstream tempOut;
    int res = 0;

    allTowns.resetCursor();
    for (Town*  i = allTowns.getNextItem(); i!= nullptr ; i=allTowns.getNextItem()) {
       res+= i->saveTrips(tempOut,tripType);
    }

    out<<res<<endl<<tempOut.str();
	return out.good();
}


void Catalogue::addTrip(istream& input,bool echo)
{

	int numStops;
	char buffer[INPUTBUFFER];
	char* startingPoint,*finishingPoint,*meansOfTransport;

    if(echo) {
        cout << "Number of stopoff points\n";
    }
    input >> numStops;

    if(echo) {
        cout << "Enter starting point\n";
    }
    input >> buffer;
	startingPoint = new char[strlen(buffer) + 1];
	strcpy(startingPoint, buffer);

    if(echo) {
        cout << "Enter End point\n";
    }
    input >> buffer;
	finishingPoint = new char[strlen(buffer) + 1];
	strcpy(finishingPoint, buffer);

    if(echo) {
        cout << "Enter means of transport\n";
    }
    input >> buffer;
	meansOfTransport = new char[strlen(buffer) + 1];
	strcpy(meansOfTransport, buffer);


	if (numStops == 0) {
		addTrip(startingPoint, finishingPoint, meansOfTransport);
	}
	else {
		char** stops, ** stopMeans;
		stops = new char* [numStops];
		stopMeans = new char* [numStops];
		for (int i = 0; i < numStops; ++i) {
            if(echo) {
                cout << i << " st stop\n";
            }
            input >> buffer;
			stops[i] = new char[strlen(buffer) + 1];
			strcpy(stops[i], buffer);

            if(echo) {
                cout << i << " st means\n";
            }
            input >> buffer;
			stopMeans[i] = new char[strlen(buffer) + 1];
			strcpy(stopMeans[i], buffer);
		}

		addComplexeTrip(startingPoint, finishingPoint, meansOfTransport, stops, stopMeans, numStops);
	}
}

void Catalogue::showTrips()
{
	allTowns.resetCursor();
	for (Town* i = allTowns.getNextItem(); i != nullptr; i = allTowns.getNextItem()) {
		i->showTrips();
	}
}

void Catalogue::addTrip(const char* startingPoint, const char* finishingPoint, const char* meansOfTransport)
{
	Town* i,*o;
	i = addOrGetTown(startingPoint);

	o = addOrGetTown(finishingPoint);

	Trip* newTrip = new Trip(i, o, meansOfTransport);
	i->addTrip(newTrip);
	delete[] startingPoint;
	delete[] finishingPoint;
	delete[] meansOfTransport;
}

void Catalogue::addComplexeTrip(const char* startingPoint, const char* finishingPoint, const char* meansOfTransport, char** stops, char** stopMeans, int numStops)
{
	Town* i, * o;
	Town** nSt = new Town*[numStops];

	
	for (int cnter = 0; cnter < numStops; ++cnter) {
		nSt[cnter] = addOrGetTown(stops[cnter]);
	}
	

	i = addOrGetTown(startingPoint);

	o = addOrGetTown(finishingPoint);

	Trip* newTrip = new ComplexeTrip(i, o, meansOfTransport,nSt,stopMeans,numStops);
	i->addTrip(newTrip);
	delete[] startingPoint;
	delete[] finishingPoint;
	delete[] meansOfTransport;


	for (int j = 0; j < numStops; ++j) {
		delete[] stops[j];
		delete[] stopMeans[j];
	}
	delete[] stops;
	delete[] stopMeans;

	delete[] nSt;
}
int Catalogue::findPath(const char* a, const char* b)
{
    int res = 0;
    allTowns.resetCursor();
    for (Town* i = allTowns.getNextItem(); i != nullptr; i = allTowns.getNextItem()) {
        if (i->isCalled(a)) {
            allTowns.resetCursor();
            for (Town* o = allTowns.getNextItem(); o != nullptr; o = allTowns.getNextItem()) {
                if (o->isCalled(b)) {
                    LinkedList<const Town>* path = new LinkedList<const Town>(false);
                    LinkedList<const Trip>* trips = new LinkedList<const Trip>(false);
                    path->addItem(i);
                    res = i->findPath(*path, *o,trips);
                    delete path;
                    delete trips;
                }
            }


            break;
        }
    }

    cout << res << endl;
    return res;
}
Town* Catalogue::addOrGetTown(const char* townName)
{
	Town* i;
	allTowns.resetCursor();
	for (i = allTowns.getNextItem(); i != nullptr; i = allTowns.getNextItem()) {
		if (i->isCalled(townName)) {
			break;
		}
	}
	if (i == nullptr) {
		Town* newTown = new Town(townName);
		allTowns.addItem(newTown);
		i = newTown;
	}
	return i;
}

//------------------------------------------------- Surcharge d'opérateurs



//-------------------------------------------- Constructeurs - destructeur
Catalogue::Catalogue()
{

}

Catalogue::~Catalogue()
{
}

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées