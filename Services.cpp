using namespace std;
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "Services.h"

#define BUFFER 100

Services::Services ()
{

} 


Services::~Services ( )
{

}

double Services::moyenneQualiteAir(Position p, double rayon, string dateDebut, string dateFin)
{
    int nbCapteurs=0;
    int moyenne=0;
    vector<Capteur> listeCapteurs;
    for (auto capteur = listeCapteurs.begin(); capteur != listeCapteurs.end(); ++capteur)
    {
        if((*capteur).getPosition().estDansLaZone(p,rayon))
        {

        }
    }

    
}
double Services::moyenneQualiteAir(Position p, double rayon, string moment)
{

}
vector<Capteur> Services::identifierCapteursNonFiables()
{
    
}

vector<Capteur> Services::initCapteur(istream& str )
{
    
    vector<Capteur> capteurs;
    string ligne;
    string sensorID;
    string lat;
    string lng;
    
    while( getline(str,ligne) )
    {
        istringstream iss{ligne};
        getline(iss,sensorID,';');
        getline(iss,lat,';');
        getline(iss,lng,';');
        int latitude = stoi(lat);
        int longitude = stoi(lng);
        Capteur capteur(sensorID,latitude,longitude);
        capteurs.push_back(capteur);

        cout<< sensorID << lat << lng <<endl;
    }
    return capteurs;
}
