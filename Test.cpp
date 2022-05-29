#include <iostream>
using namespace std;

#include "Test.h"



Test::Test()
{} 

// estDansLaZone() tests

void Test::testEstDansLaZone()
{
    cout<<"**************Test de estDansLaZone***********"<<endl;
    Position a (15.0,0.0);
    Position b (15.0,15.0);
    Position c (0.0,0.0);

    cout<<c.estDansLaZone(a,15.0)<<endl;
    cout<<c.estDansLaZone(b,15.0)<<endl;
    cout<<c.estDansLaZone(a,10.0)<<endl;
    cout<<c.estDansLaZone(c,0.0)<<endl;
    cout<<c.estDansLaZone(b,-3.0)<<endl;

}

void Test::testGetAtmo()
{
    cout<<"**************Test de getAtmo***********"<<endl;
    
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

    cout<<c1.getATMO(date2)<<endl;;

}
