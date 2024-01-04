#include "../header/suatchieu.h"
suatchieu::suatchieu() {
    if (thoigianchieu.getthungay() >= 1 && thoigianchieu.getthungay() < 6) {
        giave = 60;

    }
    else {
        giave = 70;
    }

}
void suatchieu::xuatgiochieu()
{

    cout << thoigianchieu.gio << endl;
    cout << thoigianchieu.phut << endl;
}
string suatchieu::getidphong()
{
    return idphong;
}
string suatchieu::getidphim()
{
    return idphim;
}
int suatchieu::getgiave() {
    return giave;
}
void suatchieu::setgioketthucfirst(int i)
{
    gioketthuc.first = i;
}
void suatchieu::setgioketthucsecond(int i)
{
    gioketthuc.second = i;
}
void suatchieu::xuatgioketthuc()
{
    cout << gioketthuc.first;
    cout << ":";
    cout << gioketthuc.second;
}
void suatchieu::setidphong(string s)
{
    idphong = s;
}
void suatchieu::setgiochieu(int i, int  j)
{
    thoigianchieu.gio = i;
    thoigianchieu.phut = j;
    if (thoigianchieu.getphut() >= 15)
    {
        gioketthuc.second = thoigianchieu.getphut() + 45 - 60;
        gioketthuc.first = thoigianchieu.getgio() + 2;
    }
    else
    {
        gioketthuc.second = thoigianchieu.getphut() + 45;
        gioketthuc.first = thoigianchieu.getgio() + 1;
    }
}
void suatchieu::setthoigianchieu(Time T)
{
    thoigianchieu.setngay(T.getngay());
    thoigianchieu.setthang(T.getthang());
    thoigianchieu.setnam(T.getnam());
    thoigianchieu.setgio(T.getgio());
    thoigianchieu.setphut(T.getphut());
    if (thoigianchieu.getphut() >= 15)
    {
        gioketthuc.second = thoigianchieu.getphut() + 45 - 60;
        gioketthuc.first = thoigianchieu.getgio() + 2;
    }
    else
    {
        gioketthuc.second = thoigianchieu.getphut() + 45;
        gioketthuc.first = thoigianchieu.getgio() + 1;
    }
}
void suatchieu::setidphim(string s)
{
    idphim = s;
}
void suatchieu::operator=(suatchieu sc)
{
    this->thoigianchieu = sc.thoigianchieu;
    this->gioketthuc.first = sc.gioketthuc.first;
    this->gioketthuc.second = sc.gioketthuc.second;
    this->idphong = sc.idphong;
    this->idphim = sc.idphim;
}
Time suatchieu::getthoigianchieu()
{
    return thoigianchieu;
}
pair<int, int> suatchieu::getgioketthuc()
{
    return gioketthuc;
}
bool suatchieu::operator==(suatchieu sc) {
    return (thoigianchieu == sc.thoigianchieu && idphim == sc.idphim && idphong == sc.idphong);
}
// suatchieu suatchieu::operator[](int i) {
//     return ((*this)[i]);
// }