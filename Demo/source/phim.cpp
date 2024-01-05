#include "../header/phim.h"

phim::phim() {
    sosuatchieu = 0;
    tenphim = "aa";
}
phim::~phim() {}
string phim::getid() { return this->id; }
string phim::gettenphim() { return this->tenphim; };
string phim::gettheloai() { return this->theloai; };
Time phim::getkhoichieu() { return this->khoichieu; };
Time phim::gethankhoichieu() { return this->hankhoichieu; };
int phim::getthoiluong() { return this->thoiluong; };
string phim::getgioithieuphim() { return this->gioithieuphim; };
int phim::getsosuatchieu() { return this->sosuatchieu; }
suatchieu* phim::getdanhsachsuatchieu() { return this->danhsachsuatchieu; }

phim phim::operator=(phim p)
{
    this->id = p.id;
    this->tenphim = p.tenphim;
    this->theloai = p.theloai;
    this->khoichieu = p.khoichieu;
    this->hankhoichieu = p.hankhoichieu;
    this->thoiluong = p.thoiluong;
    this->gioithieuphim = p.gioithieuphim;
    this->danhsachsuatchieu = p.danhsachsuatchieu;
    this->sosuatchieu = p.sosuatchieu;
    return (*this);
}
string phim::getlinkanh() {
    return linkAnh;
}
suatchieu phim::suatchieuluc(int i, int j)
{
    for (int o = 0; o < sosuatchieu; o++)
    {
        if (((*(danhsachsuatchieu + o)).getthoigianchieu()).getphut() == j && ((*(danhsachsuatchieu + o)).getthoigianchieu()).getgio() == i)
            return (*(danhsachsuatchieu + o));
    }
    return *(danhsachsuatchieu + 0);
}
void phim::sethankhoichieu()
{
    if (khoichieu.getngay() >= 15 && khoichieu.getthang() == 2)
    {
        hankhoichieu.setngay(khoichieu.getngay() + 14 - 28);
        hankhoichieu.setthang(khoichieu.getthang() + 1);
        hankhoichieu.setnam(khoichieu.getnam());
    }
    else if (khoichieu.getngay() >= 18 && khoichieu.getthang() == 12)
    {
        hankhoichieu.setngay(khoichieu.getngay() + 14 - 31);
        hankhoichieu.setthang(1);
        hankhoichieu.setnam(khoichieu.getnam() + 1);
    }
    else if (khoichieu.getngay() >= 17 && (khoichieu.getthang() == 4 || khoichieu.getthang() == 6 || khoichieu.getthang() == 9 || khoichieu.getthang() == 11))
    {
        hankhoichieu.setngay(khoichieu.getngay() + 14 - 30);
        hankhoichieu.setthang(khoichieu.getthang() + 1);
        hankhoichieu.setnam(khoichieu.getnam());
    }
    else if (khoichieu.getngay() >= 18 && (khoichieu.getthang() == 1 || khoichieu.getthang() == 3 || khoichieu.getthang() == 5 || khoichieu.getthang() == 7 || khoichieu.getthang() == 8 || khoichieu.getthang() == 10))
    {
        hankhoichieu.setngay(khoichieu.getngay() + 14 - 31);
        hankhoichieu.setthang(khoichieu.getthang() + 1);
        hankhoichieu.setnam(khoichieu.getnam());
    }
    else
    {
        hankhoichieu.setngay(khoichieu.getngay() + 14);
        hankhoichieu.setthang(khoichieu.getthang());
        hankhoichieu.setnam(khoichieu.getnam());
    }
    hankhoichieu.setphut(khoichieu.getphut());
    hankhoichieu.setgio(khoichieu.getgio());
}
istream& operator>>(istream& i, phim& p)
{
    getline(i, p.tenphim);
    getline(i, p.theloai);
    int tmp;
    i >> tmp;
    i.ignore();
    p.khoichieu.setgio(tmp);
    i >> tmp;
    i.ignore();
    p.khoichieu.setphut(tmp);
    i >> tmp;
    i.ignore();
    p.khoichieu.setngay(tmp);
    i >> tmp;
    i.ignore();
    p.khoichieu.setthang(tmp);
    i >> tmp;
    i.ignore();
    p.khoichieu.setnam(tmp);

    p.sethankhoichieu();
    i >> p.thoiluong;
    i.ignore();
    getline(i, p.gioithieuphim);
    i.ignore();
    return i;
}

bool phim::operator==(phim p)
{


    if (p.tenphim == tenphim && p.hankhoichieu == this->hankhoichieu && p.theloai == theloai && p.khoichieu == khoichieu && p.thoiluong == thoiluong && p.gioithieuphim == gioithieuphim && p.sosuatchieu == sosuatchieu)
        return true;
    else
        return false;
}
ostream& operator<<(ostream& o, phim p)
{
    o << p.id << endl;
    o << p.tenphim << endl;
    o << p.theloai << endl;
    o << p.khoichieu;
    o << p.hankhoichieu;
    o << p.thoiluong << endl;
    o << p.gioithieuphim << endl;
    return o;
}
phim* phim::getcontrophim() {
    return this;
}