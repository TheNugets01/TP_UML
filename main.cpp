#include <iostream>
#include <cstring>
#include <vector>

#include "Utilisateur.h"
#include "Capteur.h"

#include "Utilisateur.h"
#include "Position.h"

using namespace std;

int main()
{
    Utilisateur *U1 = new Utilisateur("hugo","mdp");
    Utilisateur *U2 = new Utilisateur("octave","oui");
    cout << U1->userID << endl;
    cout << U2->userID << endl;

    Position *p1 = new Position(45.778912,4.871650);
    Position *p2 = new Position(45.776199,4.871971);
    cout << p1->estDansLaZone(*p2,10.0) << endl;
    cout << p1->estDansLaZone(*p2,0.001) << endl;

    return 0;
}