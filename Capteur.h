#include <string>
using namespace std;

#include "Position.h"
class Capteur
{
public:
    
    Capteur (string ID, Position p);
    virtual ~Capteur ( );
    double getATMO(string date);
    Position getPosition();
    
protected:

string sensorID;
Position position;

};
