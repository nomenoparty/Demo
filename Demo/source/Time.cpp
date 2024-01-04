#include "../header/Time.h"
Time::Time(int x, int y, int z, int a, int b, int c) {
    this->phut = x;
    this->gio = y;
    this->ngay = z;
    this->thang = a;
    this->nam = b;
    this->thungay = c;
}
Time::~Time() {}
int Time::getphut() { return phut; }
int Time::getgio() { return gio; }
int Time::getngay() { return ngay; }
int Time::getthang() { return thang; }
int Time::getnam() { return nam; }
int Time::getthungay() { return thungay; }
void Time::setphut(int phut) { this->phut = phut; }
void Time::setgio(int gio) { this->gio = gio; }
void Time::setngay(int ngay) { this->ngay = ngay; }
void Time::setthang(int thang) { this->thang = thang; }
void Time::setnam(int nam) { this->nam = nam; }
void Time::setthungay(int thungay) { this->thungay = thungay; }

istream& operator>>(istream& i, Time& d)
{
    int* tmp = new int;
    i >> *tmp;
    d.setgio(*tmp);
    i.ignore();
    i >> *tmp;
    i.ignore();
    d.setphut(*tmp);
    i >> *tmp;
    d.setngay(*tmp);
    i.ignore();
    i >> *tmp;
    d.setthang(*tmp);
    i.ignore();
    i >> *tmp;
    d.setnam(*tmp);
    i.ignore();
    i >> *tmp;
    d.setthungay(*tmp);
    i.ignore();
    delete tmp;
    return i;
}
Time Time::operator=(Time d)
{
    phut = d.getphut();
    gio = d.getgio();
    ngay = d.getngay();
    thang = d.getthang();
    nam = d.getnam();
    thungay = d.getthungay();
    return *this;
}
Time Time::operator+(int n)
{
    if ((ngay + n) > 28 && thang == 2)
    {
        this->ngay = ngay + n - 28;
        this->thang = thang + 1;
        this->nam = nam;
    }
    else if ((ngay + n) > 31 && thang == 12)
    {
        this->ngay = ngay + n - 31;
        this->thang = 1;
        this->nam = nam + 1;
    }
    else if ((ngay + n) > 30 && (thang == 4 || thang == 6 || thang == 9 || thang == 11))
    {
        this->ngay = ngay + n - 30;
        this->thang = thang + 1;
        this->nam = nam;
    }
    else if ((ngay + n) > 31 && (thang == 1 || thang == 3 || thang == 5 || thang == 7 || thang == 8 || thang == 10))
    {
        this->ngay = ngay + n - 31;
        this->thang = thang + 1;
        this->nam = nam;
    }
    else
    {
        this->ngay = ngay + n;
        this->thang = thang;
        this->nam = nam;
    }
    this->thungay += n % 7;
    return (*this);
}
bool Time::operator==(Time d)
{
    if (
        ngay == d.getngay() &&
        thang == d.getthang() &&
        nam == d.getnam()
        )

        return true;
    else
        return false;
}
int Time::trungay(Time T2)
{
    if (this->getthang() != T2.getthang())
    {
        if (T2.getthang() == 2)
        {
            return (this->getngay() - T2.getngay() + 28);
        }
        else if (T2.getthang() == 4 || T2.getthang() == 6 || T2.getthang() == 9 || T2.getthang() == 11)
        {
            return (this->getngay() - T2.getngay() + 30);
        }
        else if (T2.getthang() == 1 || T2.getthang() == 3 || T2.getthang() == 5 || T2.getthang() == 7 || T2.getthang() == 8 || T2.getthang() == 10 || T2.getthang() == 12)
        {
            return (this->getngay() - T2.getngay() + 31);
        }
    }
    else
    {
        return (this->getngay() - T2.getngay());
    }

    return (this->getngay() - T2.getngay());
}
bool Time::equalday(Time T)
{
    return (T.getngay() == this->ngay && T.getthang() == this->thang && T.getnam() == this->nam);
}
bool Time::operator>(Time d)
{
    if (this->nam > d.nam) return true;
    else if (this->thang > d.thang) return true;
    else if (this->ngay > d.ngay) return true;
    else return false;
}
ostream& operator<<(ostream& o, const Time& d)
{
    o << d.gio << endl << d.phut << endl << d.ngay << endl << d.thang << endl << d.nam << endl;
    return o;
}
void Time::xuatngay()
{
    cout << " " << ngay << "/" << thang << "/" << nam;
}
Time Time::congngay(Time T, int n)
{
    if ((T.getngay() + n) > 28 && T.getthang() == 2)
    {
        this->setngay(T.getngay() + n - 28);
        this->setthang(T.getthang() + 1);
        this->setnam(T.getnam());
    }
    else if ((T.getngay() + n) > 31 && T.getthang() == 12)
    {
        this->setngay(T.getngay() + n - 31);
        this->setthang(1);
        this->setnam(T.getnam() + 1);
    }
    else if ((T.getngay() + n) > 30 && (T.getthang() == 4 || T.getthang() == 6 || T.getthang() == 9 || T.getthang() == 11))
    {
        this->setngay(T.getngay() + n - 30);
        this->setthang(T.getthang() + 1);
        this->setnam(T.getnam());
    }
    else if ((T.getngay() + n) > 31 && (T.getthang() == 1 || T.getthang() == 3 || T.getthang() == 5 || T.getthang() == 7 || T.getthang() == 8 || T.getthang() == 10))
    {
        this->setngay(T.getngay() + n - 31);
        this->setthang(T.getthang() + 1);
        this->setnam(T.getnam());
    }
    else
    {
        this->setngay(T.getngay() + n);
        this->setthang(T.getthang());
        this->setnam(T.getnam());
    }
    this->setthungay(thungay + n % 7);
    return (*this);
}