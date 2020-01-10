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

int Catalogue::FindPath() const
{
    cin.ignore(INPUTBUFFER,'\n');
    char buffer1[INPUTBUFFER], buffer2[INPUTBUFFER];
    cout << "From: ";
    cin.getline(buffer1, INPUTBUFFER);
    replaceCharacter(buffer1,' ','-');
    cout << " To: ";
    cin.getline(buffer2,INPUTBUFFER);
    replaceCharacter(buffer2,' ','-');
    return findPath(buffer1, buffer2);
}

template <typename T>
void Catalogue::readInput(T& dest, istream& input) const
{
    do {
        if (input.fail())
        {
            input.clear();
            input.ignore(INPUTBUFFER, '\n');
            cout << "input wrong try again" << endl;
        }
        input >> dest;
    } while (input.fail());
}

bool Catalogue::SaveCatalogue(ostream& out) const
{

    if (out.fail())
    {
        cout << "invalid stream state for <SaveCatalogue>" << endl;
        return false;
    }

    //buffer and restriction variables
    typeSelection tripType = ALL;
    char buffer[INPUTBUFFER];
    char originSelect[INPUTBUFFER];
    bool selectFromCertainTown = false;
    int startInterval = 0, endInterval = INT32_MAX, intervalCounter = 0;
    const Town* destinationTown = nullptr;

    //ask user for all restrictions
    cout<<"save all types of trips?(yes/no)"<<endl;
    cin>>buffer;
    if(strcmp(buffer,"yes"))
    {
        cout<<"simple or complexe?"<<endl;
        cin>>buffer;
        if(strcmp(buffer,"simple")==0)
        {
            tripType = SIMPLE;
        }else{
            tripType = COMPLEXE;
        }
    }
    cout<<"Save only from certain town?(yes/no)"<<endl;
    cin>>buffer;
    if(strcmp(buffer,"no"))
    {
        selectFromCertainTown = true;
        cout<<"Enter town name:"<<endl;
        cin.ignore(INPUTBUFFER,'\n');
        cin.getline(originSelect,INPUTBUFFER);
        replaceCharacter(originSelect,' ','-');
    }

    cout<<"Save only to certain town?(yes/no)"<<endl;
    cin>>buffer;
    if(strcmp(buffer,"no"))
    {
        cout<<"Enter town name: "<<endl;
        cin.ignore(INPUTBUFFER,'\n');
        cin.getline(buffer,INPUTBUFFER);
        replaceCharacter(buffer,' ','-');
        destinationTown = getConstTown(buffer);
    }

    cout<<"Save only a certain Interval?(yes/no)"<<endl;
    cin>>buffer;
    if(strcmp(buffer,"no"))
    {
        cout<<"Start interval(Starts at 0):"<<endl;
        readInput(startInterval);
        cout<<"end interval:"<<endl;
        readInput(endInterval);
    }

    stringstream tempOut;
    int res = 0;
    //start going through trips stored in memory and saving those selected
    Iterator<Town> myIterator(allTowns);
    for (Town*  i; !myIterator.AtEnd(); ++myIterator)
    {
        i = myIterator.GetContents();
        if(!selectFromCertainTown || i->IsCalled(originSelect))
        {
            res += i->SaveTrips(tempOut, tripType, startInterval - intervalCounter,
                                endInterval - intervalCounter, destinationTown);
        }
        intervalCounter+= i->GetNumTrips();
    }

    out<<res<<endl<<tempOut.str();
    return out.good();
}

