#pragma once
#include "maychu.h"
class rap
{
private:
    string tenrap;
    string diachi;
    /// 10 : 10 ngay chieu phim
    phong danhsachphong[10][3][8];
    maychu maychurap;
    Time ngaychieuphim;
public:
    rap();
    ~rap();
    maychu getmaychu();
    void datlaiphim();
    string gettenrap();
    string getdiachi();
    phong getphong(string);
    string getidphong(suatchieu);
    /// 10 : 10 ngay chieu phim
    phong getphong(int, int, int);
    Time getngaychieuphim();
    friend ostream& operator<<(ostream&, const rap&);
public:
    friend class admin;
};