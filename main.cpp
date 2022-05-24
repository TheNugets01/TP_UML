#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <time.h>

#include "Utilisateur.h"
#include "Capteur.h"
#include "Services.h"


using namespace std;

int main()
{
    Utilisateur *U1 = new Utilisateur("hugo","mdp");
    Utilisateur *U2 = new Utilisateur("octave","oui");
    cout << U1->userID << endl;
    cout << U2->userID << endl;

    Position *p1 = new Position(45.778912,4.871650);
    Position *p2 = new Position(45.776199,4.871971);
    cout << p1->estDansLaZone(*p2,10.0) << endl;
    cout << p1->estDansLaZone(*p2,0.001) << endl;

    /*string time_details = "2009-12-31";
    struct tm tm;
    strptime(time_details.c_str(), "%Y-%m-%d", &tm);
    time_t t = mktime(&tm);  // t is now your desired time_t
    cout << asctime(localtime(&t)) << endl;*/

    string temps = "2012-12-20";
    tm* tf = new tm();
    tf->tm_year = stoi(temps.substr(0,4)) - 1900;
    tf->tm_mon = stoi(temps.substr(5,2)) - 1;
    tf->tm_mday = stoi(temps.substr(8,2));
    mktime(tf);
    cout << asctime(tf) << endl;

    Services* service = new Services();
    fstream source;
    source.open("measurements.csv");
    service->initMesure(source);
    
    //service->initAttribut(source);
    //service->moyenneQualiteAir(*p1,2.4,"2019-01-02");


    return 0;
}