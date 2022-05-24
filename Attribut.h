#include <string>
using namespace std;

class Attribut
{
public:
    
    Attribut (string u, string desc);
    virtual ~Attribut ( );
    string getID();

protected:
    string id;
    string unite;
    string description;
};
