#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

// 計算兩個向量的內積
double dotProduct(const vector<double>& v1, const vector<double>& v2) {
    double sum = 0.0;
    for (size_t i = 0; i < v1.size(); ++i) {
        sum += v1[i] * v2[i];
    }
    return sum;
}

// 向量純量乘法
vector<double> scalarMultiply(double scalar, const vector<double>& v) {
    vector<double> result(v.size());
    for (size_t i = 0; i < v.size(); ++i) {
        result[i] = scalar * v[i];
    }
    return result;
}

// 向量減法
vector<double> vectorSubtract(const vector<double>& v1, const vector<double>& v2) {
    vector<double> result(v1.size());
    for (size_t i = 0; i < v1.size(); ++i) {
        result[i] = v1[i] - v2[i];
    }
    return result;
}

// 葛蘭-史密特正交程序
// 輸入：m x n 矩陣 A
// 輸出：m x n 矩陣 U (行向量為正交向量)
vector<vector<double>> gramSchmidt(const vector<vector<double>>& A) {
    if (A.empty()) return {};
    
    int m = A.size();       // 列數 (維度)
    int n = A[0].size();    // 行數 (向量個數)
    
    // 初始化輸出矩陣 U 為 m x n 的零矩陣
    vector<vector<double>> U(m, vector<double>(n, 0.0));
    
    for (int j = 0; j < n; ++j) {
        // 1. 提取矩陣 A 的第 j 個行向量 a_j
        vector<double> a_j(m);
        for (int i = 0; i < m; ++i) {
            a_j[i] = A[i][j];
        }
        
        vector<double> u_j = a_j;
        
        // 2. 減去 a_j 在前面已經正交化的所有向量 u_k 上的投影
        for (int k = 0; k < j; ++k) {
            // 提取矩陣 U 的第 k 個行向量 u_k
            vector<double> u_k(m);
            for (int i = 0; i < m; ++i) {
                u_k[i] = U[i][k];
            }
            
            double uk_dot_uk = dotProduct(u_k, u_k);
            
            // 避免除以零：如果 u_k 是零向量 (長度極小)，則跳過投影計算
            if (uk_dot_uk > 1e-9) {
                // 投影係數 = (a_j 內積 u_k) / (u_k 內積 u_k)
                double proj_scalar = dotProduct(a_j, u_k) / uk_dot_uk;
                vector<double> proj_vec = scalarMultiply(proj_scalar, u_k);
                u_j = vectorSubtract(u_j, proj_vec);
            }
        }
        
        // 3. 將計算出的正交向量 u_j 存入矩陣 U 的第 j 行
        for (int i = 0; i < m; ++i) {
            U[i][j] = u_j[i];
        }
    }
    
    return U;
}

// 輔助函式：印出矩陣
void printMatrix(const vector<vector<double>>& matrix) {
    for (const auto& row : matrix) {
        for (double val : row) {
            // 處理浮點數誤差，將極小的值顯示為 0
            if (abs(val) < 1e-9) val = 0.0;
            cout << setw(10) << fixed << setprecision(4) << val << " ";
        }
        cout << endl;
    }
}

int main() {
    // 測試範例：m = 2, n = 3 (n > m)
    // 矩陣 A = [ 1  2  3 ]
    //          [ 1  0  1 ]
    vector<vector<double>> A = {
        {1.0, 2.0, 3.0},
        {1.0, 0.0, 1.0}
    };

    cout << "原始矩陣 A (" << A.size() << "x" << A[0].size() << "):" << endl;
    printMatrix(A);
    cout << "\n----------------------------------\n";

    vector<vector<double>> U = gramSchmidt(A);

    cout << "正交化後的矩陣 U (" << U.size() << "x" << U[0].size() << "):" << endl;
    printMatrix(U);

    return 0;
}
