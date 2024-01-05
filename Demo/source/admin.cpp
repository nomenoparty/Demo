#include "../header/admin.h"

admin::admin()
{

}
admin::~admin()
{
}
rap admin::getrapquanly() {
    return rapquanly;
}
void admin::setusername(string s)
{
    username = s;
}
void admin::setpassword(string s)
{
    password = s;
}

string admin::getusername()
{
    return username;
}
string admin::getpassword()
{
    return password;
}

void admin::xacnhandatve(int i, int j, int e, int r, bool k[], string name_file)
{

    ofstream o;
    for (int t = 0; t < 11; t++) {
        rapquanly.danhsachphong[i][j][e].ghengoi[r][t] = k[t];
    }
    o.open(name_file, ios::trunc);
    for (int t = 0; t < 10; t++) {
        for (int v = 0; v < 3; v++) {
            for (int q = 0; q < 8; q++) {
                o << rapquanly.danhsachphong[t][v][q].getidphong() << endl;
                for (int l = 0; l < 7; l++) {
                    for (int p = 0; p < 11; p++) {
                        o << rapquanly.danhsachphong[t][v][q].getghengoi(l, p);
                    }
                    o << endl;
                }
            }
        }
    }


    o.close();

}



void admin::themve(int giavee, now ngaydatt, string bapnuocc, string tenphimm, Time ngaychieuu, string ghengoii, string loaighee)
{
    ////// tao ve
    ve v(giavee, ngaydatt, bapnuocc, tenphimm, ngaychieuu, ghengoii, loaighee);
    if (rapquanly.maychurap.sove == 0)
    {
        rapquanly.maychurap.danhsachve = new ve[rapquanly.maychurap.sove + 1];
        *(rapquanly.maychurap.danhsachve + rapquanly.maychurap.sove) = v;
        rapquanly.maychurap.sove++;
    }
    else
    {
        ve* tmp = new ve[rapquanly.maychurap.sove];
        for (int i = 0; i < rapquanly.maychurap.sove; i++)
        {
            *(tmp + i) = *(rapquanly.maychurap.danhsachve + i);
        }
        delete[] rapquanly.maychurap.danhsachve;
        rapquanly.maychurap.danhsachve = new ve[rapquanly.maychurap.sove + 1];
        for (int i = 0; i < rapquanly.maychurap.sove; i++)
        {
            *(rapquanly.maychurap.danhsachve + i) = *(tmp + i);
        }
        *(rapquanly.maychurap.danhsachve + rapquanly.maychurap.sove) = v;
        delete[] tmp;
        rapquanly.maychurap.sove++;
    }


    writeve("DanhSachVe.txt", v);

}
void admin::writeve(string name_file, ve v) {

    ofstream o;
    o.open(name_file, ios::app);
    if (!o.is_open()) return;
    o << v.getid() << endl;
    o << v.getgiave() << endl;
    o << v.getngaydat().getgio() << endl;
    o << v.getngaydat().getphut() << endl;
    o << v.getngaydat().getngay() << endl;
    o << v.getngaydat().getthang() << endl;
    o << v.getngaydat().getnam() << endl;
    o << v.getbapnuoc() << endl;
    o << v.gettenphim() << endl;
    o << v.getngaychieu().getgio() << endl;
    o << v.getngaychieu().getphut() << endl;
    o << v.getngaychieu().getngay() << endl;
    o << v.getngaychieu().getthang() << endl;
    o << v.getngaychieu().getnam() << endl;
    o << v.getghengoi() << endl;
    o << v.getloaighe() << endl;
    o.close();
}


