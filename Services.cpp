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


double Services::moyenneQualiteAir(Position p, double rayon, string jour)
{
    int nbCapteurs=0;
    double moyenne=0;
    vector<Capteur> listeCapteurs;//RECUPERER LES LISTES DE CAPTEURS INITIALISEE  PARTIR DU CSV
    for (auto capteur = listeCapteurs.begin(); capteur != listeCapteurs.end(); ++capteur)
    {
        if((*capteur).getPosition().estDansLaZone(p,rayon))
        {
            nbCapteurs++;
            moyenne += (*capteur).getATMO(jour);//A CODER : on met que le jour ou quoi ?
        }
    }
    moyenne= moyenne/nbCapteurs;
    return moyenne;
}

/*
double Services::moyenneQualiteAir(Position p, double rayon, string dateDebut, string dateFin)
{
    int nbCapteurs=0;
    double moyPeriode=0;
    double moyenne=0;
    vector<Capteur> listeCapteurs;//RECUPERER LES LISTE DE CAPTEURS INITIALISEE  PARTIR DU CSV
    for (auto capteur = listeCapteurs.begin(); capteur != listeCapteurs.end(); ++capteur)
    {
        if((*capteur).getPosition().estDansLaZone(p,rayon))
        {
            nbCapteurs++;
            int nbJours=0;
            
            moyenne += (*capteur).getATMO(moment);//A CODER : on met que le jour ou quoi ?
        }
    }

}


vector<Capteur> Services::identifierCapteursNonFiables(string jour)
{
   vector<Capteur> listeCapteurs;
    for (auto capteur = listeCapteurs.begin(); capteur != listeCapteurs.end(); ++capteur)
    {
        double moyenne=(*capteur).getMoyenneATMO();
        double rayon=0.5;
        double moyenneZone=moyenneQualiteAir((*capteur).getPosition(),rayon,jour);
        if(moyenne<0.5*moyenneZone || moyenne>2*moyenne)//A REVOIR S
        {

        }

    }
}*/