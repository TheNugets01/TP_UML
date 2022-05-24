#include <string>
using namespace std;

class Attribut
{
public:
    
    Attribut (string u, string desc);
    virtual ~Attribut ( );

    string id;
    string unite;
    string description;
protected:

};