bool Catalogue::LoadCatalogue(std::istream &in)
{

    if (in.fail())
    {
        cout << "invalid stream state for <LoadCatalogue>" << endl;
        return false;
    }

    //buffer and restriction variables
    typeSelection tripType = ALL;
    int startLimit = 0,endLimit = INT32_MAX;
    string buffer;
    string startTown, endTown;
    bool limitToCertainStartTown = false, limitToCertainEndTown = false;

    //ask user for restrictions
    cout<<"Load all types of trips?(yes/no)"<<endl;
    cin>>buffer;

    if(buffer == "no")
    {
        cout<<"simple or complexe?"<<endl;
        cin>>buffer;
        if(buffer == "simple")
        {
            tripType = SIMPLE;
        }else{
            tripType = COMPLEXE;
        }
    }

    cout<<"Load a certain number of trips?(yes/no)"<<endl;
    cin>>buffer;

    if(buffer=="yes")
    {
        cout<<"Start limit: (starts at 0)"<<endl;
        readInput(startLimit);
        cout<<"endLimit: "<<endl;
        readInput(endLimit);
    }

    cout<<"Load only trips from a certain start town?(yes/no)"<<endl;
    cin>>buffer;

    if(buffer=="yes")
    {
        limitToCertainStartTown=true;
        cout<<"Enter town name: "<<endl;
        cin.ignore(INPUTBUFFER,'\n');
        getline(cin,startTown);
        replaceCharacter(startTown,' ','-');
    }

    cout<<"Load only trips going to a certain town?(yes/no)"<<endl;
    cin>>buffer;

    if(buffer=="yes")
    {
        limitToCertainEndTown= true;
        cout<<"Enter town name: "<<endl;
        cin.ignore(INPUTBUFFER,'\n');
        getline(cin,endTown);
        replaceCharacter(endTown,' ','-');
    }

    //read file
    if(in)
    {
        int numLines;
        in>> numLines;
        in.ignore(INPUTBUFFER,'\n');
        for (int i = 0; i < numLines; ++i) // loop for each trip (line)
        {
            string lineBuffer;
            getline(in, lineBuffer);
            if(i>=startLimit &&i<=endLimit)
            {
                bool readTrip = true;
                stringstream lineStream;
                lineStream.str(lineBuffer);

                int numStops;
                string startT,endT;

                lineStream >> numStops;
                lineStream>>startT;
                lineStream>>endT;
                if ((tripType == SIMPLE && numStops != 0) || (tripType == COMPLEXE && numStops == 0))
                {
                    readTrip = false;
                }
                else if((limitToCertainStartTown && startT!=startTown)||(limitToCertainEndTown&&endT!=endTown))
                {
                    readTrip= false;
                }

                lineStream.seekg(0, ios_base::beg); //return to start of line
                if (readTrip)
                {
                    AddTrip(lineStream, false, ' ');//create objects in memory (same as fonction for manual input)
                }
            }
        }
        return true;
    }
    return false;
}

