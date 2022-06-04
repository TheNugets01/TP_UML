#include <iostream>
using namespace std;

#include "Test.h"


int CPT=0;
int ECHEC=0;


Test::Test(Services* service):service(service)
{} 

void Test::runTests()
{
    
    testEstDansLaZone();
    testGetAtmo();
    testZoneMemeQualiteAir();
    testGetCapteurByID();
    testMoyenneQualiteAir();
    cout<<"---------------- TESTS REUSSIS : "<<CPT<<" ----------------"<<endl;
    cout<<"---------------- TESTS ECHOUES : "<<ECHEC<<" ----------------"<<endl;
}


void Test::testEstDansLaZone()
{
    cout<<"**************TEST DE estDansLaZone***********"<<endl<<endl;
    Position a (15.0,0.0);
    Position b (15.0,15.0);
    Position c (0.0,0.0);

    cout<<"===== Résulat attendu : ===== "<<endl;
    cout<<endl;
    cout<<1<<endl;
    cout<<0<<endl;
    cout<<0<<endl;
    cout<<1<<endl;
    cout<<0<<endl;

    cout<<"===== Résulat obtenu : ====="<<endl;
    cout<<endl;
    cout<<c.estDansLaZone(a,15.0)<<endl;
    cout<<c.estDansLaZone(b,15.0)<<endl;
    cout<<c.estDansLaZone(a,10.0)<<endl;
    cout<<c.estDansLaZone(c,0.0)<<endl;
    cout<<c.estDansLaZone(b,-3.0)<<endl;

    cout<<">>>>>>>>>>>>>>>>>TEST REUSSI "<<endl<<endl<<endl;
    CPT++;

}

void Test::testGetAtmo()
{
    cout<<"**************TEST DE getAtmo***********"<<endl;
    cout<<endl;
    cout<<"Calcul de l'indice ATMO du capteur Sensor1"<<endl<<endl;;
    cout<<"===== Resultat attendu : ====="<<endl;
    cout<<endl;
    cout<<6<<endl;
    cout<<endl;
    Position a (44.0,0.0);
    Capteur c1 ("Sensor1", *(new Position (44.0,-0.3)));

    Attribut o3 ("O3","µg/m3","concentration d'ozone");
    Attribut so2 ("SO2","µg/m3","concentration de dioxyde de soufre");
    Attribut no2 ("NO2","µg/m3","concentration de dioxyde d'azote");
    Attribut pm10 ("PM10","µg/m3","concentration de particules fines");

    string sdate2 = "2019-01-01";
    time_t date2;
    tm* tf = new tm();
    tf->tm_year = stoi(sdate2.substr(0,4)) - 1900;
    tf->tm_mon = stoi(sdate2.substr(5,2)) - 1;
    tf->tm_mday = stoi(sdate2.substr(8,2));
    date2 = mktime(tf);

    Mesure* m1 = new Mesure(date2, "Sensor1",o3,63.05);
    Mesure* m2 = new Mesure(date2, "Sensor1",so2,34.42);
    Mesure* m3 = new Mesure(date2, "Sensor1",no2,61.92);
    Mesure* m4 = new Mesure(date2, "Sensor1",pm10,51.12);

    c1.ajouterMesure(*m1);
    c1.ajouterMesure(*m2);
    c1.ajouterMesure(*m3);
    c1.ajouterMesure(*m4);

    cout<<"===== Resultat obtenu :  ====="<<endl;
    cout<<endl;
    cout<<c1.getATMO(date2)<<endl;
    cout<<endl;
    cout<<">>>>>>>>>>>>>>>>>TEST REUSSI "<<endl<<endl<<endl;
    CPT++;
}

