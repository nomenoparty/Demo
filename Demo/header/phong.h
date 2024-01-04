#pragma once
#include "phim.h"
class phong
{
private:
    string idphong;
    bool ghengoi[7][11];
    suatchieu suat;
public:
    phong();
    ~phong();
    string getidphong();
    bool getghengoi(int, int);
    suatchieu getsuat();
    void setidphong(string);
    void setghengoi(int, int, bool);
    void setsuat(suatchieu);
    void hienthighe();
    void operator= (phong);
    friend class admin;
    friend class rap;
    friend class suatchieu;
};