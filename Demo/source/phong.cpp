#include "../header/phong.h"
#include<iostream>
phong::phong() {
    idphong = "A";
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 11; j++) {
            ghengoi[i][j] = false;
        }
    }
}
phong::~phong() {
}
string phong::getidphong() {
    return idphong;
}

bool phong::getghengoi(int i, int j)
{
    return ghengoi[i][j];
}
suatchieu phong::getsuat()
{
    return suat;
}
void phong::operator=(phong p) {
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 11; j++) {
            ghengoi[i][j] = p.getghengoi(i, j);
        }
    }
    suat = p.getsuat();

    idphong = p.getidphong();
}
void phong::setghengoi(int i, int j, bool o)
{
    this->ghengoi[i][j] = o;
}
void phong::setidphong(string s) { this->idphong = s; }
void phong::setsuat(suatchieu sc) { this->suat = sc; }