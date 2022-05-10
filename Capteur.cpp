#include <iostream>
using namespace std;



#include "Capteur.h"
#include "Position.h"

Capteur::Capteur (string ID, Position p):sensorID(ID),Position(p)
{} 


Capteur::~Capteur ( )
{}

double Capteur::getATMO(string date)
{

}

Position Capteur::getPosition()
{
    return position;
}