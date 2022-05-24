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
    double moyenneQualiteAir(Position p, double rayon, time_t dateDebut, time_t dateFin);
    double moyenneQualiteAir(Position p, double rayon, time_t jour);
    vector<Capteur> initCapteur(istream& str);
    vector<Capteur> identifierCapteursNonFiables();

};

