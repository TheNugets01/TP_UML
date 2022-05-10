#include <string>
using namespace std;

class Mesure
{
public:
    
    Mesure (string date, double valeur);
    virtual ~Mesure ( );

protected:

string date;
double valeur;
};
