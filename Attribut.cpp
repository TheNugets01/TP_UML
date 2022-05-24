#include <iostream>
using namespace std;


#include "Attribut.h"

Attribut::Attribut (string id, string u, string desc):id(id),unite(u),description(desc)
{} 


Attribut::~Attribut ( )
{}

string Attribut::getID()
{
    return id;
}