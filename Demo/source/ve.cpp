#include "../header/ve.h"
ve::ve() {
    id = "A";
    giave = 0;
    bapnuoc = "A";
    ghengoi = "A";
}
ve::ve(int giavee, now ngaydatt, string bapnuocc, string tenphimm, Time ngaychieuu, string ghengoii, string loaighee)
{
    id = "R";
    ngaydat = ngaydatt;
    bapnuoc = bapnuocc;
    giave = giavee;
    ghengoi = ghengoii;
    ngaychieu = ngaychieuu;
    tenphim = tenphimm;
    loaighe = loaighee;
    int* tmp = new int;
    int* tmp1 = new int;
    string* tmpstring = new string;
    (*tmpstring) = bapnuoc + ghengoi + loaighe + tenphim;
    for (int i = 0; i < 9; i += 2) {
        (*tmpstring)[i] += i;
    }
    for (int i = 9; i < 9 + ghengoi.length(); i += 2) {
        (*tmpstring)[i] += i;
    }
    for (int i = 9 + ghengoi.length(); i < (*tmpstring).length(); i += 2) {
        (*tmpstring)[i] += i;
    }
    for (int i = 1; i <= 8; i++)
    {
        if (i == 1)
            *tmp = ngaydat.getphut();
        else if (i == 2)
            *tmp = ngaydat.getgio();
        else if (i == 3)
            *tmp = ngaydat.getngay();
        else if (i == 4)
            *tmp = ngaydat.getthang();
        else if (i == 5)
            *tmp = ngaychieuu.getphut();
        else if (i == 6)
            *tmp = ngaychieuu.getgio();
        else if (i == 7)
            *tmp = ngaychieuu.getngay();
        else if (i == 8)
            *tmp = ngaychieuu.getthang();
        if (*tmp < 10) { id += (char)((*tmp) + 48); }
        else {
            if (((*tmp + 65) < 97 && (*tmp + 65) > 90) || (*tmp + 65) > 122)
            {
                *tmp1 = *tmp;

                while ((*tmp1) != 0)
                {
                    id += (char)(((*tmp1) % 10) + 48);
                    (*tmp1) /= 10;
                }
            }
            else
            {
                id += (char)(*tmp + 65);
            }
        }
    }
    id += *(tmpstring);
}
string ve::getloaighe() {
    return loaighe;
}
string ve::gettenphim() {
    return tenphim;
}
string ve::getbapnuoc() {
    return bapnuoc;
}
Time ve::getngaychieu() {
    return ngaychieu;
}
string ve::getid() { return this->id; }
int ve::getgiave() { return this->giave; }
now ve::getngaydat() { return this->ngaydat; }
string ve::getbap() { return this->bapnuoc; }
string ve::getghengoi() { return this->ghengoi; }
void ve::setid(string s) { this->id = s; }
void ve::setgiave(int s) { this->giave = s; }
void ve::setbap(string s) { this->bapnuoc = s; }
void ve::setghengoi(string gn) { this->ghengoi = gn; }
void ve::operator=(ve v) {
    this->id = v.id;
    this->giave = v.giave;
    this->ngaydat = v.ngaydat;
    this->bapnuoc = v.bapnuoc;
    this->tenphim = v.tenphim;
    this->ngaychieu = v.ngaychieu;
    this->ghengoi = v.ghengoi;
    this->loaighe = v.loaighe;
}
bool ve::operator==(ve v) {
    if (v.id != this->id) return false;
    else return true;
}
ve::~ve() {}