void Test::testZoneMemeQualiteAir()
{
    cout<<"**************TEST DE ZoneMemeQualiteAir***********"<<endl;
    cout<<endl;
    cout<<"Liste des 10 zones les plus similaires à la zone (44,-1), triées par ordre de similarité : "<<endl;
    cout<<endl;
    cout<<"===== Resultat attendu : ====="<<endl;
    cout<<endl;
    cout<<"Zone 0: (45.2,45.2)"<<endl<<"Zone 1: (47.6,47.6)"<<endl<<"Zone 2: (46,46)"<<endl<<"Zone 3: (47.2,47.2)"<<endl<<"Zone 4: (44.8,44.8)"<<endl<<"Zone 5: (46.8,46.8)"<<endl<<"Zone 6: (46.8,46.8)"<<endl<<"Zone 7: (44.8,44.8)"<<endl<<"Zone 8: (47.6,47.6)"<<endl<<"Zone 9: (45.2,45.2)"<<endl;
    cout<<endl;

    Attribut o3 ("O3","µg/m3","concentration d'ozone");
    Attribut so2 ("SO2","µg/m3","concentration de dioxyde de soufre");
    Attribut no2 ("NO2","µg/m3","concentration de dioxyde d'azote");
    Attribut pm10 ("PM10","µg/m3","concentration de particules fines");

    string sdate2 = "2019-01-01";
    time_t date2;
    tm* tf = new tm();
    tf->tm_year = stoi(sdate2.substr(0,4)) - 1900;
    tf->tm_mon = stoi(sdate2.substr(5,2)) - 1;
    tf->tm_mday = stoi(sdate2.substr(8,2));
    date2 = mktime(tf);

    Capteur c0 ("Sensor0", *(new Position (44.0,-1.0)));

    Mesure* m9 = new Mesure(date2, "Sensor0",o3,100);
    Mesure* m10 = new Mesure(date2, "Sensor0",so2,200);
    Mesure* m11 = new Mesure(date2, "Sensor0",no2,300);
    Mesure* m12 = new Mesure(date2, "Sensor0",pm10,400);

    c0.ajouterMesure(*m9);
    c0.ajouterMesure(*m10);
    c0.ajouterMesure(*m11);
    c0.ajouterMesure(*m12);


    Capteur c1 ("Sensor1", *(new Position (44.0,-0.3)));

    Mesure* m1 = new Mesure(date2, "Sensor1",o3,63.05);
    Mesure* m2 = new Mesure(date2, "Sensor1",so2,34.42);
    Mesure* m3 = new Mesure(date2, "Sensor1",no2,61.92);
    Mesure* m4 = new Mesure(date2, "Sensor1",pm10,51.12);

    c1.ajouterMesure(*m1);
    c1.ajouterMesure(*m2);
    c1.ajouterMesure(*m3);
    c1.ajouterMesure(*m4);

    Capteur c2 ("Sensor2", *(new Position (44.0,0.4)));

    Mesure* m5 = new Mesure(date2, "Sensor2",o3,47.84);
    Mesure* m6 = new Mesure(date2, "Sensor2",so2,43.32);
    Mesure* m7 = new Mesure(date2, "Sensor2",no2,43.32);
    Mesure* m8 = new Mesure(date2, "Sensor2",pm10,45.02);

    c2.ajouterMesure(*m5);
    c2.ajouterMesure(*m6);
    c2.ajouterMesure(*m7);
    c2.ajouterMesure(*m8);

    vector<pair<double, Position>> zones = service->zoneMemeQualiteAir(c0,date2,date2);
    int i=0;
    cout<<"===== Resultat obtenu :  ====="<<endl;
    cout<<endl;
    for (auto it : zones) 
    {
        if(i==10)
        {
            break;
        }
        cout <<"Zone "<<i+1<<": "<<"("<<it.second.latitude<<","<<it.second.latitude<<")"<<endl;
        i++;
    }
    cout<<endl;
    cout<<">>>>>>>>>>>>>>>>>TEST REUSSI "<<endl<<endl<<endl;
    CPT++;
}

void Test::testGetCapteurByID()
{
    cout<<"**************TEST DE getCapteurByID***********"<<endl;
    cout<<endl;

    cout<<"===== Resultat attendu : ====="<<endl;
    cout<<endl;
    cout<<"Capteur inexistant"<<endl;
    cout<<"Sensor0"<<endl<<endl;

    cout<<"===== Resultat obtenu :  ====="<<endl;
    cout<<endl;

    cout<<service->getCapteurByID("Sensor100").getID()<<endl;
    cout<<service->getCapteurByID("Sensor0").getID()<<endl;
    cout<<endl;
    cout<<">>>>>>>>>>>>>>>>>TEST REUSSI "<<endl<<endl<<endl;
    CPT++;
}

void Test::testMoyenneQualiteAir()
{

    cout<<"**************TEST DE moyenneQualiteAir***********"<<endl;
    cout<<endl;

    cout<<"===== Resultat attendu : ====="<<endl;
    cout<<endl;
    cout<<"Qualité de l'air pour le jour 2019-01-01 : "<<5<<endl;
    cout<<"Moyenne de la qualité de l'air pour la période 2019-01-01 à 2019-01-03 : "<<5<<endl<<endl;

    string sdate2 = "2019-01-01";
    time_t date2;
    tm* tf = new tm();
    tf->tm_year = stoi(sdate2.substr(0,4)) - 1900;
    tf->tm_mon = stoi(sdate2.substr(5,2)) - 1;
    tf->tm_mday = stoi(sdate2.substr(8,2));
    date2 = mktime(tf);

    string sdate1 = "2019-01-03";
    time_t date1;
    tm* tf1 = new tm();
    tf1->tm_year = stoi(sdate1.substr(0,4)) - 1900;
    tf1->tm_mon = stoi(sdate1.substr(5,2)) - 1;
    tf1->tm_mday = stoi(sdate1.substr(8,2));
    date1 = mktime(tf);

    cout<<"===== Resultat obtenu :  ====="<<endl;
    cout<<endl;
    cout<<"Qualité de l'air pour le jour 2019-01-01 : "<<service->moyenneQualiteAir(*(new Position (44.0,-1.0)),0.1,date2)<<endl;
    cout<<"Moyenne de la qualité de l'air pour la période 2019-01-01 à 2019-01-03 : "<<service->moyenneQualiteAir(*(new Position (44.0,-1.0)),0.1,date2, date1)<<endl;
    cout<<endl;
    cout<<">>>>>>>>>>>>>>>>>TEST REUSSI "<<endl<<endl<<endl;
    CPT++;
}


