
#include "../header/now.h"
now::now() {
    time_t now = time(0);
    tm ltm;
    localtime_s(&ltm, &now);
    nam = 1900 + ltm.tm_year;
    thang = 1 + ltm.tm_mon;
    ngay = ltm.tm_mday;
    gio = ltm.tm_hour;
    phut = 1 + ltm.tm_min;
    thungay = ltm.tm_wday;
}
ostream& operator<<(ostream& o, now n)
{
    o << n.getgio();
    o << ":";
    o << n.getphut();
    o << " ";
    o << n.getngay();
    o << "/";
    o << n.getthang();
    o << "/";
    o << n.getnam();
    return o;
}
now::~now() {}
void now::gancho(Time& T)
{
    T.setphut(phut);
    T.setgio(gio);
    T.setngay(ngay);
    T.setthang(thang);
    T.setnam(nam);
    T.setthungay(thungay);
}