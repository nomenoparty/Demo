#pragma once
#include<iostream>
#include<string>
#include<conio.h>
#include<fstream>

using namespace std;
class Time
{
protected:
    int thungay;
    int phut;
    int gio;
    int ngay;
    int thang;
    int nam;
public:
    Time(int = 0, int = 0, int = 0, int = 0, int = 0, int = 0);
    ~Time();
    int getphut();
    int getgio();
    int getngay();
    int getthang();
    int getnam();
    int getthungay();
    void setphut(int);
    void setgio(int);
    void setngay(int);
    void setthang(int);
    void setnam(int);
    void setthungay(int);
    friend istream& operator>>(istream&, Time&);
    Time operator=(Time);
    Time operator+(int);
    Time congngay(Time T, int);
    bool operator==(Time);
    bool equalday(Time);
    friend ostream& operator<<(ostream&, const Time&);
    void xuatngay();
    int trungay(Time);
    bool operator>(Time);
    friend class suatchieu;
    friend class admin;
};