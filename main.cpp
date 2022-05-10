#include <iostream>
#include <cstring>
#include <vector>

#include "Utilisateur.h"
#include "Capteur.h"

using namespace std;

int main()
{
    Utilisateur *U1 = new Utilisateur("hugo","mdp");
    Utilisateur *U2 = new Utilisateur("octave","oui");
    cout << U1->userID << endl;
    cout << U2->userID << endl;


    return 0;
}