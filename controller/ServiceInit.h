#pragma once
#include <string>
#include <vector>

#include "../models/Capteur.h"
#include "../models/Attribut.h"
#include "../models/Services.h"


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
