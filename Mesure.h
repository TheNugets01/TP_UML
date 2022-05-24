#include <string>
#include "Attribut.h"
using namespace std;

class Mesure
{
public:
    
    Mesure (string d, double v, Attribut a);
    virtual ~Mesure ( );

    string date;
    double valeur;
    Attribut attribut;
protected:

};
