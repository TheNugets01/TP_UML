#pragma once

#include <string>
#include "Attribut.h"
using namespace std;

class Mesure
{
public:
    
    Mesure (time_t d, double v, Attribut a);
    virtual ~Mesure ( );
    time_t getDate();
    double getValeur();
    Attribut getAttribut();

protected:

    time_t date;
    double valeur;
    Attribut attribut;
};
