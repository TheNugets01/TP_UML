#include <string>
using namespace std;

class Utilisateur : public Trajet
{

public:
    
    Utilisateur (char * unDepart, char * uneArrivee, char * unTransport);
    virtual ~Utilisateur ( );

protected:

int userID;
String identifiant;
String mdp;
};

