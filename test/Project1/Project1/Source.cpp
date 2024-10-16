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


// ������� ��� ���������� ������������ �������
double Determinant(const vector<vector<double>>& matrix, int n) {
    if (n == 1) {
        return matrix[0][0];
    }
    if (n == 2) {
        return matrix[0][0] * matrix[1][1] - matrix[1][0] * matrix[0][1];
    }

    double det = 0.0;
    vector<vector<double>> subMatrix(n - 1, vector<double>(n - 1)); // ��������� �������

    for (int x = 0; x < n; x++) {
        // �������� ����������
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
        // ��������� �� �������������� �������
        det += (x % 2 == 0 ? 1 : -1) * matrix[0][x] * Determinant(subMatrix, n - 1);
    }
    return det;
}


// ������� ��� ������� ������� ��������� ������� �������
void SolveWithCramersRule(const vector<vector<double>>& mas, const vector<double>& mas2) {
    int m = mas.size();
    vector<double> x(m);

    // ��������� ������������ �������� �������
    double d0 = Determinant(mas, m);
    

    if (d0 != 0) {
        vector<vector<double>> tempMatrix = mas; // �������� ������� A

        for (int i = 0; i < m; i++) {
            // �������� i-��� ������� �� ������ B
            for (int j = 0; j < m; j++) {
                tempMatrix[j][i] = mas2[j];
            }
            // ������� ������������ ����� �������
            double di = Determinant(tempMatrix, m);
            x[i] = di / d0; // ��������� x[i] �� ������� �������
            tempMatrix = mas; // ��������������� �������� ������� ��� ��������� ��������
        }

        for (int i = 0; i < m; i++) {
            cout << "x" << i + 1 << " = " << x[i] << '\n';
        }
    }
    else {
        cout << "����������� ����� 0, ������� ������� ������� ����������.\n" << endl;
    }
}


// ������� ��� ���������� ������� ������������� � ������� ��������� ������
void FillMatrixAndVector(int& m, vector<vector<double>>& mas, vector<double>& mas2) {
    cout << "������� ���������� ����������� (����� � �������): ";
    cin >> m;

    mas.resize(m, vector<double>(m)); // ������� ������� ������� �������������
    mas2.resize(m); // Resize ��� ������� ��������� ������

    cout << "������� ������� ������������� (������ " << m << "x" << m << "):\n";
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            cout << "A[" << i + 1 << "][" << j + 1 << "] = ";
            cin >> mas[i][j];
        }
    }

    cout << "������� ������ ��������� ������ (������ " << m << "):\n";
    for (int i = 0; i < m; i++) {
        cout << "B[" << i + 1 << "] = ";
        cin >> mas2[i];
    }
}

// ������� ��� ���� ���������� ������� ������������� � ������� ��������� ������
void AutoFillMatrixAndVector(int& m, vector<vector<double>>& mas, vector<double>& mas2) {
    cout << "������� ���������� ����������� (����� � �������): ";
    cin >> m;

    mas.resize(m, vector<double>(m)); // ������� ������� ������� �������������
    mas2.resize(m); // Resize ��� ������� ��������� ������

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
    cout << "������� ���� ������� ������ \n";
    cout << "��� ������� ���� ������� ������ ���������� ��� �� ���������� �������� � ���������� ����������� ���� ����� \n";
    cout << "� ��� �� ����������� �������� ������� ����� ����� 0 \n";
    d0 = 0;
    m = 5;

    do
    {
        cout << endl;
        cout << "..............................." << endl;
        cout << " 1 - ������ ����" << endl;
        cout << " 2 - ������� ����" << endl;
        cout << " 3 - ������ ����" << endl;
        cout << " 4 - ����� ������������ �������� �������" << endl;
        cout << " 5 - �����" << endl;
        cout << "..............................." << endl;
        cout << " > "; 
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "..............................." << endl;
            cout << " 1 - ������ ���� �������" << endl;
            cout << " 2 - ������ ���� �������������" << endl;
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
            cout << "������������ �������� ������� �����: " << d0 << '\n';
            break;
        }
    
    } while(choice != 5);

    return 0;
}
