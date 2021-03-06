#pragma once
#include <string>
#include <vector>
#include <iostream>

#include "../models/Capteur.h"

using namespace std;

class Services
{

public:
    

    Services ();
    double moyenneQualiteAir(Position p, double rayon, time_t dateDebut, time_t dateFin);
    double moyenneQualiteAir(Position p, double rayon, time_t jour);
    
    vector<Capteur> identifierCapteursNonFiables(time_t dateDebut, time_t dateFin);
    vector<pair<double, Position>> zoneMemeQualiteAir(Capteur capteurRef, time_t debut, time_t fin);
    void setCapteurs(vector<Capteur> c);
    vector<Capteur> getCapteurs();
    void afficherCapteurs();
    Capteur getCapteurByID(string ID);


    
    private:
	vector<Capteur> capteurs;
    
};
