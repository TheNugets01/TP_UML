using namespace std;
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include <fstream>
using std::fstream;

#include "Services.h"

#define DAY 86400

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


double Services::moyenneQualiteAir(Position p, double rayon, time_t dateDebut, time_t dateFin)
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

}

//lister les capteurs non fiables detectés entre deux dates 
vector<Capteur> Services::identifierCapteursNonFiables(time_t dateDebut, time_t dateFin)
{
    vector<Capteur> liste_non_fiables;
    const double rayon = 0.5;
    double moyenne=0;
    double moyenneZone=0;

    fstream source;
    source.open("sensors.csv");

    vector<Capteur> listeCapteurs=this->initCapteur(source);//RECUPERER LES LISTES DE CAPTEURS INITIALISEE  PARTIR DU CSV
    for (auto capteur = begin(listeCapteurs); capteur != end(listeCapteurs); ++capteur)
    {
        moyenne = capteur->getMoyATMO(dateDebut, dateFin);
        moyenneZone = moyenneQualiteAir(capteur->getPosition(),rayon,dateDebut, dateFin);

        if(moyenne<0.5*moyenneZone || moyenne>2*moyenne){
            liste_non_fiables.push_back(*capteur);
        }
        else{
            for (time_t day = dateDebut; day <= dateFin; day += DAY){
                if(capteur->getATMO(day)<0.5*moyenne||capteur->getATMO(day)>1.5*moyenne){
                    liste_non_fiables.push_back(*capteur);
                }
            }
        }
    }
    return liste_non_fiables;
}

vector<Capteur> Services::initCapteur(istream& str)
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

vector<Attribut> Services::initAttribut(istream& str){
    vector<Attribut> attributs;
    string ligne;
    string attributID;
    string unite;
    string description;

    getline(str,ligne); // Ignorer la première ligne du fichier

     while( getline(str,ligne) )
    {
        istringstream iss{ligne};
        getline(iss,attributID,';');
        getline(iss,unite,';');
        getline(iss,description,';');

        Attribut attribut(attributID,unite,description);
        attributs.push_back(attribut);
    }
    
    return attributs;
}

vector<Mesure> Services::initMesure(istream& str )
{
    vector<Mesure> mesures;
    string ligne;
    string sTemps;
    string sensorID;
    string attributID;
    string sValeur;

    fstream source;
    source.open("attributes.csv");
    vector<Attribut> attributs = initAttribut(source);
    int itr=0;
    while( getline(str,ligne) && itr<5)
    {
        itr++;
        istringstream iss{ligne};

        getline(iss,sTemps,';'); //Date de la mesure
        tm* tf = new tm();
        tf->tm_year = stoi(sTemps.substr(0,4)) - 1900;
        tf->tm_mon = stoi(sTemps.substr(5,2)) - 1;
        tf->tm_mday = stoi(sTemps.substr(8,2));
        time_t temps = mktime(tf);
        

        getline(iss,sensorID,';'); //Sensor ID

        getline(iss,attributID,';'); //Attribut
        Attribut attribut;
        for(int i = 0; i<attributs.size() ;++i){
            if( attributID.compare(attributs[i].getID()) == 0 ){
                attribut = attributs[i];
            }
        }

        getline(iss,sValeur,';');//Valeur
        double valeur = stod(sValeur);
        
        Mesure mesure(temps , sensorID , attribut , valeur);
        mesures.push_back(mesure);
    }
    return mesures;
}
