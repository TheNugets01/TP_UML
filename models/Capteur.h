#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include "Position.h"
#include "Mesure.h"
using namespace std;

class Capteur
{
public:
   
    Capteur();
    Capteur (string ID, Position pos);
    Position getPosition();
    virtual ~Capteur ( );
    int getATMO(time_t date);
    double getMoyATMO(time_t dateDebut, time_t dateFin);
    int maxi(int, int, int, int);
    int index(double valeur, double palier1, double palier2, double palier3, double palier4, double palier5, double palier6, double palier7, double palier8, double palier9);
    void ajouterMesure(Mesure mesure);
    string getID();
    void setMesures(time_t temps, vector<Mesure> mesures);
    void setVecteursMesures(Mesure mesure);
    unordered_map<time_t, vector<Mesure>>& getMesures();
	friend bool operator==(const Capteur&, const Capteur&);

    protected:

    string sensorID;
    Position position;
    unordered_map<time_t, vector<Mesure> > mesures;
};
