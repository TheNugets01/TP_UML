using namespace std;
#include <ctime>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include <fstream>
using std::fstream;

#include "ServiceInit.h"

#define DAY 86400


void ServiceInit::init(){
    fstream source;
    fstream sourceMesures;
    fstream sourceAtt;
    cout<<"init......"<<endl;
    source.open("../data/sensors.csv");
    sourceMesures.open("../data/measurements.csv");
    sourceAtt.open("../data/attributes.csv");

    vector<Capteur> capteurs;
    initCapteurs(capteurs,source);

    vector<Attribut> attributs;
    initAttributes(attributs,sourceAtt);

    initMesures(capteurs,attributs,sourceMesures);

    service_capteurs.setCapteurs(capteurs);

    source.close();
    sourceMesures.close();
    sourceAtt.close();
}

void ServiceInit::initCapteurs(vector<Capteur>& capteurs,istream& str)
{
    
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
    }
}

void ServiceInit::initAttributes(vector<Attribut>& attributs,istream& str){
    
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

}

void ServiceInit::initMesures(vector<Capteur>& capteurs, vector<Attribut>& attributs,istream &str ){
    {

    string ligne;
    string sTemps;
    string sensorID;
    string attributID;
    string sValeur;

    int itr=0;

    while( getline(str,ligne) && itr<10000000)
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
        
        const Capteur temp(sensorID, Position(0.0, 0.0));
        vector<Capteur>::iterator it = find(capteurs.begin(), capteurs.end(), temp);

		if (it != capteurs.end())
		{
			it->ajouterMesure(Mesure(temps , sensorID , attribut , valeur));
		}
    }    
}

}

Services ServiceInit::getServices()
{
	return service_capteurs;
}