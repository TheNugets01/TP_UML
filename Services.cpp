using namespace std;
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

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
    double moyenne=0.0;
    
    fstream cap;
    fstream source;
    cap.open("sensors.csv");
    source.open("measurements.csv");
    vector<Capteur> capteurs=initCapteur(cap);

    initMesure(source,capteurs);

    for (auto capteur : capteurs)
    {
        if(capteur.getPosition().estDansLaZone(p,rayon))
        {
            nbCapteurs++;
            moyenne += capteur.getATMO(jour);
        }
    }
    moyenne= moyenne/(nbCapteurs);
    source.close();
    return moyenne;
}


double Services::moyenneQualiteAir(Position p, double rayon, time_t dateDebut, time_t dateFin)
{
    double moyenne=0.0;
    int nbJours=0;

    for(time_t t = dateDebut; t <= dateFin; t += DAY)
    {
        nbJours++;	
        moyenne=moyenne+moyenneQualiteAir(p,rayon,t);				
    }
    moyenne=moyenne/nbJours;
    return moyenne;
}

//lister les capteurs non fiables detectés entre deux dates 
vector<Capteur> Services::identifierCapteursNonFiables(time_t dateDebut, time_t dateFin)
{
    fstream cap;
    fstream source;
    cap.open("sensors.csv");
    source.open("measurements.csv");
    vector<Capteur> capteurs=initCapteur(cap);

    initMesure(source,capteurs);

    vector<Capteur> liste_non_fiables;
    const double rayon = 2.5;
    double moyenne=0.0;
    double moyenneZone=0.0;

    //cout<<capteurs.size()<<endl;

    //bool pushed;
    for (auto capteur:capteurs)
    {
        //pushed = false;
        //cout<<"on a un capteur"<<endl;
        moyenne = capteur.getMoyATMO(dateDebut, dateFin);
        //cout<<"atmo: "<<moyenne<<endl;
        moyenneZone = moyenneQualiteAir(capteur.getPosition(),rayon,dateDebut, dateFin);
        //cout<<"zone: "<<moyenneZone<<endl;
        if(moyenne<0.5*moyenneZone || moyenne>2*moyenne){
            //cout<<"pushed"<<endl;
            liste_non_fiables.push_back(capteur);
            //pushed = true;
        }
        else{
            for (time_t day = dateDebut; day <= dateFin; day += DAY){
                if(capteur.getATMO(day)<0.5*moyenne||capteur.getATMO(day)>2*moyenne){
                   // cout<<"pushed"<<endl;
                    //pushed = true;
                    liste_non_fiables.push_back(capteur);
                    break;
                }
                
            }
            
            
        }
        //if(!pushed)cout<<"unpushed"<<endl;
    }
    
    return liste_non_fiables;
}


bool c(pair<double,Position> a, pair<double,Position> b) {
	return a.first < b.first;
}
vector<pair<double, Position>> Services::zoneMemeQualiteAir(Capteur& capteurRef, time_t debut, time_t fin)
{
    fstream cap;
    fstream source;
    cap.open("sensors.csv");
    source.open("measurements.csv");
    vector<Capteur> capteurs=initCapteur(cap);

    initMesure(source,capteurs);
	
    vector<pair<double,Position>> positions;

	if ((fin != 0 && difftime(fin, debut) < 0.f))
	{
		return positions;
	}

	double reference = capteurRef.getMoyATMO(debut, fin);
	double currentValue, diff;

	for (Capteur cpt : capteurs) 
	{
		currentValue = cpt.getMoyATMO(debut, fin); //get caracteristic value of Sensor i
		diff = abs(reference - currentValue);
		positions.push_back(std::make_pair(diff, cpt.getPosition()));
	}
	//trier la liste par la difference de mesure
	std::sort(positions.begin(), positions.end(), c);
	return positions;
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

void Services::initMesure(istream& str, vector<Capteur>& capteurs )
{
    fstream sourceAtt;
    sourceAtt.open("attributes.csv");
    vector<Attribut> attributs = initAttribut(sourceAtt);

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
