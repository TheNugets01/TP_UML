using namespace std;
#include <ctime>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include <fstream>
using std::fstream;

#include "Services.h"

#define DAY 86400

Services::Services()
{
}


double Services::moyenneQualiteAir(Position p, double rayon, time_t jour)
{
    int nbCapteurs = 0;
    double moyenne = 0.0;

    // fstream cap;
    // fstream source;
    // cap.open("sensors.csv");
    // source.open("measurements.csv");
    // vector<Capteur> capteurs=initCapteurs(cap);

    // initMesure(source,capteurs);
    // cerr<<"taille liste capteurs "<<capteurs.size()<<endl;
    for (Capteur capteur : capteurs)
    {
        if (capteur.getPosition().estDansLaZone(p, rayon))
        {
            // cout<<"*****dans la zone"<<endl;
            nbCapteurs++;
            moyenne += capteur.getATMO(jour);
        }
    }
    // cout<<"nb capCteurs "<<nbCapteurs<<endl;
    moyenne = moyenne / (nbCapteurs);

    if (isnan(moyenne))
    {
        cerr << "-!!!!!!!!!-Moyenne incalculable, pas de mesures pour la zone ou la date choisie-!!!!!!!!!-" << endl;
        cout << endl;
        return 0;
    }
    return round(moyenne);
}

double Services::moyenneQualiteAir(Position p, double rayon, time_t dateDebut, time_t dateFin)
{
    double moyenne = 0.0;
    int nbJours = 0;

    for (time_t t = dateDebut; t <= dateFin; t += DAY)
    {
        nbJours++;
        moyenne = moyenne + moyenneQualiteAir(p, rayon, t);
    }
    moyenne = moyenne / nbJours;

    if (isnan(moyenne))
    {
        cerr << "-!!!!!!!!!-Moyenne incalculable, pas de mesures pour la zone ou la date choisie-!!!!!!!!!-" << endl;
        cout << endl;
        return 0;
    }
    return round(moyenne);
}

// lister les capteurs non fiables detectés entre deux dates
vector<Capteur> Services::identifierCapteursNonFiables(time_t dateDebut, time_t dateFin)
{
    vector<Capteur> liste_non_fiables;
    const double rayon = 2.5;
    double moyenne = 0;
    double moyenneZone = 0;

    for (Capteur capteur : capteurs)
    {

        // cout<<"on a un capteur"<<endl;
        moyenne = capteur.getMoyATMO(dateDebut, dateFin);
        //cout << "atmo: " << moyenne << endl
        //     << "\n";
        moyenneZone = moyenneQualiteAir(capteur.getPosition(), rayon, dateDebut, dateFin);
        //cout << "zone: " << moyenneZone << "\n";
        if (abs(moyenne - moyenneZone) > 1.5)
        {
            // cout<<"pushed"<<endl;
            liste_non_fiables.emplace_back(capteur);
        }
        else
        {
            for (time_t day = dateDebut; day <= dateFin; day += DAY)
            {
                if (capteur.getATMO(day) < 0.75 * moyenne || capteur.getATMO(day) > 1.5 * moyenne)
                {

                    liste_non_fiables.emplace_back(capteur);
                    break;
                }
            }
        }
        // if(!pushed)cout<<"unpushed"<<endl;
    }

    return liste_non_fiables;
}

bool c(pair<double, Position> a, pair<double, Position> b)
{
    return a.first < b.first;
}
vector<pair<double, Position>> Services::zoneMemeQualiteAir(Capteur capteurRef, time_t debut, time_t fin)
{

    vector<pair<double, Position>> positions;

    if ((fin != 0 && difftime(fin, debut) < 0.f))
    {
        return positions;
    }

    double reference = capteurRef.getMoyATMO(debut, fin);
    double currentValue, diff;

    for (Capteur cpt : capteurs)
    {
        currentValue = cpt.getMoyATMO(debut, fin); // get valeur capteur
        diff = abs(reference - currentValue);
        positions.push_back(std::make_pair(diff, cpt.getPosition()));
    }
    // trier la liste par la difference de mesure
    std::sort(positions.begin(), positions.end(), c);
    return positions;
}

void Services::afficherCapteurs()
{

    for (auto capteur : capteurs)
    {
        cout << capteur.getID() << " : (" << capteur.getPosition().longitude << "," << capteur.getPosition().latitude << ")" << endl;
    }
}

Capteur Services::getCapteurByID(string ID)
{
    Capteur capteur = Capteur("Capteur inexistant", Position(44, 0));
    for (auto cpt : capteurs)
    {
        if (cpt.getID() == ID)
        {
            return cpt;
        }
    }
    return capteur;
}

void Services::setCapteurs(vector<Capteur> c)
{
    // cout<<c.size();
    capteurs = c;
}

vector<Capteur> Services::getCapteurs()
{
    return capteurs;
}