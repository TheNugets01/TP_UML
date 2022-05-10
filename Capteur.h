#include <string>
using namespace std;

class Capteur
{
public:
    
    Capteur (char * unDepart, char * uneArrivee, char * unTransport);
    virtual ~Capteur ( );

protected:

int sensorID;
};
