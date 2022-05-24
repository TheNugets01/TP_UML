using namespace std;
#include <string>
#include <vector>
#include <iostream>

#include "Capteur.h"
#include "Position.h"

class Services
{

public:
    
    Services ();
    virtual ~Services ( );
    double moyenneQualiteAir(Position p, double rayon, string dateDebut, string dateFin);
    double moyenneQualiteAir(Position p, double rayon, string moment);
    vector<Capteur> identifierCapteursNonFiables();

    static vector<Capteur> initCapteur(istream& str );
};

