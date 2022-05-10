using namespace std;
#include <iostream>
#include <string>
#include <vector>

#include "Services.h"


Services::Services ()
{

} 


Services::~Services ( )
{

}

double Services::moyenneQualiteAir(Position p, double rayon, string dateDebut, string dateFin)
{
    int nbCapteurs=0;
    int moyenne=0;
    vector<Capteur> listeCapteurs;
    for (auto capteur = listeCapteurs.begin(); capteur != listeCapteurs.end(); ++capteur)
    {
        if((*capteur).getPosition().estDansLaZone(p,rayon))
        {

        }
    }

    
}
double Services::moyenneQualiteAir(Position p, double rayon, string moment)
{

}
vector<Capteur> Services::identifierCapteursNonFiables()
{
    
}