#pragma once

#include <string>
#include "Attribut.h"
using namespace std;

class Mesure
{
public:
    
    Mesure (time_t d, string sensorID,Attribut a, double v);
    virtual ~Mesure ( );
    time_t getDate();
    double getValeur();
    Attribut getAttribut();

protected:

    string sensorID;
    time_t date;
    double valeur;
    Attribut attribut;
};
