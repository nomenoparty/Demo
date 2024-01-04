#include "Time.h"

class now : public Time
{
public:
    now();
    ~now();
    void gancho(Time&);
    friend ostream& operator<<(ostream&, now);
};