void admin::nhapphongchieu(string name_file) {
    ifstream i;
    i.open(name_file);
    if (!i.is_open()) return;
    string tmp;
    int k = 0, j = 0, z = 0;
    int p = 0, q = 0;
    while (getline(i, tmp))
    {

        if (tmp.length() <= 3) {
            rapquanly.danhsachphong[k][j][z].idphong = tmp;
        }
        else {
            if (k == 10) break;
            for (int t = 0; t < 11; t++) {
                rapquanly.danhsachphong[k][j][z].ghengoi[p][q] = tmp[t] - '0';
                q++;
                if (q == 11) {
                    q = 0;
                    p++;
                    if (p == 7) {
                        p = 0; q = 0;
                        z++;
                        if (z == 8) {
                            z = 0;
                            j++;
                            if (j == 3) {
                                j = 0; k++; if (k == 10) break;
                            }
                        }

                    }
                }
            }
        }
    }
    i.close();
}
void admin::writephim(phim p, const string name_file) {
    ifstream i;
    i.open(name_file);
    string tmp;
    int count = 1;
    while (getline(i, tmp))
    {
        count++;
    }
    i.close();
    ofstream o;
    o.open(name_file, ios::app);
    if (count != 1) o << endl;
    o << p.gettenphim() << endl;
    o << p.gettheloai() << endl;
    o << p.getkhoichieu().getphut() << endl;
    o << p.getkhoichieu().getgio() << endl;
    o << p.getkhoichieu().getngay() << endl;
    o << p.getkhoichieu().getthang() << endl;
    o << p.getkhoichieu().getnam() << endl;
    o << p.getthoiluong() << endl;
    o << p.getgioithieuphim() << endl;
    o.close();
}


void admin::setid(string s, phim& p)
{
    p.id = s;
}
void admin::settenphim(string s, phim& p)
{
    p.tenphim = s;
}

void admin::setlinkanh(string s, phim& p) {
    p.linkAnh = s;
}
void admin::setgiochieu(int a, phim& p) { p.khoichieu.setgio(a); }
void admin::setphutchieu(int a, phim& p) { p.khoichieu.setphut(a); }
void admin::setngaychieu(int a, phim& p) { p.khoichieu.setngay(a); }
void admin::setthangchieu(int a, phim& p) { p.khoichieu.setthang(a); }
void admin::setnamchieu(int a, phim& p) { p.khoichieu.setnam(a); }
void admin::settheloai(string s, phim& p)
{
    p.theloai = s;
}
void admin::setkhoichieu(Time T, phim& p)
{
    p.khoichieu = T;
}
void admin::sethankhoichieu(phim& p)
{
    if (p.khoichieu.getngay() >= 15 && p.khoichieu.getthang() == 2)
    {
        p.hankhoichieu.setngay(p.khoichieu.getngay() + 14 - 28);
        p.hankhoichieu.setthang(p.khoichieu.getthang() + 1);
        p.hankhoichieu.setnam(p.khoichieu.getnam());
    }
    else if (p.khoichieu.getngay() >= 18 && p.khoichieu.getthang() == 12)
    {
        p.hankhoichieu.setngay(p.khoichieu.getngay() + 14 - 31);
        p.hankhoichieu.setthang(1);
        p.hankhoichieu.setnam(p.khoichieu.getnam() + 1);
    }
    else if (p.khoichieu.getngay() >= 17 && (p.khoichieu.getthang() == 4 || p.khoichieu.getthang() == 6 || p.khoichieu.getthang() == 9 || p.khoichieu.getthang() == 11))
    {
        p.hankhoichieu.setngay(p.khoichieu.getngay() + 14 - 30);
        p.hankhoichieu.setthang(p.khoichieu.getthang() + 1);
        p.hankhoichieu.setnam(p.khoichieu.getnam());
    }
    else if (p.khoichieu.getngay() >= 18 && (p.khoichieu.getthang() == 1 || p.khoichieu.getthang() == 3 || p.khoichieu.getthang() == 5 || p.khoichieu.getthang() == 7 || p.khoichieu.getthang() == 8 || p.khoichieu.getthang() == 10))
    {
        p.hankhoichieu.setngay(p.khoichieu.getngay() + 14 - 31);
        p.hankhoichieu.setthang(p.khoichieu.getthang() + 1);
        p.hankhoichieu.setnam(p.khoichieu.getnam());
    }
    else
    {
        p.hankhoichieu.setngay(p.khoichieu.getngay() + 14);
        p.hankhoichieu.setthang(p.khoichieu.getthang());
        p.hankhoichieu.setnam(p.khoichieu.getnam());
    }
    p.hankhoichieu.setphut(p.khoichieu.getphut());
    p.hankhoichieu.setgio(p.khoichieu.getgio());
}
void admin::setsosuatchieu(int n, phim& p)
{
    p.sosuatchieu = n;
}
void admin::setthoiluong(int s, phim& p)
{
    p.thoiluong = s;
}

