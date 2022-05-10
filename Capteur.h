#include <string>
#include "Position.h"
using namespace std;

class Capteur
{
public:
    
    Capteur (string ID, Position pos);
    virtual ~Capteur ( );
    double getATMO(string date);

protected:

string sensorID;
Position position;
};
