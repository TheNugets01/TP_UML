#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>

#include "Services.h"

using namespace std;

int main()
{
    ifstream src("sensors.csv", ios_base::in);
    Services::initCapteur(src);

    return 0;
}