void admin::setgioithieuphim(string s, phim& p)
{
    p.gioithieuphim = s;
}

// g++ test.cpp thuvienadmin.cpp -o bangdz

void admin::themsuatchieu(suatchieu& sc, phim& p)
{
    if (p.sosuatchieu == 0)
    {
        p.danhsachsuatchieu = new suatchieu[1];
        *(p.danhsachsuatchieu + 0) = sc;
        p.sosuatchieu++;
    }
    else
    {
        suatchieu* tmp = new suatchieu[p.sosuatchieu + 1];
        for (int i = 0; i < p.sosuatchieu; i++)
        {

            *(tmp + i) = *(p.danhsachsuatchieu + i);
        }
        *(tmp + p.sosuatchieu) = sc;
        delete[] p.danhsachsuatchieu;
        p.sosuatchieu++;
        p.danhsachsuatchieu = new suatchieu[p.sosuatchieu];
        for (int i = 0; i < p.sosuatchieu; i++)
        {
            *(p.danhsachsuatchieu + i) = *(tmp + i);
        }
        delete[] tmp;
    }
    sc.setidphim(p.id);
}
void admin::themsuatchieu(suatchieu& sc, string s)
{
    for (int i = 0; i < this->getsophim(); i++) {
        if (rapquanly.maychurap.danhsachphim[i].getid() == s) {
            themsuatchieu(sc, rapquanly.maychurap.danhsachphim[i]);
        }
    }
}
void admin::setngaychieuphim(Time T) { rapquanly.ngaychieuphim = T; }
void admin::setphong(int i, int j, int k, phong p) { rapquanly.danhsachphong[i][j][k] = p; }
void admin::setmaychu(maychu mc) { rapquanly.maychurap = mc; }

void admin::nhaprap()
{
    rapquanly.tenrap = "CGV DA NANG";
    rapquanly.diachi = "Lien Chieu ";
    for (int o = 0; o < 8; o++)
    {
        ((rapquanly.danhsachphong[0][0][o].suat)).setgiochieu(7 + (2 * o), 45);
        ((rapquanly.danhsachphong[0][1][o].suat)).setgiochieu(7 + 1 + (2 * o), 0);
        ((rapquanly.danhsachphong[0][2][o].suat)).setgiochieu(7 + 1 + (2 * o), 15);
    }
    for (int o = 0; o < 3; o++)
    {
        for (int k = 0; k < 8; k++)
        {
            if (o == 0)
            {
                rapquanly.danhsachphong[0][o][k].suat.setgioketthucfirst(rapquanly.danhsachphong[0][o][k].suat.getthoigianchieu().getgio() + 2);
                rapquanly.danhsachphong[0][o][k].suat.setgioketthucsecond(rapquanly.danhsachphong[0][o][k].suat.getthoigianchieu().getphut() + 45 - 60);
            }
            else if (o == 1)
            {
                rapquanly.danhsachphong[0][o][k].suat.setgioketthucfirst(rapquanly.danhsachphong[0][o][k].suat.getthoigianchieu().getgio() + 2);
                rapquanly.danhsachphong[0][o][k].suat.setgioketthucsecond(rapquanly.danhsachphong[0][o][k].suat.getthoigianchieu().getphut() + 45);
            }
            else
            {
                rapquanly.danhsachphong[0][o][k].suat.setgioketthucfirst(rapquanly.danhsachphong[0][o][k].suat.getthoigianchieu().getgio() + 2);
                rapquanly.danhsachphong[0][o][k].suat.setgioketthucsecond(rapquanly.danhsachphong[0][o][k].suat.getthoigianchieu().getphut() - 15);
            }
        }
    }
    for (int g = 0; g < 10; g++)
    {
        for (int o = 0; o < 3; o++)
        {
            for (int k = 0; k < 8; k++)
            {
                rapquanly.danhsachphong[g][o][k].suat.setgiochieu(rapquanly.danhsachphong[0][o][k].suat.getthoigianchieu().getgio(), rapquanly.danhsachphong[0][o][k].suat.getthoigianchieu().getphut());
                rapquanly.danhsachphong[g][o][k].suat.setgioketthucfirst(rapquanly.danhsachphong[0][o][k].suat.getthoigianchieu().getgio());
                rapquanly.danhsachphong[g][o][k].suat.setgioketthucsecond(rapquanly.danhsachphong[0][o][k].suat.getthoigianchieu().getphut());
            }
        }
    }
}


