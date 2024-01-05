#pragma once
#include "suatchieu.h"
class phim
{
private:
    string id;
    string tenphim;
    string theloai;
    Time khoichieu;
    Time hankhoichieu;
    int thoiluong;
    string gioithieuphim;
    suatchieu* danhsachsuatchieu;
    int sosuatchieu;
    string linkAnh;
public:
    phim();
    phim operator=(phim);
    ~phim();

    string getlinkanh();
    string getid();
    string gettenphim();
    string gettheloai();
    Time getkhoichieu();
    Time gethankhoichieu();
    int getthoiluong();
    string getgioithieuphim();
    suatchieu* getdanhsachsuatchieu();
    int getsosuatchieu();
    void sethankhoichieu();
    phim* getcontrophim();
    friend ostream& operator<<(ostream&, phim);
    bool operator==(phim);
    suatchieu suatchieuluc(int, int);
    friend class admin;
    friend class rap;
    friend istream& operator>>(istream&, phim&);
    friend class maychu;
    friend class ve;
};



