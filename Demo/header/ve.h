#pragma once
#include "phong.h"
class ve
{
private:

    string id;
    int giave;
    now ngaydat;
    string bapnuoc;
    string tenphim;
    Time ngaychieu;
    string ghengoi;
    string loaighe;
public:
    ve();
    ve(int, now, string, string, Time, string, string);
    ~ve();
    string getid();
    string gettenphim();
    int getgiave();
    string getloaighe();
    Time getngaychieu();
    string getbapnuoc();
    Time getngayxem();
    now getngaydat();
    string getbap();
    string getnuoc();
    string getghengoi();
    void setid(string);
    void setgiave(int);
    void setngayxem(Time);
    void setngaydat(Time);
    void setbap(string);
    void setnuoc(string);
    void setghengoi(string);
    bool operator==(ve);
    friend ostream& operator<<(ostream&, ve);
    void operator=(ve);
    friend class maychu;
};