void admin::quanlychieuphim2() {

    now n;
    {

        n.gancho(rapquanly.ngaychieuphim);


        int r = 0;
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 3; j++) {
                for (int o = 0; o < 8; o++) {
                    (rapquanly.danhsachphong)[i][j][o].suat.idphong = ((rapquanly.danhsachphong)[i][j])[o].getidphong();
                    (rapquanly.danhsachphong)[i][j][o].suat.idphim = (*(rapquanly.maychurap.danhsachphim + r)).getid();
                    (rapquanly.danhsachphong)[i][j][o].suat.thoigianchieu.congngay(rapquanly.ngaychieuphim, i);
                    themsuatchieu(((rapquanly.danhsachphong)[i][j][o].suat), (*(rapquanly.maychurap.danhsachphim + r)));
                    r = r + 1;
                    if (r == rapquanly.maychurap.getsophim())
                    {
                        r = 0;
                    }

                }
            }
        }
    }

}

void admin::quanlychieuphim() {
    now n;
    rapquanly.ngaychieuphim.setngay(rapquanly.danhsachphong[0][0][0].suat.getthoigianchieu().getngay());

    if (n.getngay() >= rapquanly.ngaychieuphim.getngay() + 10) {
        n.gancho(rapquanly.ngaychieuphim);
        int r = 0;
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 3; j++) {
                for (int o = 0; o < 8; o++) {
                    (rapquanly.danhsachphong)[i][j][o].suat.idphong = ((rapquanly.danhsachphong)[i][j])[o].getidphong();
                    (rapquanly.danhsachphong)[i][j][o].suat.idphim = (*(rapquanly.maychurap.danhsachphim + r)).getid();
                    (rapquanly.danhsachphong)[i][j][o].suat.thoigianchieu.congngay(rapquanly.ngaychieuphim, i);
                    themsuatchieu(((rapquanly.danhsachphong)[i][j][o].suat), (*(rapquanly.maychurap.danhsachphim + r)));
                    r = r + 1;
                    if (r == rapquanly.maychurap.getsophim())
                    {
                        r = 0;
                    }

                }
            }
        }
    }


    else if (n.getngay() > rapquanly.ngaychieuphim.getngay()) {
        int soNgay = n.trungay(rapquanly.ngaychieuphim);
        rapquanly.ngaychieuphim.ngay += soNgay;
        int r = 0;
        for (int i = 0; i < 10 - soNgay; i++) {
            for (int j = 0; j < 3; j++) {
                for (int o = 0; o < 8; o++) {
                    (rapquanly.danhsachphong)[i][j][o].suat.idphong = ((rapquanly.danhsachphong)[i][j])[o].getidphong();
                    (rapquanly.danhsachphong)[i][j][o].suat.thoigianchieu = (rapquanly.danhsachphong)[i + soNgay][j][o].suat.thoigianchieu;
                    (rapquanly.danhsachphong)[i][j][o].suat.idphim = (rapquanly.danhsachphong)[i + soNgay][j][o].suat.getidphim();


                    for (int m = 0; m < 7; m++) {
                        for (int n = 0; n < 11; n++) {
                            rapquanly.danhsachphong[i][j][o].setghengoi(m, n, rapquanly.danhsachphong[i + soNgay][j][o].getghengoi(m, n));
                        }
                    }
                    themsuatchieu(((rapquanly.danhsachphong)[i][j][o].suat), (*(rapquanly.maychurap.danhsachphim + getphimtuid((rapquanly.danhsachphong)[i + soNgay][j][o].suat.idphim))));
                    r = r + 1;
                    if (r == rapquanly.maychurap.getsophim())
                    {
                        r = 0;
                    }

                }
            }
        }



        r = 0;
        for (int i = 10 - soNgay; i < 10; i++) {
            for (int j = 0; j < 3; j++) {
                for (int o = 0; o < 8; o++) {

                    (rapquanly.danhsachphong)[i][j][o].suat.idphim = (*(rapquanly.maychurap.danhsachphim + r)).getid();
                    (rapquanly.danhsachphong)[i][j][o].suat.thoigianchieu.congngay(rapquanly.ngaychieuphim, i);
                    themsuatchieu(((rapquanly.danhsachphong)[i][j][o].suat), (*(rapquanly.maychurap.danhsachphim + r)));
                    r = r + 1;
                    if (r == rapquanly.maychurap.getsophim())
                    {
                        r = 0;
                    }

                }
            }
        }

    }



    writesuatchieu("DanhSachSuatChieu.txt");
    ofstream o;
    o.open("DanhSachPhong.txt", ios::trunc);
    for (int t = 0; t < 10; t++) {
        for (int v = 0; v < 3; v++) {
            for (int q = 0; q < 8; q++) {
                o << rapquanly.danhsachphong[t][v][q].getidphong() << endl;
                for (int l = 0; l < 7; l++) {
                    for (int p = 0; p < 11; p++) {
                        o << rapquanly.danhsachphong[t][v][q].getghengoi(l, p);
                    }
                    o << endl;
                }
            }
        }
    }
    o.close();





}

