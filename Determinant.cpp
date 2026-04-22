#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

int main() {
    int n, m;
    cout << "計算行列式值" << endl;
    cout << "請輸入矩陣的列:";
    cin >> n;
    cout << "請輸入矩陣的行: ";
    cin >> m;

    if (n != m) {
        cout << "無行列式值" << endl;
        return 0; 
    }

    vector<vector<double>> matrix(n, vector<double>(n));

    cout << "請輸入 " << n << " x " << m << " 的矩陣:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> matrix[i][j];
        }
    }

    double det = 1.0;

    for (int i = 0; i < n; i++) {
        int pivotRow = i;
        for (int j = i + 1; j < n; j++) {
            if (abs(matrix[j][i]) > abs(matrix[pivotRow][i])) {
                pivotRow = j;
            }
        }

        if (abs(matrix[pivotRow][i]) < 1e-9) {
            det = 0.0;
            break;
        }

        if (pivotRow != i) {
            swap(matrix[i], matrix[pivotRow]);
            det *= -1.0;
        }

        for (int j = i + 1; j < n; j++) {
            double factor = matrix[j][i] / matrix[i][i];
            for (int k = i; k < n; k++) {
                matrix[j][k] -= factor * matrix[i][k];
            }
        }

        det *= matrix[i][i];
    }

    if (abs(det) < 1e-9) det = 0.0;

    cout << fixed << setprecision(4) << endl; 
    cout << "行列式值= " << det << endl;

    return 0;
}
