// TP3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>
#include "Catalogue.h"
using namespace std;

const int INPUTBUFFERSIZE = 100;

void testLeak()
{
    cout << "Starting testLeak" << endl;
    char buffer[INPUTBUFFERSIZE];
    Catalogue myCatalogue;
    cout << "To add a trip : add"<<endl<<"To show contents : show\nTo search : search\nTo save : save\n"
                                         "To load : load\nTo exit : exit\n";
    do {
        do {
            if(cin.fail())
            {
                cin.clear();
                cin.ignore(INPUTBUFFERSIZE,'\n');
                cout<<"input wrong try again"<<endl;
            }
            cin >> buffer;
        }while(cin.fail());

        cout << endl;
        if (strcmp(buffer, "add") == 0)
        {
            myCatalogue.addTrip();
        }
        else if (strcmp(buffer, "show") == 0)
        {
            myCatalogue.showTrips();
        }
        else if (strcmp(buffer, "search") == 0)
        {
            myCatalogue.findPath();
        }else if(strcmp(buffer,"save")==0)
        {
            ofstream outputFile("test.txt");
            if(outputFile)
            {
                myCatalogue.saveCatalogue(outputFile);
                outputFile.close();
            }else{
                cerr<<"File cannot be saved"<<endl;
            }
        }else if(strcmp(buffer,"load")==0)
        {
            ifstream inputFile("test.txt");
            if(!myCatalogue.loadCatalogue(inputFile))
            {
                cerr<<"File cannot be loaded"<<endl;
            }
            inputFile.close();
        }
        for (int i = 0; i < INPUTBUFFERSIZE; ++i)
        {
            cout << "-";
        }
        cout << endl;
    } while (strcmp(buffer, "exit"));

    cout << "Ending testLeak\n";
}

int main()
{
    testLeak();

    cout << "ending program" << endl;
}
