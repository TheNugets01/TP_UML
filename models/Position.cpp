#include <math.h>
#include "Position.h"

Position::Position (double lat, double lon)
{
    latitude = lat;
    longitude = lon;
} 

Position::Position ()
{
    
} 
Position::~Position ( )
{

}

bool Position::estDansLaZone(Position centre, double rayon) const
{
    double dist = pow(latitude - centre.latitude, 2) + pow(longitude - centre.longitude, 2);
    //cout << dist << endl;
	return dist <= pow(rayon, 2);
}