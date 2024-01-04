#include "../header/rap.h"
rap::rap()
{
    tenrap = "A";
    diachi = "A";
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 8; k++) {
                danhsachphong[i][j][k].idphong = (string(1, (char)(i + 48)) + string(1, (char)(j + 48 + 1)) + string(1, (char)(k + 48 + 1)));

            }
        }
    }
}
rap::~rap() {
}
string rap::gettenrap() { return tenrap; }
string rap::getdiachi() { return diachi; }
phong rap::getphong(int i, int j, int k) { return danhsachphong[i][j][k]; }
maychu rap::getmaychu() { return maychurap; }
Time rap::getngaychieuphim() { return ngaychieuphim; }
void rap::datlaiphim() {
    now n;
    Time homnay;
    n.gancho(homnay);
    int count = 0;
    Time max;
    max = homnay;
    for (int i = 0; i < 10; i++) {
        if (homnay > danhsachphong[i][0][0].suat.getthoigianchieu()) {
            count++;
        }
        if (danhsachphong[i][0][0].suat.getthoigianchieu() > max) {
            max = danhsachphong[i][0][0].suat.getthoigianchieu();
        }

    }
    for (int i = 0; i < count; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 8; k++) {
                danhsachphong[i][j][k].suat.getthoigianchieu().congngay(max, (i + 1));
            }
        }
    }
}
string rap::getidphong(suatchieu sc) {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 8; k++) {
                if (sc == danhsachphong[i][j][k].suat) {
                    return danhsachphong[i][j][k].getidphong();
                }
            }
        }
    }
}
phong rap::getphong(string idphong) {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 8; k++) {
                if (danhsachphong[i][j][k].getidphong() == idphong) {
                    return danhsachphong[i][j][k];
                }
            }
        }
    }
}