using namespace std;
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include <fstream>
using std::fstream;

#include "Services.h"


Services::Services ()
{

} 


Services::~Services ( )
{

}


double Services::moyenneQualiteAir(Position p, double rayon, time_t jour)
{
    int nbCapteurs=0;
    double moyenne=0;
    fstream source;
    source.open("sensors.csv");
    vector<Capteur> listeCapteurs=this->initCapteur(source);//RECUPERER LES LISTES DE CAPTEURS INITIALISEE  PARTIR DU CSV
    for (auto capteur = begin(listeCapteurs); capteur != end(listeCapteurs); ++capteur)
    {
        if((*capteur).getPosition().estDansLaZone(p,rayon))
        {
            nbCapteurs++;
            moyenne += (*capteur).getATMO(jour);
        }
    }
    moyenne= moyenne/(nbCapteurs);
    source.close();
    return moyenne;
}


/*double Services::moyenneQualiteAir(Position p, double rayon, time_t dateDebut, time_t dateFin)
{
    int nbCapteurs=0;
    double moyPeriode=0;
    double moyenne=0;
    fstream source;
    source.open("sensors.csv");
    vector<Capteur> listeCapteurs=this->initCapteur(source);//RECUPERER LES LISTE DE CAPTEURS INITIALISEE  PARTIR DU CSV
    for (auto capteur = begin(listeCapteurs); capteur != end(listeCapteurs); ++capteur)
    {
        if((*capteur).getPosition().estDansLaZone(p,rayon))
        {
            nbCapteurs++;
            int nbJours=0;
            //PARCOURS DE LA PERIODE
			for(time_t t = dateDebut; t <= dateFin; t += DAY)
			{
                nbJours++;	
				moyenne += (*capteur).getATMO(t);				
			}
            moyPeriode=moyPeriode/nbJours;			
        }
		moyenne=moyenne+moyPeriode;
    }
	moyenne=moyenne/nbCapteurs;
	return moyenne;

}*/

/*
vector<Capteur> Services::identifierCapteursNonFiables()
{
    
}*/

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
        double latitude = stod(lat);
        double longitude = stod(lng);
        Position pos = Position(latitude,longitude);
        Capteur capteur(sensorID,pos);
        capteurs.push_back(capteur);

        cout<< sensorID << lat << lng <<endl;
    }
    return capteurs;
}
vector<Mesure> Services::initMesure(istream& str )
{
    
    vector<Mesure> mesures;
    string ligne;
    string temps;
    string sensorID;
    string attribut;
    string mesure;
    
    while( getline(str,ligne) )
    {
        istringstream iss{ligne};
        getline(iss,sensorID,';');

        string temps = "2012-12-20";
        tm* tf = new tm();
        tf->tm_year = stoi(temps.substr(0,4)) - 1900;
        tf->tm_mon = stoi(temps.substr(5,2)) - 1;
        tf->tm_mday = stoi(temps.substr(8,2));
        time_t time = mktime(tf);
        cout << asctime(tf) << endl;

    }
    return mesures;
}
