#pragma once

#include <string>
#include <iostream>
using namespace std;

class Position
{

public:
    
    bool estDansLaZone(Position centre, double rayon) const;

    Position (double lat, double lon);
    virtual ~Position ( );
    
    double latitude;
    double longitude;
protected:


};

