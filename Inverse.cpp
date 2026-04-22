#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int main() {
    cout << "反矩陣計算程式" << endl;
    int m, n;
    cout << "輸入行:";
    cin >> m;
    cout << "輸入列:";
    cin >> n;

    if (m != n) {
        cout << "反矩陣不存在\n";
        return 0;
    }

    double** A = new double*[m];
    for (int i = 0; i < m; i++) {
        A[i] = new double[2 * n]();
    }

    cout << "輸入矩陣:\n";
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> A[i][j];
        }
        A[i][n + i] = 1.0;
    }

    int k = 0;
    for (int c = 0; c < n && k < m; c++) {
        int p = k;

        for (int i = k + 1; i < m; i++) {
            if (abs(A[i][c]) > abs(A[p][c])) {
                p = i;
            }
        }

        if (abs(A[p][c]) < 1e-9) {
            cout << "反矩陣不存在！\n";
            for (int i = 0; i < m; i++) delete[] A[i];
            delete[] A;
            return 0;
        }

        if (p != k) {
            for (int j = 0; j < 2 * n; j++) {
                double temp = A[k][j];
                A[k][j] = A[p][j];
                A[p][j] = temp;
            }
        }

        double pivot = A[k][c];
        for (int j = c; j < 2 * n; j++) {
            A[k][j] /= pivot;
        }

        for (int i = 0; i < m; i++) {
            if (i != k) {
                double factor = A[i][c];
                for (int j = c; j < 2 * n; j++) {
                    A[i][j] -= factor * A[k][j];
                }
            }
        }
        k++;
    }

    cout << "\n=== 反矩陣 ===\n" << endl;
    cout << fixed << setprecision(3);
    for (int i = 0; i < m; i++) {
        for (int j = n; j < 2 * n; j++) {
            double val = A[i][j];
            if (abs(val) < 1e-9) val = 0.000;
            cout << val << "\t";
        }
        cout << "\n";
    }

    return 0;
}
