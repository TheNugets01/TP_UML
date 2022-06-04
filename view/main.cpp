#include <iostream>
#include <fstream>
#include <cstring>
#include <stdio.h>
#include <vector>
#include <time.h>
#include <string>
#include <vector>

#include "../controller/ServiceInit.h"
#include "../models/Utilisateur.h"
#include "../tests/Test.h"
#include "../util/Timer.h"

#define TAILLEBUFFER 100
#define VIDEBUFFERCLAVIER()                       \
    char ch;                                      \
    while ((ch = getchar() != '\n') && ch != EOF) \
        ;

using namespace std;

void AfficherMenu()
{
    cout << endl;
    cout << "=============================== AIR WATCHER ===============================" << endl;
    cout << "Bonjour et bienvenue dans l'application AirWatcher" << endl;
    cout << "Ceci est une version Beta, nous vous proposons donc pas toutes les fonctionalites" << endl;
    cout << "Veuillez choisir parmis les suivantes :" << endl
         << endl;
    ;
    cout << "1 : Calcul de la moyenne de qualité de l'air dans une zone donnee" << endl;
    cout << "2 : Verifier le bon fonctionnement des capteurs" << endl;
    cout << "3 : Trouver les zones produisant des données similaires" << endl;
    cout << "4 : Afficher la liste de tous les capteurs" << endl;
    cout << "5 : Executer les tests unitaires " << endl;
    cout << "q : Quitter" << endl;
}

char *Saisi()
// Algorithme : Permet de saisir une chaine de caractère au clavier et de la ranger dans une zone alloué dynamiquement
{
    char unMot[TAILLEBUFFER];
    cin >> unMot;

    char *leMot = new char[strlen(unMot) + 1];
    strcpy(leMot, unMot);

    if (strcmp(leMot, "-1") != 0)
    {
        VIDEBUFFERCLAVIER();
    }

    return leMot;
} //----- Fin de Saisi

void DisplayAlgorithmRuntime(double duration)
{
    string msg = "L'algorithme s'est executé en ";
    msg += to_string(duration);
    msg += " millisecondes.\n";
    cout<<msg;
}

