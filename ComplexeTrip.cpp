/*************************************************************************
                           TrajetCompose  -  Inheriting from TrajetSimple, It adds stop off points during the trip
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <TrajetCompose> (fichier TrajetCompose.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
#include <cstring>

//------------------------------------------------------ Include personnel
#include "Town.h"
#include "ComplexeTrip.h"

using namespace std;

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

void ComplexeTrip::showTrip() const
{
	cout << "Complexe trip from: " << start->getName() << " then leaving using " << means;
	
	for (int i = 0; i < numStopOffs; ++i) {
		cout << " to: " << stopOffs[i].t->getName() << " then leaving using " << stopOffs[i].method;
	}

	cout<<" to:" << destination->getName() << endl;
}
bool ComplexeTrip::writeToStream(ostream& out)const{
    out<<numStopOffs<<DELIMITER<< start->getName()<<DELIMITER<<destination->getName()<<DELIMITER<< means<<DELIMITER;
    for(int i = 0;i<numStopOffs;++i){
        out<<stopOffs[i].t->getName()<<DELIMITER<<stopOffs[i].method<<DELIMITER;
    }
    out<<endl;
	return out.good();
}

//------------------------------------------------- Surcharge d'opérateurs



//-------------------------------------------- Constructeurs - destructeur

ComplexeTrip::ComplexeTrip(Town* begin, Town* end, const char* how, Town** stops, char** stopMeans, int numStops):Trip(begin,end,how)
{
	numStopOffs = numStops;
	stopOffs = new stopOff[numStopOffs];
	for (int i = 0; i < numStopOffs; ++i) {
		stopOffs[i].t  = stops[i];
		stopOffs[i].method = new char[strlen(stopMeans[i]) + 1];
		strcpy(stopOffs[i].method, stopMeans[i]);
	}
	isSimple=false;
}

ComplexeTrip::~ComplexeTrip()
{
	for (int i = 0; i < numStopOffs; ++i) {
		delete[] stopOffs[i].method;
	}
	delete[] stopOffs;
}

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées