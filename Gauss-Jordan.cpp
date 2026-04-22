#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int main() {
    cout << "高斯喬登消去法計算程式" << endl;
    int n, m;
    cout << "請輸入矩陣的列:";
    cin >> n;
    cout << "請輸入矩陣的行:";
    cin >> m;

    vector<vector<double>> matrix(n, vector<double>(m));
    cout << "請輸入 " << n << " x " << m << " 的矩陣:" << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> matrix[i][j];
        }
    }

    int row = 0;
    for (int col = 0; col < m && row < n; ++col) {
        int maxRow = row;
        for (int k = row + 1; k < n; ++k) {
            if (abs(matrix[k][col]) > abs(matrix[maxRow][col])) {
                maxRow = k;
                }
        }
        if (abs(matrix[maxRow][col]) < 1e-9) {
            continue; 
            }
        swap(matrix[row], matrix[maxRow]);

        double pivot = matrix[row][col];
        for (int j = col; j < m; ++j) {
            matrix[row][j] /= pivot;
        }

        for (int k = 0; k < n; ++k) {
            if (k != row) {
                double factor = matrix[k][col];
                for (int j = col; j < m; ++j) {
                    matrix[k][j] -= factor * matrix[row][j];
                }
            }
        }
        
        row++; 
    }

    cout << "\n=== 簡化列列梯形 ===" << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            double val = matrix[i][j];
            if (abs(val) < 1e-9) val = 0; 
            cout << val << "\t";
        }
        cout << endl;
    }
    return 0;
}


