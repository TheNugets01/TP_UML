#include <string>
#include <unordered_map>
#include <vector>
#include "Position.h"
#include "Mesure.h"
using namespace std;

class Capteur
{
public:
    
    Capteur (string ID, Position pos);
    virtual ~Capteur ( );
    int getATMO(string date);
    int maxi(int, int, int, int);
    int index(double valeur, double palier1, double palier2, double palier3, double palier4, double palier5, double palier6, double palier7, double palier8, double palier9);

protected:

string sensorID;
Position position;
unordered_map<string, vector<Mesure>> mesures;
};
