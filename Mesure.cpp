#include <iostream>
using namespace std;


#include "Mesure.h"

Mesure::Mesure (time_t d, double v, Attribut a):date(d),valeur(v),attribut(a)
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