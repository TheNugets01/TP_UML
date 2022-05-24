#include <iostream>
using namespace std;

#define DAY 86400

#include "Capteur.h"
#include "Position.h"

Capteur::Capteur (string ID, Position pos):sensorID(ID),position(pos)
{} 


Capteur::~Capteur ( )
{}

int Capteur::maxi(int a ,int b ,int c ,int d)
{
    int left_max = max(a, b);
    int right_max = max(c, d);
    int final_max = max(left_max, right_max);
    return final_max;
}

int Capteur::index(double valeur, double palier1, double palier2, double palier3, double palier4, double palier5, double palier6, double palier7, double palier8, double palier9)
{
	int index;
	if (valeur < 0)
		return 0;
	if (valeur < palier1) 
	{
		index = 1;
	}
	else if (valeur < palier2)
	{
		index = 2;
	}
	else if (valeur < palier3)
	{
		index = 3;
	}
	else if (valeur < palier4)
	{
		index = 4;
	}
	else if (valeur < palier5)
	{
		index = 5;
	}
	else if (valeur < palier6)
	{
		index = 6;
	}
	else if (valeur < palier7)
	{
		index = 7;
	}
	else if (valeur < palier8)
	{
		index = 8;
	}
	else if (valeur < palier9)
	{
		index = 9;
	}
	else
	{
		index = 10;
	}
	return index;
}

int Capteur::getATMO(time_t date)
{
    double atmoO3 = 0.0, atmoSO2 = 0.0, atmoNO2 = 0.0, atmoPM10 = 0.0;
	double nbO3 = 0.0, nbSO2 = 0.0, nbNO2 = 0.0, nbPM10 = 0.0;

    unordered_map<time_t, vector<Mesure>>::const_iterator itmap = mesures.find(date);
    vector<Mesure> mesure;

    if (itmap == mesures.end())
	{
        cerr << "Pas de mesures pour cette date" << endl;
	}
    else
    {
        mesure = itmap->second;
        vector<Mesure>::iterator itvec;
        for(itvec = begin(mesure) ; itvec != end(mesure) ; ++itvec)
        {
            string idGaz = itvec->attribut.id;
            if(idGaz == "O3")
            {
                atmoO3 += itvec->valeur;
                nbO3++;
            }
            else if(idGaz == "SO2")
            {
                atmoSO2 += itvec->valeur;
                nbSO2++;
            }
            else if(idGaz == "NO2")
            {
                atmoNO2 += itvec->valeur;
                nbNO2++;
            }
            else if(idGaz == "PM10")
            {
                atmoPM10 += itvec->valeur;
                nbPM10++;
            }
        }
        if(nbO3!=0)
            atmoO3 = atmoO3/nbO3;
        else
            atmoSO2 = 0;

        if(nbSO2!=0)
            atmoSO2 = atmoSO2/nbSO2;
        else
            atmoSO2 = 0;

        if(nbNO2!=0)
            atmoNO2 = atmoNO2/nbNO2;
        else
            atmoNO2 = 0;

        if(nbPM10!=0)
            atmoPM10 = atmoPM10/nbPM10;
        else
            atmoPM10 = 0;

        int indexO3 = index(atmoO3,30,55,80,105,130,150,180,210,240);
        int indexSO2 = index(atmoSO2,40,80,120,160,200,250,300,400,500);
        int indexNO2 = index(atmoNO2,30,55,85,110,135,165,200,275,400);
        int indexPM10 = index(atmoPM10,10,20,30,40,50,65,80,100,125);

        return maxi(indexO3,indexSO2,indexNO2,indexPM10);
    }

}

double Capteur::getMoyATMO(time_t dateDebut, time_t dateFin)
{
	double total = 0.0;
	double nb = 0.0;
    double moy = 0.0;
	for (time_t t = dateDebut; t <= dateFin; t += DAY) //iterating each 24h starting with timestampStart
	{
		total += getATMO(t);
		nb++;
	}
	if (nb == 0)
		moy = 0;
    else
        moy = total/nb;
	return moy;
}

Position Capteur::getPosition()
{
    return position;
}