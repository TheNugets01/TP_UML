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
    vector<Mesure> mesuresCapteur;
    fstream sourceCap;
    sourceCap.open("sensors.csv");
    vector<Capteur> capteurs = initCapteur(sourceCap);
    fstream sourceAtt;
    sourceAtt.open("attributes.csv");
    vector<Attribut> attributs = initAttribut(sourceAtt);

    string ligne;
    string sTemps;
    string sensorID;
    string attributID;
    string sValeur;

    int itr=0;
    time_t tempsPrecedent;


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

        // Au premier passage ont ne peut psa connaitre le temps précedent donc on les considere identique
        if( itr == 1 ){
            tempsPrecedent = temps;
        }
        

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

        if(tempsPrecedent == temps)
        //Si temps même que précedent ajouter mesure
        {
            mesuresCapteur.push_back(mesure);
        } else { //Sinon envoyer la liste au capteur défini

        }
        for( auto capteur : capteurs  )
        {
            
        }

        tempsPrecedent = temps;
    }
    return mesures;
}
