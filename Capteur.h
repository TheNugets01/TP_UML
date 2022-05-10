#include <string>
using namespace std;

class Capteur
{
public:
    
    Capteur (string ID, int lat, int log);
    virtual ~Capteur ( );
    double getATMO(string date);

protected:

string sensorID;
int Lat;
int Log;
};
