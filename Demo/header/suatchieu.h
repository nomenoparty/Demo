#pragma once
#include "now.h"
class phong;
class phim;
class Time;

class suatchieu
{
private:
    Time thoigianchieu;
    pair<int, int> gioketthuc;
    string idphim;
    string idphong;
    int giave;
public:
    suatchieu();
    Time getthoigianchieu();
    pair<int, int> getgioketthuc();
    string getidphong();
    string getidphim();
    int getgiave();
    void setidphong(string);
    void setidphim(string);
    void setthoigianchieu(Time);
    void setgiochieu(int, int);
    void setgioketthucfirst(int);
    void setgioketthucsecond(int);
    void xuatgiochieu();
    void xuatgioketthuc();
    void operator=(suatchieu);
    bool operator == (suatchieu);
    friend class phong;
    friend class admin;
};