#pragma once

#include <string>
using namespace std;

class Attribut
{
public:
    
    Attribut (string id, string u, string desc);
    virtual ~Attribut ( );
    string getID();

protected:
    string id;
    string unite;
    string description;
};
