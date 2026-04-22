#include <iostream>
#include <iomanip>

using namespace std;

int main() {
    cout << "高斯喬登消去法求簡化列梯形" << endl;
    int n, m;
    cout << "請輸入矩陣的列:";
    cin >> n;
    cout << "請輸入矩陣的行:";
    cin >> m;

    double** A = new double*[m];
    for (int i = 0; i < m; i++) {
        A[i] = new double[n];
    }

    cout << "輸入矩陣:\n";
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            cin >> A[i][j];

    int k = 0;
    for (int c = 0; c < n && k < m; c++) {
        int p = k;
        while (p < m && A[p][c] == 0) p++;
        if (p == m) continue;

        if (p != k) {
            for (int j = 0; j < n; j++) {
                double temp = A[k][j];
                A[k][j] = A[p][j];
                A[p][j] = temp;
            }
        }

        double div = A[k][c];
        for (int j = c; j < n; j++) {
            A[k][j] /= div;
        }

        for (int i = 0; i < m; i++) {
            if (i == k) continue;
            double mul = A[i][c];
            for (int j = c; j < n; j++) {
                A[i][j] -= mul * A[k][j];
            }
        }
        k++;
    }

    cout << "\n=== 簡化列列梯形 ===" << endl;
    cout << fixed << setprecision(3);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            double val = A[i][j];
            if (val > -0.0001 && val < 0.0001) val = 0.000;
            cout << setw(8) << val << " ";
        }
        cout << "\n";
    }
    return 0;
}
