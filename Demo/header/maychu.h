#include "ve.h"
class maychu
{
private:
    ve* danhsachve;
    int sove;
    phim* danhsachphim;
    int sophim;
public:
    maychu();
    ~maychu();
    int getsove();
    int getsophim();
    void updatedanhsachve(string);
    void updatedanhsachphim(string);
    void xoaphim(phim);
    ve* getdanhsachve();
    phim* getdanhsachphim();
    void themve(ve);
    void xoave(ve);
    friend class admin;
    friend class rap;
};