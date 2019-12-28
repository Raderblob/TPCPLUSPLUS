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

int Catalogue::findPath()const
{
    cin.ignore(INPUTBUFFER,'\n');
	char buffer1[INPUTBUFFER],buffer2[INPUTBUFFER];
	cout << "From: ";
	cin.getline(buffer1,INPUTBUFFER);
	replaceCharacter(buffer1,' ','-');
	cout << " To: ";
    cin.getline(buffer2,INPUTBUFFER);
    replaceCharacter(buffer2,' ','-');
	return findPath(buffer1, buffer2);
}
bool Catalogue::saveCatalogue(ostream& out) const{
    typeSelection tripType = ALL;
    char buffer[INPUTBUFFER];
    char originSelect[INPUTBUFFER];
    bool selectFromCertainTown = false;
    int startInterval = 0,endInterval = INT32_MAX,intervalCounter =0;
    const Town* destinationTown = nullptr;

    cout<<"save all types of trips?(yes/no)"<<endl;
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
    cout<<"Save only from certain town?(yes/no)"<<endl;
    cin>>buffer;
    if(strcmp(buffer,"no")){
        selectFromCertainTown = true;
        cout<<"Enter town name:"<<endl;
        cin>>originSelect;
    }

    cout<<"Save only to certain town?(yes/no)"<<endl;
    cin>>buffer;
    if(strcmp(buffer,"no")){
        cout<<"Enter town name: "<<endl;
        cin>>buffer;
        destinationTown = getConstTown(buffer);
    }

    cout<<"Save only a certain Interval?(yes/no)"<<endl;
    cin>>buffer;
    if(strcmp(buffer,"no")){
        cout<<"Start interval(Starts at 0):"<<endl;
        cin>>startInterval;
        cout<<"end interval:"<<endl;
        cin>>endInterval;
    }

    stringstream tempOut;
    int res = 0;

    const Item<Town>* iterator = allTowns.getIterator();
    for (Town*  i; iterator!= nullptr ; iterator=iterator->nextItem) {
        i = iterator->thisItem;
        if(!selectFromCertainTown || i->isCalled(originSelect)) {
            res += i->saveTrips(tempOut, tripType,startInterval-intervalCounter,endInterval-intervalCounter,destinationTown);
        }
        intervalCounter+=i->getNumTrips();
    }

    out<<res<<endl<<tempOut.str();
	return out.good();
}

bool Catalogue::loadCatalogue(std::istream &in)  {
    typeSelection tripType = ALL;
    string buffer;
    cout<<"Load all types of trips?(yes/no)"<<endl;
    cin>>buffer;
    if(buffer == "no"){
        cout<<"simple or complexe?"<<endl;
        cin>>buffer;
        if(buffer == "simple"){
            tripType = SIMPLE;
        }else{
            tripType = COMPLEXE;
        }
    }
    if(in){
        int numLines;
        in>> numLines;
        in.ignore(INPUTBUFFER,'\n');
        for (int i = 0; i < numLines; ++i) {
            bool readTrip = true;
            string lineBuffer;
            getline(in,lineBuffer);
            stringstream lineStream;
            lineStream.str(lineBuffer);

            int numStops;
            lineStream>>numStops;
            if((tripType == SIMPLE && numStops !=0)||(tripType==COMPLEXE &&numStops==0)){
                readTrip=false;
            }

            lineStream.seekg(0,ios_base::beg);
            if(readTrip) {
                addTrip(lineStream, false, ' ');
            }
        }
        return true;
    }
    return false;
}

void Catalogue::addTrip(istream& input,bool echo,char inputDelimiter)
{

	int numStops;
	char buffer[INPUTBUFFER];
	char* startingPoint,*finishingPoint,*meansOfTransport;

    if(echo) {
        cout << "Number of stopoff points\n";
    }
    do {
        if(input.fail()){
            input.clear();
            input.ignore(INPUTBUFFER,'\n');
            cout<<"input wrong try again"<<endl;
        }
        input >> numStops;
    }while(input.fail());
    if(echo) {
        cout << "Enter starting point\n";
    }
    input.ignore(INPUTBUFFER,inputDelimiter);
    input.getline(buffer,INPUTBUFFER,inputDelimiter);
    replaceCharacter(buffer,' ','-');

	startingPoint = new char[strlen(buffer) + 1];
	strcpy(startingPoint, buffer);

    if(echo) {
        cout << "Enter End point\n";
    }
    input.getline(buffer,INPUTBUFFER,inputDelimiter);
    replaceCharacter(buffer,' ','-');

	finishingPoint = new char[strlen(buffer) + 1];
	strcpy(finishingPoint, buffer);

    if(echo) {
        cout << "Enter means of transport\n";
    }
    input.getline(buffer,INPUTBUFFER,inputDelimiter);
    replaceCharacter(buffer,' ','-');

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
            input.getline(buffer,INPUTBUFFER,inputDelimiter);
            replaceCharacter(buffer,' ','-');

			stops[i] = new char[strlen(buffer) + 1];
			strcpy(stops[i], buffer);

            if(echo) {
                cout << i+1 << " st means\n";
            }
            input.getline(buffer,INPUTBUFFER,inputDelimiter);
            replaceCharacter(buffer,' ','-');

			stopMeans[i] = new char[strlen(buffer) + 1];
			strcpy(stopMeans[i], buffer);
		}

		addComplexeTrip(startingPoint, finishingPoint, meansOfTransport, stops, stopMeans, numStops);
	}
}

void Catalogue::showTrips()const
{
    const Item<Town>* iterator = allTowns.getIterator();
	for (Town* i ; iterator != nullptr; iterator = iterator->nextItem) {
	    i=iterator->thisItem;
		i->showTrips();
	}
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
int Catalogue::findPath(const char* a, const char* b)const
{
    int res = 0;
    const Item<Town>* iterator = allTowns.getIterator();


    for (Town* i; iterator != nullptr; iterator = iterator->nextItem) {
        i=iterator->thisItem;
        if (i->isCalled(a)) {

            const Item<Town>* iterator2 = allTowns.getIterator();
            for (Town* o ; iterator2 != nullptr; iterator2 = iterator2->nextItem) {
                o=iterator2->thisItem;
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
const Town* Catalogue::getConstTown(const char* townName) const{
    const Town* res;
    const Item<Town>* iterator = allTowns.getIterator();
    for (;  iterator!= nullptr ; iterator=iterator->nextItem) {
        res = iterator->thisItem;
        if(res->isCalled(townName)){
            return res;
        }
    }
    return nullptr;
}

void Catalogue::replaceCharacter(char* aString, const char oldChar, const char newChar) const{
    int stringLen = strlen(aString);
    for(int i = 0;i<stringLen;++i){
        if(aString[i]==oldChar){
            aString[i] = newChar;
        }
    }
}




