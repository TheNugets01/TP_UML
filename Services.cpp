using namespace std;
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

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
    vector<Capteur> listeCapteurs;//RECUPERER LES LISTES DE CAPTEURS INITIALISEE  PARTIR DU CSV
    for (auto capteur = listeCapteurs.begin(); capteur != listeCapteurs.end(); ++capteur)
    {
        if((*capteur).getPosition().estDansLaZone(p,rayon))
        {
            nbCapteurs++;
            moyenne += (*capteur).getATMO(jour);
        }
    }
    moyenne= moyenne/(nbCapteurs);
    return moyenne;
}


/*double Services::moyenneQualiteAir(Position p, double rayon, time_t dateDebut, time_t dateFin)
{
    int nbCapteurs=0;
    double moyPeriode=0;
    double moyenne=0;
    vector<Capteur> listeCapteurs;//RECUPERER LES LISTE DE CAPTEURS INITIALISEE  PARTIR DU CSV
    for (auto capteur = listeCapteurs.begin(); capteur != listeCapteurs.end(); ++capteur)
    {
        if((*capteur).getPosition().estDansLaZone(p,rayon))
        {
            nbCapteurs++;
            int nbJours=0;
            //PARCOURS DE LA PERIODE
			for(time_t time=dateDebut; time<=dateFin; )
			{
				moyenne += (*capteur).getATMO(time);
				moyPeriode=moyPeriode/nbJours;	
			}			
        }
		moyenne=moyenne+moyPeriode;
    }
	moyenne=moyenne/nbCapteurs;
	return moyenne;

}*/

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
        double latitude = stod(lat);
        double longitude = stod(lng);
        Position pos = Position(latitude,longitude);
        Capteur capteur(sensorID,pos);
        capteurs.push_back(capteur);

        cout<< sensorID << lat << lng <<endl;
    }
    return capteurs;
}
