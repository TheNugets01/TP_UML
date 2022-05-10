#include <iostream>
using namespace std;



#include "Capteur.h"
#include "Position.h"

Capteur::Capteur (string ID, Position pos):sensorID(ID),position(pos)
{} 


Capteur::~Capteur ( )
{}

double Capteur::getATMO(string date)
{

}

double Capteur::getMoyenneATMO()
{

}

Position Capteur::getPosition()
{
    return position;
}