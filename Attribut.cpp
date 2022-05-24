#include <iostream>
using namespace std;


#include "Attribut.h"

Attribut::Attribut (string u, string desc):unite(u),description(desc)
{} 


Attribut::~Attribut ( )
{}

string Attribut::getID()
{
    return id;
}