int main()
{
    ServiceInit controlleur;
    controlleur.init();

    // tous les capteurs
    Services *service = new Services(controlleur.getServices());

    AfficherMenu();
    char lecture;
    cin >> lecture;
    while (lecture != 'q')
    {
        if (lecture == '1')
        {
            double resultat = 0.0;
            double latitude = 0.0, longitude = 0.0, rayon = 0.0;
            VIDEBUFFERCLAVIER();
            cout << "Quelle est la zone qui vous interesse ?" << endl;
            while (1)
            {
                cout << "Latitude ?" << endl
                     << ">> ";
                if (cin >> latitude)
                {
                    break;
                }
                else
                {
                    cout << "-----Veuillez rentrer une latitude valide------" << endl;
                    cout << endl;
                    cin.clear();
                    while (cin.get() != '\n')
                        ; // empty loop
                }
            }

            while (1)
            {
                cout << "Longitude ?" << endl
                     << ">> ";
                if (cin >> longitude)
                {
                    break;
                }
                else
                {
                    cout << "-----Veuillez rentrer une longitude valide------" << endl;
                    cout << endl;
                    cin.clear();
                    while (cin.get() != '\n')
                        ; // empty loop
                }
            }

            while (1)
            {
                cout << "Rayon ?" << endl
                     << ">> ";
                if (cin >> rayon)
                {
                    break;
                }
                else
                {
                    cout << "-----Veuillez rentrer un rayon valide------" << endl;
                    cout << endl;
                    cin.clear();
                    while (cin.get() != '\n')
                        ; // empty loop
                }
            }

            cout << "Choisissez : " << endl;
            cout << "1 : Pour une date precise" << endl;
            cout << "2 : Pour une periode" << endl;
            cin >> lecture;
            string sdate;
            time_t date;
            if (lecture == '1')
            {
                cout << "A quelle date doit on calculer la moyenne (YYYY-MM-DD) ?" << endl;
                cin >> sdate;
                tm *tf = new tm();
                tf->tm_year = stoi(sdate.substr(0, 4)) - 1900;
                tf->tm_mon = stoi(sdate.substr(5, 2)) - 1;
                tf->tm_mday = stoi(sdate.substr(8, 2));
                date = mktime(tf);
                Timer t;
                t.Start();
                resultat = service->moyenneQualiteAir(*(new Position(latitude, longitude)), rayon, date);
                double duration = t.GetDuration();
                DisplayAlgorithmRuntime(duration);
            }
            else if (lecture == '2')
            {
                cout << "Quelle est la date de debut (YYYY-MM-DD) ?" << endl;
                cin >> sdate;
                tm *tf = new tm();
                tf->tm_year = stoi(sdate.substr(0, 4)) - 1900;
                tf->tm_mon = stoi(sdate.substr(5, 2)) - 1;
                tf->tm_mday = stoi(sdate.substr(8, 2));
                date = mktime(tf);

                string sdate2;
                time_t date2;
                cout << "Quelle est la date de fin (YYYY-MM-DD) ?" << endl;
                cin >> sdate2;
                tf->tm_year = stoi(sdate2.substr(0, 4)) - 1900;
                tf->tm_mon = stoi(sdate2.substr(5, 2)) - 1;
                tf->tm_mday = stoi(sdate2.substr(8, 2));
                date2 = mktime(tf);
                Position pos = Position(latitude, longitude);
                Timer t;
                t.Start();
                resultat = service->moyenneQualiteAir(pos, rayon, date, date2);

                double duration = t.GetDuration();
                DisplayAlgorithmRuntime(duration);
            }
            if (resultat != 0)
            {
                cout << "La moyenne de qualite de l'air pour votre zone est la suivante : " << resultat << endl;
            }
        }
        else if (lecture == '2')
        {
            vector<Capteur> capteurs;
            string sdate;
            time_t date;
            cout << "Quelle est la date de debut (YYYY-MM-DD) ?" << endl;
            cin >> sdate;
            tm *tf = new tm();
            tf->tm_year = stoi(sdate.substr(0, 4)) - 1900;
            tf->tm_mon = stoi(sdate.substr(5, 2)) - 1;
            tf->tm_mday = stoi(sdate.substr(8, 2));
            date = mktime(tf);

            string sdate2;
            time_t date2;
            cout << "Quelle est la date de fin (YYYY-MM-DD) ?" << endl;
            cin >> sdate2;
            tf->tm_year = stoi(sdate2.substr(0, 4)) - 1900;
            tf->tm_mon = stoi(sdate2.substr(5, 2)) - 1;
            tf->tm_mday = stoi(sdate2.substr(8, 2));
            date2 = mktime(tf);

            Timer t;
            t.Start();
            capteurs = service->identifierCapteursNonFiables(date, date2);
            double duration = t.GetDuration();
            DisplayAlgorithmRuntime(duration);

            cout << "Liste des capteurs non fiables : " << endl;
            for (size_t i = 0; i < capteurs.size(); ++i)
            {
                cout << capteurs[i].getID() << "; ";
            }
        }
        else if (lecture == '3')
        {
            string capteurID;
            while (1)
            {

                cout << "Veuillez entrer l'identifiant du capteur sous-la forme SensorX avec X numéro du capteur " << endl;
                ;
                cin >> capteurID;
                capteurID = service->getCapteurByID(capteurID).getID();
                if (capteurID != "Capteur inexistant")
                {
                    break;
                }
                else
                {
                    cout << "-----Veuillez rentrer un capteur valide de numéro entre 0 et 99 ------" << endl;
                    cout << endl;
                    cin.clear();
                    while (cin.get() != '\n')
                        ; // empty loop
                }
            }

            string sdate;
            time_t date;
            cout << "Quelle est la date de debut (YYYY-MM-DD) ?" << endl;
            cin >> sdate;
            tm *tf = new tm();
            tf->tm_year = stoi(sdate.substr(0, 4)) - 1900;
            tf->tm_mon = stoi(sdate.substr(5, 2)) - 1;
            tf->tm_mday = stoi(sdate.substr(8, 2));
            date = mktime(tf);

            string sdate2;
            time_t date2;
            cout << "Quelle est la date de fin (YYYY-MM-DD) ?" << endl;
            cin >> sdate2;
            tf->tm_year = stoi(sdate2.substr(0, 4)) - 1900;
            tf->tm_mon = stoi(sdate2.substr(5, 2)) - 1;
            tf->tm_mday = stoi(sdate2.substr(8, 2));
            date2 = mktime(tf);

            Timer t;
            t.Start();
            vector<pair<double, Position>> zones = service->zoneMemeQualiteAir(service->getCapteurByID(capteurID), date, date2);
            double duration = t.GetDuration();
            cout << endl;
            cout << "Voici la liste des centres des zones similaires à la zone du capteur choisi " << endl;
            cout << endl;
            int i = 0;
            for (auto it : zones)
            {
                if (i == 10)
                {
                    break;
                }
                cout << "Zone " << i << ": (" << it.second.latitude << ", " << it.second.longitude << ")" << endl;
                i++;
            }
            DisplayAlgorithmRuntime(duration);
        }
        else if (lecture == '4')
        {
            service->afficherCapteurs();
        }
        else if (lecture == '5')
        {
            Test *test = new Test(service);
            test->runTests();
        }
        else
        {
            cout << "Je n'ai pas compris veuillez recommencer !" << endl;
        }
        VIDEBUFFERCLAVIER();
        cout << endl;
        cout << endl;
        cout << endl;
        AfficherMenu();
        cin >> lecture;
    }
    return 0;
}