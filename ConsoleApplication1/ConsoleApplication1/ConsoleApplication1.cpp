#include <iostream>

using namespace std;


// Получение матрицы без i-й строки и j-го столбца
void GetMatr(double** mas, double** p, int i, int j, int m) {
    int ki, kj, di, dj;
    di = 0;
    for (ki = 0; ki < m - 1; ki++) { // проверка индекса строки
        if (ki == i) di = 1;
        dj = 0;
        for (kj = 0; kj < m - 1; kj++) { // проверка индекса столбца
            if (kj == j) dj = 1;
            p[ki][kj] = mas[ki + di][kj + dj];
        }
    }
}


int main() {
    int m, i, j, O;
    double d, d0;
    int mas2[100];
    int mas3[100];
    double x[100];
    double** mas;
    system("chcp 1251");
    system("cls");
    cout << "Решение СЛАУ методом Камера \n";
    cout << "Для решение СЛАУ методом Камера необходимо что бы количество уравненй и количество неизвестных были равны \n";
    cout << "а так же детерминант основной матрицы небыл равен 0 \n";
    cout << "Введите количество неизвестных (уравнений): ";
    cin >> m;
    while (m < 2) {
        cout << "это не СЛАУ ! \n" << "Введите число больше или равное двум \n";
        cin >> m;
    }
    mas = new double* [m];
    double** p;
    p = new double* [m];
    for (i = 0; i < m; i++) {
        mas[i] = new double[m];
        cout << "коэфиценты неизвестных в " << i + 1 << " уравнении" << '\n';
        for (j = 0; j < m; j++) {

            cin >> mas[i][j];
        }
    }
    if (m > 2) {
        for (i = 0; i < m; i++) {
            GetMatr(mas, p, i, 0, m);

        }
        for (i = 0; i < m; i++) {
            for (j = 0; j < m; j++)
                cout << mas[i][j] << " ";
            cout << endl;
        }
    }
}