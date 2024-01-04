#pragma once
#include "rap.h"
class admin
{
private:
    string username;
    string password;
    rap rapquanly;
public:
    admin();
    ~admin();
    rap getrapquanly();
    void setusername(string);
    void setpassword(string);
    void setid(string, phim&);
    void settenphim(string, phim&);
    void setgiochieu(int, phim&);
    void setphutchieu(int, phim&);
    void setngaychieu(int, phim&);
    void setthangchieu(int, phim&);
    void setnamchieu(int, phim&);
    void settheloai(string, phim&);
    void setthoiluong(int, phim&);
    void setgioithieuphim(string, phim&);
    void sethankhoichieu(phim&);
    void setsosuatchieu(int, phim&);
    void setkhoichieu(Time, phim&);
    int getphimtuid(string);
    void themsuatchieu(suatchieu&, phim&);
    void themsuatchieu(suatchieu&, string);
    void nhapphongchieu(string);
    void themve(int, now, string, string, Time, string, string);
    suatchieu getsuatchieu(int, int, Time);
    string getusername();
    string getpassword();
    static string increaseString(string);
    void swap(Time&, Time&);
    phim* getdanhsachphim();
    friend bool compareStrings(const string& str1, const string& str2);
    friend int ConvertToInt(string);
    void xacnhandatve(int, int, int, int, bool[], string);
    bool ktrafull(phong);
    void setphong(int, int, int, phong);
    void setmaychu(maychu);
    void setngaychieuphim(Time);
    int getsophim();
    void nhaprap();
    void quanlychieuphim();
    void themphim(phim);
    void themphim(string);
    void xoaphim(phim);
    phim getphim(string);
    void xuatphim();
    void xuatve();
    void writeve(string, ve);
    void writesuatchieu(const string);
    void nhapsuatchieu(const string);
    void updatedanhsachphong(string);
    void writephim(phim, const string);
    string chinhSuaText(string, int[], int, bool);
    suatchieu getsuat(int i, int j, int k);
    phong getphong(string);

};