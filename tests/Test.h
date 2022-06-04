#pragma once

#include "../models/Services.h"

using namespace std;

class Test
{
public:

Test();
Test(Services* service);
void testEstDansLaZone();
void testGetAtmo();
void testZoneMemeQualiteAir();
void testGetCapteurByID();
void testMoyenneQualiteAir();
void runTests();

private:
Services* service;
};
