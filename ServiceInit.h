
#include <string>
#include <vector>
#include <iostream>

#include "Capteur.h"
#include "Attribut.h"
#include "Services.h"

using namespace std;

class ServiceInit
{

public:
    void init();
    void initCapteurs(vector<Capteur> &capteurs, istream &str);
    void initAttributes(vector<Attribut> &attributs, istream &str);
    void initMesures(vector<Capteur> &capteurs, vector<Attribut> &attributs, istream &str);
    Services getServices();
private:
    Services service_capteurs;
};