void Catalogue::AddTrip(istream& input, bool echo, char inputDelimiter)
{

    int numStops;
    char buffer[INPUTBUFFER];
    char* startingPoint, *finishingPoint, *meansOfTransport;

    if(echo)
    {
        cout << "Number of stopoff points\n";
    }

    readInput(numStops, input);

    if(echo)
    {
        cout << "Enter starting point\n";
    }
    input.ignore(INPUTBUFFER,inputDelimiter);
    input.getline(buffer,INPUTBUFFER,inputDelimiter);
    replaceCharacter(buffer,' ','-');

    startingPoint = new char[strlen(buffer) + 1];
    strcpy(startingPoint, buffer);

    if(echo)
    {
        cout << "Enter End point\n";
    }
    input.getline(buffer,INPUTBUFFER,inputDelimiter);
    replaceCharacter(buffer,' ','-');

    finishingPoint = new char[strlen(buffer) + 1];
    strcpy(finishingPoint, buffer);

    if(echo)
    {
        cout << "Enter means of transport\n";
    }
    input.getline(buffer,INPUTBUFFER,inputDelimiter);
    replaceCharacter(buffer,' ','-');

    meansOfTransport = new char[strlen(buffer) + 1];
    strcpy(meansOfTransport, buffer);


    if (numStops == 0)
    {
        addTrip(startingPoint, finishingPoint, meansOfTransport);
    }
    else {
        char** stops, ** stopMeans;
        stops = new char* [numStops];
        stopMeans = new char* [numStops];
        for (int i = 0; i < numStops; ++i)
        {
            if(echo)
            {
                cout << i << " st stop\n";
            }
            input.getline(buffer,INPUTBUFFER,inputDelimiter);
            replaceCharacter(buffer,' ','-');

            stops[i] = new char[strlen(buffer) + 1];
            strcpy(stops[i], buffer);

            if(echo)
            {
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

void Catalogue::ShowTrips() const
{
    Iterator<Town> myIterator(allTowns);
    for (Town* i ; !myIterator.AtEnd(); ++myIterator)
    {
        i= myIterator.GetContents();
        i->ShowTrips();
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
    i->AddTrip(newTrip);
    delete[] startingPoint;
    delete[] finishingPoint;
    delete[] meansOfTransport;
}

void Catalogue::addComplexeTrip(const char* startingPoint, const char* finishingPoint, const char* meansOfTransport,
                                char** stops, char** stopMeans, int numStops)
{
    Town* i, * o;
    Town** nSt = new Town*[numStops];


    for (int cnter = 0; cnter < numStops; ++cnter)
    {
        nSt[cnter] = addOrGetTown(stops[cnter]);
    }


    i = addOrGetTown(startingPoint);

    o = addOrGetTown(finishingPoint);

    Trip* newTrip = new ComplexeTrip(i, o, meansOfTransport,nSt,stopMeans,numStops);
    i->AddTrip(newTrip);
    delete[] startingPoint;
    delete[] finishingPoint;
    delete[] meansOfTransport;


    for (int j = 0; j < numStops; ++j)
    {
        delete[] stops[j];
        delete[] stopMeans[j];
    }
    delete[] stops;
    delete[] stopMeans;

    delete[] nSt;
}

int Catalogue::findPath(const char* a, const char* b) const
{
    int res = 0;
    Iterator<Town> myIterator(allTowns);

    for (Town* i; !myIterator.AtEnd(); ++myIterator)
    {
        i= myIterator.GetContents();
        if (i->IsCalled(a))
        {

            Iterator<Town> myIterator2(allTowns);
            for (Town* o ; !myIterator2.AtEnd(); ++myIterator2)
            {
                o= myIterator2.GetContents();
                if (o->IsCalled(b))
                {
                    LinkedList<const Town>* path = new LinkedList<const Town>(false);
                    LinkedList<const Trip>* trips = new LinkedList<const Trip>(false);
                    path->AddItem(i);
                    res = i->FindPath(*path, *o, trips);
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
    allTowns.ResetCursor();
    for (i = allTowns.GetNextItem(); i != nullptr; i = allTowns.GetNextItem())
    {
        if (i->IsCalled(townName))
        {
            break;
        }
    }

    if (i == nullptr)
    {
        Town* newTown = new Town(townName);
        allTowns.AddItem(newTown);
        i = newTown;
    }
    return i;
}

const Town* Catalogue::getConstTown(const char* townName) const
{
    const Town* res;
    for (Iterator<Town> myIterator(allTowns); !myIterator.AtEnd(); ++myIterator)
    {
        res = myIterator.GetContents();
        if(res->IsCalled(townName))
        {
            return res;
        }
    }
    return nullptr;
}

void Catalogue::replaceCharacter(char* aString, char oldChar, char newChar) const
{
    int stringLen = strlen(aString);
    for(int i = 0;i<stringLen;++i)
    {
        aString[i] = tolower(aString[i]);
        if(aString[i]==oldChar)
        {
            aString[i] = newChar;
        }
    }
}

void Catalogue::replaceCharacter(std::string& aString, char oldChar, char newChar) const
{
    int stringLen = aString.length();
    for (int i = 0; i < stringLen; ++i)
    {
        aString[i] = tolower(aString[i]);
        if (aString[i] == oldChar)
        {
            aString[i] = newChar;
        }
    }
}

