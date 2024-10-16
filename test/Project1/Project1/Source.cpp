#include <iostream>
#include <random>
#include <vector>

using namespace std;

void PrintMatr(vector<vector<double>> mas, int m, vector<double> mas2) {
    int i, j;
    for (i = 0; i < m; i++) {
        for (j = 0; j < m; j++) {

            cout << mas[i][j] << "x" << j+1 ;
            if (j < m-1) cout << " + ";
        }            
        cout << " = " << mas2[i];
        cout << endl;
    }
}


// Функция для вычисления определителя матрицы
double Determinant(const vector<vector<double>>& matrix, int n) {
    if (n == 1) {
        return matrix[0][0];
    }
    if (n == 2) {
        return matrix[0][0] * matrix[1][1] - matrix[1][0] * matrix[0][1];
    }

    double det = 0.0;
    vector<vector<double>> subMatrix(n - 1, vector<double>(n - 1)); // временная матрица

    for (int x = 0; x < n; x++) {
        // Получаем подматрицу
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (j < x) {
                    subMatrix[i - 1][j] = matrix[i][j];
                }
                else if (j > x) {
                    subMatrix[i - 1][j - 1] = matrix[i][j];
                }
            }
        }
        // Суммируем по специфическому правилу
        det += (x % 2 == 0 ? 1 : -1) * matrix[0][x] * Determinant(subMatrix, n - 1);
    }
    return det;
}


// Функция для решения системы уравнений методом Крамера
void SolveWithCramersRule(const vector<vector<double>>& mas, const vector<double>& mas2) {
    int m = mas.size();
    vector<double> x(m);

    // Вычисляем определитель основной матрицы
    double d0 = Determinant(mas, m);
    

    if (d0 != 0) {
        vector<vector<double>> tempMatrix = mas; // Копируем матрицу A

        for (int i = 0; i < m; i++) {
            // Заменяем i-тый столбец на вектор B
            for (int j = 0; j < m; j++) {
                tempMatrix[j][i] = mas2[j];
            }
            // Находим определитель новой матрицы
            double di = Determinant(tempMatrix, m);
            x[i] = di / d0; // Вычисляем x[i] по формуле Крамера
            tempMatrix = mas; // Восстанавливаем исходную матрицу для следующей итерации
        }

        for (int i = 0; i < m; i++) {
            cout << "x" << i + 1 << " = " << x[i] << '\n';
        }
    }
    else {
        cout << "Детерминант равен 0, решение методом Крамера невозможно.\n" << endl;
    }
}


// Функция для заполнения матрицы коэффициентов и вектора свободных членов
void FillMatrixAndVector(int& m, vector<vector<double>>& mas, vector<double>& mas2) {
    cout << "Введите количество неизвестных (строк в матрице): ";
    cin >> m;

    mas.resize(m, vector<double>(m)); // Сжимаем размеры матрицы коэффициентов
    mas2.resize(m); // Resize для вектора свободных членов

    cout << "Введите матрицу коэффициентов (размер " << m << "x" << m << "):\n";
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            cout << "A[" << i + 1 << "][" << j + 1 << "] = ";
            cin >> mas[i][j];
        }
    }

    cout << "Введите вектор свободных членов (размер " << m << "):\n";
    for (int i = 0; i < m; i++) {
        cout << "B[" << i + 1 << "] = ";
        cin >> mas2[i];
    }
}

// Функция для авто заполнения матрицы коэффициентов и вектора свободных членов
void AutoFillMatrixAndVector(int& m, vector<vector<double>>& mas, vector<double>& mas2) {
    cout << "Введите количество неизвестных (строк в матрице): ";
    cin >> m;

    mas.resize(m, vector<double>(m)); // Сжимаем размеры матрицы коэффициентов
    mas2.resize(m); // Resize для вектора свободных членов

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(0, 1000);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            mas[i][j] = dist(gen) / static_cast<float>(100);
        }
    }

    
    for (int i = 0; i < m; i++) {
        mas2[i] = dist(gen) / static_cast<float>(10);
    }
}

int main() {
    int m, i, j, O, choice;
    double d, d0;
    vector<double> mas2;
    double mas3[100];
    double x[100];
    vector<vector<double>> mas;
    system("chcp 1251");
    system("cls");
    cout << "Решение СЛАУ методом Камера \n";
    cout << "Для решение СЛАУ методом Камера необходимо что бы количество уравненй и количество неизвестных были равны \n";
    cout << "а так же детерминант основной матрицы небыл равен 0 \n";
    d0 = 0;
    m = 5;

    do
    {
        cout << endl;
        cout << "..............................." << endl;
        cout << " 1 - Ввести СЛАУ" << endl;
        cout << " 2 - Вывести СЛАУ" << endl;
        cout << " 3 - Решить СЛАУ" << endl;
        cout << " 4 - Найти определитель основной матрицы" << endl;
        cout << " 5 - Выход" << endl;
        cout << "..............................." << endl;
        cout << " > "; 
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "..............................." << endl;
            cout << " 1 - Ввести СЛАУ вручную" << endl;
            cout << " 2 - Ввести СЛАУ автоматически" << endl;
            cout << "..............................." << endl;
            cin >> O;
            if (O == 1) {
                FillMatrixAndVector(m, mas, mas2);
            }            
            else if (O == 2) {
                AutoFillMatrixAndVector(m, mas, mas2);
            }
            break;
        case 2:
            PrintMatr(mas, m, mas2);
            break;
        case 3:
            SolveWithCramersRule(mas, mas2);
            break;
        case 4:
            d0 = Determinant(mas, m);
            cout << "Определитель основной матрицы равен: " << d0 << '\n';
            break;
        }
    
    } while(choice != 5);

    return 0;
}
