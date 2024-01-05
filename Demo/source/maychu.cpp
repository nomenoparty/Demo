#include "../header/maychu.h"
maychu::maychu()
{
    danhsachve = NULL;
    danhsachphim = NULL;
    sove = 0;
    sophim = 0;
}
maychu::~maychu()
{
    delete[] danhsachve;
    delete[] danhsachphim;
}
int maychu::getsove()
{
    return sove;
}
phim* maychu::getdanhsachphim() {
    return danhsachphim;
}
int maychu::getsophim()
{
    return sophim;
}


void maychu::xoaphim(phim p)
{
    if (sophim != 0)
    {
        phim* tmp = new phim[sophim - 1];
        for (int i = 0; i < sophim; i++)
        {
            if (*(danhsachphim + i) == p)
            {
                for (int j = i + 1; j < sophim; j++)
                {
                    *(tmp + i) = *(danhsachphim + j);
                }
                break;
            }
            else
            {
                *(tmp + i) = *(danhsachphim + i);
            }
        }
        delete[]  danhsachphim;
        danhsachphim = new phim[sophim - 1];
        for (int i = 0; i < sophim - 1; i++)
        {
            *(danhsachphim + i) = *(tmp + i);
        }
        delete[] tmp;
        sophim -= 1;
    }
}
void maychu::updatedanhsachphim(string name_file) {
    now n;
    for (int i = 0; i < sophim; i++) {
        if ((*(danhsachphim + i)).gethankhoichieu().getthang() < n.getthang() ||
            (*(danhsachphim + i)).gethankhoichieu().getngay() < n.getngay()
            )
        {
            xoaphim(*(danhsachphim + i));
        }
    }
    ofstream o;
    o.open(name_file, ios::trunc);
    if (!o.is_open()) return;
    for (int i = 0; i < sophim; i++) {
        o << (*(danhsachphim + i)).gettenphim() << endl;
        o << (*(danhsachphim + i)).gettheloai() << endl;
        o << (*(danhsachphim + i)).getkhoichieu().getphut() << endl;
        o << (*(danhsachphim + i)).getkhoichieu().getgio() << endl;
        o << (*(danhsachphim + i)).getkhoichieu().getngay() << endl;
        o << (*(danhsachphim + i)).getkhoichieu().getthang() << endl;
        o << (*(danhsachphim + i)).getkhoichieu().getnam() << endl;
        o << (*(danhsachphim + i)).getthoiluong() << endl;
        o << (*(danhsachphim + i)).getgioithieuphim() << endl;
    }
    o.close();

}