suatchieu admin::getsuatchieu(int i, int j, Time T)
{
    int k = T.trungay(rapquanly.ngaychieuphim);
    for (int o = 0; o < 3; o++)
    {
        for (int p = 0; p < 8; p++)
        {
            if (rapquanly.danhsachphong[k][o][p].suat.getthoigianchieu().getgio() == i && rapquanly.danhsachphong[k][o][p].suat.getthoigianchieu().getphut() == j)
            {
                return rapquanly.danhsachphong[k][o][p].suat;
            }
        }
    }
    suatchieu tmpsc;
    return tmpsc;
}

bool compareStrings(const  string& str1, const  string& str2) {
    const size_t  sai = 4;  // Ng??ng cho phï¿½p s? l??ng kï¿½ t? khï¿½c nhau

    size_t  t = abs((int)(str1.length() - str2.length()));
    if (t > sai) {
        return false;
    }

    size_t  khac = 0;
    size_t i = 0, j = 0;
    while (i < str1.length() && j < str2.length()) {
        if (tolower(str1[i]) != tolower(str2[j])) {
            ++khac;
            if (khac > sai) {
                return false;
            }
            if (str1.length() > str2.length()) {
                ++i;
            }
            else if (str2.length() > str1.length()) {
                ++j;
            }
            else {
                ++i;
                ++j;
            }
        }
        else {
            ++i;
            ++j;
        }
    }
    return  khac <= sai;
}
int admin::getphimtuid(string tmp1) {
    for (int i = 0; i < rapquanly.maychurap.sophim; i++)
    {
        if ((*(rapquanly.maychurap.danhsachphim + i)).id == tmp1) return (i);

    }
    return -1;
}
phim admin::getphim(string tmp1)
{
    for (int i = 0; i < rapquanly.maychurap.sophim; i++)
    {
        string tmp = (*(rapquanly.maychurap.danhsachphim + i)).tenphim;
        if (compareStrings(tmp, tmp1))
        {
            return *(rapquanly.maychurap.danhsachphim + i);
        }
    }
    phim tmp43;
    return tmp43;
}
phim* admin::getdanhsachphim() {
    return rapquanly.maychurap.getdanhsachphim();
}
int ConvertToInt(string s) {
    int result = 0;
    int multiply = 1;

    for (int i = s.length() - 1; i >= 0; --i) {
        if (isdigit(s[i])) {
            result += (s[i] - '0') * multiply;
            multiply *= 10;
        }
        else {
            return 0;
        }
    }

    return result;
}
string admin::increaseString(string str) {
    string str1;
    str1 = "000";
    if (str[2] == '9') {
        if (str[1] == '9') {
            (str1[0]) = (str[0]) + 1;
            str1[1] = '0';
            str1[2] = '0';
        }
        else {
            (str1[0]) = (str[0]);
            (str1[1]) = (str[1]) + 1;
            str1[2] = '0';
        }
    }
    else {
        (str1[0]) = (str[0]);
        (str1[1]) = (str[1]);
        (str1[2]) = (str[2]) + 1;
    }
    return str1;
}
void admin::themphim(string namefile)
{
    delete[] rapquanly.maychurap.danhsachphim;
    rapquanly.maychurap.sophim = 0;
    ifstream i;
    i.open(namefile, ios::in);
    if (!i.is_open()) return;
    int tmpcount = 1;
    string tmp;
    while (getline(i, tmp)) {
        tmpcount++;
    }
    i.close();
    rapquanly.maychurap.danhsachphim = new phim[tmpcount];
    string line;
    int count = 1;
    int countphim = 0;
    i.open(namefile, ios::in);
    if (!i.is_open()) return;
    while (getline(i, line)) {
        switch (count % 10) {
        case 1:
            settenphim(line, rapquanly.maychurap.danhsachphim[countphim]);
            break;
        case 2:
            settheloai(line, rapquanly.maychurap.danhsachphim[countphim]);
            break;
        case 3:
            setphutchieu(ConvertToInt(line), rapquanly.maychurap.danhsachphim[countphim]);
            break;
        case 4:
            setgiochieu(ConvertToInt(line), rapquanly.maychurap.danhsachphim[countphim]);
            break;
        case 5:
            setngaychieu(ConvertToInt(line), rapquanly.maychurap.danhsachphim[countphim]);
            break;
        case 6:
            setthangchieu(ConvertToInt(line), rapquanly.maychurap.danhsachphim[countphim]);
            break;
        case 7:
            setnamchieu(ConvertToInt(line), rapquanly.maychurap.danhsachphim[countphim]);
            break;
        case 8:
            setthoiluong(ConvertToInt(line), rapquanly.maychurap.danhsachphim[countphim]);
            break;
        case 9:
            setgioithieuphim(line, rapquanly.maychurap.danhsachphim[countphim]);
            break;
        case 0:
            setlinkanh(line, rapquanly.maychurap.danhsachphim[countphim]);
            break;
        default:
            break;
        }
        count++;
        if ((count % 11) == 0) {
            rapquanly.maychurap.danhsachphim[countphim].sethankhoichieu();
            if (countphim == 0) { setid("000", rapquanly.maychurap.danhsachphim[countphim]); }
            else {
                setid(increaseString(rapquanly.maychurap.danhsachphim[countphim - 1].getid()), rapquanly.maychurap.danhsachphim[countphim]);
            }
            countphim++;
        }
    }
    i.close();


    rapquanly.maychurap.sophim += countphim;
}

