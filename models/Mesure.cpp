#include <iostream>
using namespace std;


#include "Mesure.h"

Mesure::Mesure (time_t d, string sID,Attribut a, double v):date(d),sensorID(sID),attribut(a),valeur(v)
{} 

Mesure::~Mesure ( )
{}

time_t Mesure::getDate()
{
    return date;
}

double Mesure::getValeur()
{
    return valeur;
}

Attribut Mesure::getAttribut()
{
    return attribut;
}