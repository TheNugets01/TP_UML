#include "Utilisateur.h"

static int idCourant = 0;

Utilisateur::Utilisateur (string id, string mdp)
{
    userID = idCourant;
    idCourant++;
    identifiant = id;
    motDePasse = mdp;
} 


Utilisateur::~Utilisateur ( )
{

}