void admin::writesuatchieu(const string name_file) {
    ofstream o;
    o.open(name_file, ios::trunc);
    Time T;
    now n;
    n.gancho(T);
    for (int j = 0; j < 10; j++) {
        for (int k = 0; k < 3; k++) {
            for (int p = 0; p < 8; p++) {

                o << (rapquanly.danhsachphong)[j][k][p].suat.getidphim() << endl;
                o << rapquanly.getidphong((rapquanly.danhsachphong)[j][k][p].suat) << endl;
                o << (((rapquanly.danhsachphong)[j][k][p].suat.getthoigianchieu().trungay(T) + T.thungay) % 7) << endl;
                o << (rapquanly.danhsachphong)[j][k][p].suat.getthoigianchieu().getgio() << ":";
                o << (rapquanly.danhsachphong)[j][k][p].suat.getthoigianchieu().getphut() << " ";
                o << (rapquanly.danhsachphong)[j][k][p].suat.getthoigianchieu().getngay() << "/";
                o << (rapquanly.danhsachphong)[j][k][p].suat.getthoigianchieu().getthang() << "/";
                o << (rapquanly.danhsachphong)[j][k][p].suat.getthoigianchieu().getnam() << endl;
            }
        }
    }


    o.close();
}

void admin::nhapsuatchieu(string namefile)
{
    ifstream i;
    string tmpID;
    string tmpIDPhong;
    int j = 0, k = 0, o = 0, r = 0;
    string line;
    i.open(namefile, ios::in);
    if (!i.is_open()) return;
    int THUNGAY;
    Time tmpTime;
    int count = 1;
    while (getline(i, line)) {
        cout << line << endl;
        if (count % 4 == 1) {
            tmpID = line;
            count++;
        }
        else if (count % 4 == 2) {
            tmpIDPhong = line;
            count++;
        }
        else if (line.length() == 1) {
            THUNGAY = stoi(line);
            count++;
        }
        else {
            count++;
            j = tmpIDPhong[0] - 48;
            k = tmpIDPhong[1] - 48;
            size_t pos = 0;
            int gio = std::stoi(line, &pos);
            line = line.substr(pos + 1);

            // Láº¥y phÃºt
            int phut = std::stoi(line, &pos);
            line = line.substr(pos + 1);

            // Láº¥y ngÃ y
            int ngay = std::stoi(line, &pos);
            line = line.substr(pos + 1);

            // Láº¥y thÃ¡ng
            int thang = std::stoi(line, &pos);
            line = line.substr(pos + 1);
            // Láº¥y nÄƒm
            int nam = std::stoi(line);
            Time tmpTime(phut, gio, ngay, thang, nam, THUNGAY);

            r = getphimtuid(tmpID);
            (rapquanly.danhsachphong)[j][k - 1][o].suat.setidphim(tmpID);
            (rapquanly.danhsachphong)[j][k - 1][o].suat.setidphong(tmpIDPhong);
            (rapquanly.danhsachphong)[j][k - 1][o].suat.thoigianchieu = tmpTime;
            themsuatchieu(((rapquanly.danhsachphong)[j][k - 1][o].suat), (*(rapquanly.maychurap.danhsachphim + r)));
            o++;
            if (o >= 8) {
                o = 0;
            }

        }
        // Láº¥y giá»
    }
    i.close();
    rapquanly.ngaychieuphim = rapquanly.danhsachphong[0][0][0].suat.thoigianchieu;

}
void admin::xoaSuatChieu() {
    for (int i = 0; i < getsophim(); i++) {
        delete[] rapquanly.maychurap.danhsachphim[i].danhsachsuatchieu;
        rapquanly.maychurap.danhsachphim[i].sosuatchieu = 0;
    }


}
void admin::themphim(phim sc)
{
    if (rapquanly.maychurap.sophim == 0)
    {
        delete[] rapquanly.maychurap.danhsachphim;
        rapquanly.maychurap.danhsachphim = new phim[1];
        *(rapquanly.maychurap.danhsachphim + 0) = sc;
        setid("000", (*(rapquanly.maychurap.danhsachphim + 0)));
        rapquanly.maychurap.sophim++;
    }
    else
    {
        phim* tmp = new phim[rapquanly.maychurap.sophim + 1];
        for (int i = 0; i < rapquanly.maychurap.sophim; i++)
        {
            *(tmp + i) = *(rapquanly.maychurap.danhsachphim + i);
        }
        *(tmp + rapquanly.maychurap.sophim) = sc;
        delete[] rapquanly.maychurap.danhsachphim;
        rapquanly.maychurap.sophim++;
        rapquanly.maychurap.danhsachphim = new phim[rapquanly.maychurap.sophim];
        int r = 0;
        for (int i = 0; i < rapquanly.maychurap.sophim; i++)
        {
            *(rapquanly.maychurap.danhsachphim + i) = *(tmp + i);
        }
        r = rapquanly.maychurap.sophim - 1;
        setid(increaseString((*(rapquanly.maychurap.danhsachphim + (r - 1))).getid()), (*(rapquanly.maychurap.danhsachphim + r)));

        delete[] tmp;

    }
    now n;
    quanlychieuphim();
}
int admin::getsophim() {
    return rapquanly.maychurap.getsophim();
}
suatchieu admin::getsuat(int i, int j, int k) {
    return this->rapquanly.danhsachphong[i][j][k].suat;
}
phong admin::getphong(string s) {
    return rapquanly.getphong(s);
}