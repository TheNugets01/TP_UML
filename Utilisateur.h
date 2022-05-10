#include <string>
#include <iostream>
using namespace std;

class Utilisateur
{

public:
    
    Utilisateur (string id, string mdp);
    virtual ~Utilisateur ( );
    
    int userID;
    string identifiant;
    string motDePasse;
protected:


};

