#include <string>
#include "Position.h"
using namespace std;

#include "Position.h"
class Capteur
{
public:
    
    Capteur (string ID, Position pos);
    virtual ~Capteur ( );
    double getATMO(string date);
    Position getPosition();
    double getMoyenneATMO();
    
protected:

string sensorID;
Position position;
};
