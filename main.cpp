#include <iostream>
#include <cstring>
#include <stdio.h>
#include <vector>
#include <time.h>
#include <string>
#include <vector>

#include "Utilisateur.h"
#include "Capteur.h"
#include "Services.h"

#define TAILLEBUFFER 100
#define VIDEBUFFERCLAVIER() char ch; while( (ch = getchar() != '\n') && ch != EOF );

using namespace std;

void AfficherMenu()
{
    cout << "Bonjour et bienvenue dans l'application AirWatcher" << endl;
    cout << "Ceci est une version Beta, nous vous proposons donc uniquement deux fonctionalites" << endl;
    cout << "Veuillez choisir parmis les suivantes :" << endl;
    cout << "1 : Calcul de la moyenne de qualité de l'air dans une zone donnee" << endl;
    cout << "2 : Verifier le bon fonctionnement des capteurs" << endl;
    cout << "q : Quitter" << endl;
}

char * Saisi( )
// Algorithme : Permet de saisir une chaine de caractère au clavier et de la ranger dans une zone alloué dynamiquement
{
    char unMot[TAILLEBUFFER];
    cin >> unMot;

    char * leMot = new char[strlen(unMot)+1];
    strcpy( leMot , unMot );
    
    if(strcmp(leMot,"-1") != 0)
    {
        VIDEBUFFERCLAVIER();
    }
    
    return leMot;
} //----- Fin de Saisi

int main()
{
    Services *service = new Services();
    AfficherMenu();
    char lecture;
    cin >> lecture;
    while (lecture != 'q')
    {
        if (lecture== '1')
        {
            double resultat = 0.0;
            double latitude =0.0, longitude=0.0, rayon=0.0;
            VIDEBUFFERCLAVIER();
            cout << "Quelle est la zone qui vous interesse ?" << endl;
            cout << "Latitude ?" << endl << ">> ";
            cin >> latitude;
            cout << "Longitude ?" << endl << ">> ";
            cin >> longitude;
            cout << "Rayon ?" << endl << ">> ";
            cin >> rayon;
            cout << "Choisissez : " << endl;
            cout << "1 : Pour une date precise" << endl;
            cout << "2 : Pour une periode" << endl;
            cin >> lecture;
            string sdate;
            time_t date;
            if(lecture =='1')
            {
                cout << "A quelle date doit on calculer la moyenne (YYYY-MM-DD) ?" << endl;
                cin >> sdate;
                tm* tf = new tm();
                tf->tm_year = stoi(sdate.substr(0,4)) - 1900;
                tf->tm_mon = stoi(sdate.substr(5,2)) - 1;
                tf->tm_mday = stoi(sdate.substr(8,2));
                date = mktime(tf);
                resultat = service->moyenneQualiteAir(*(new Position(latitude,longitude)),rayon,date);
            }
            else if(lecture =='2')
            {
                cout << "Quelle est la date de debut (YYYY-MM-DD) ?" << endl;
                cin >> sdate;
                tm* tf = new tm();
                tf->tm_year = stoi(sdate.substr(0,4)) - 1900;
                tf->tm_mon = stoi(sdate.substr(5,2)) - 1;
                tf->tm_mday = stoi(sdate.substr(8,2));
                date = mktime(tf);

                string sdate2;
                time_t date2;
                cout << "Quelle est la date de fin (YYYY-MM-DD) ?" << endl;
                cin >> sdate2;
                tf->tm_year = stoi(sdate2.substr(0,4)) - 1900;
                tf->tm_mon = stoi(sdate2.substr(5,2)) - 1;
                tf->tm_mday = stoi(sdate2.substr(8,2));
                date2 = mktime(tf);
                //resultat = service->moyenneQualiteAir(*(new Position(latitude,longitude)),rayon,date,date2);
            }
            cout << "La moyenne de qualite de l'air pour votre zone est la suivante : " << resultat << endl;
        }
        else if (lecture== '2')
        {
            vector<Capteur> capteurs;
            string sdate;
            time_t date;
            cout << "Quelle est la date de debut (YYYY-MM-DD) ?" << endl;
            cin >> sdate;
            tm* tf = new tm();
            tf->tm_year = stoi(sdate.substr(0,4)) - 1900;
            tf->tm_mon = stoi(sdate.substr(5,2)) - 1;
            tf->tm_mday = stoi(sdate.substr(8,2));
            date = mktime(tf);

            string sdate2;
            time_t date2;
            cout << "Quelle est la date de fin (YYYY-MM-DD) ?" << endl;
            cin >> sdate2;
            tf->tm_year = stoi(sdate2.substr(0,4)) - 1900;
            tf->tm_mon = stoi(sdate2.substr(5,2)) - 1;
            tf->tm_mday = stoi(sdate2.substr(8,2));
            date2 = mktime(tf);

            //capteurs = identifierCapteursNonFiables(date,date2);
            cout << "Voila la liste des capteurs non fiables : " << endl;
            for (size_t i = 0; i < capteurs.size(); ++i) 
            {
                cout << capteurs[i].getID() << "; ";
            }
        }
        else
        {
            cout << "Je n'ai pas compris veuillez recommencer !" << endl;
        }
        VIDEBUFFERCLAVIER();
        cout << endl; cout << endl; cout << endl;
        AfficherMenu();
        cin >> lecture;
    }
    return 0;
}