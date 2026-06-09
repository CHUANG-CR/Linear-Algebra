#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

// === 引用 HW04 的基礎運算 ===
double dotProduct(const vector<double>& v1, const vector<double>& v2) {
    double sum = 0.0;
    for (size_t i = 0; i < v1.size(); ++i) sum += v1[i] * v2[i];
    return sum;
}

vector<double> scalarMultiply(double scalar, const vector<double>& v) {
    vector<double> result(v.size());
    for (size_t i = 0; i < v.size(); ++i) result[i] = scalar * v[i];
    return result;
}

vector<double> vectorSubtract(const vector<double>& v1, const vector<double>& v2) {
    vector<double> result(v1.size());
    for (size_t i = 0; i < v1.size(); ++i) result[i] = v1[i] - v2[i];
    return result;
}

vector<vector<double>> gramSchmidt(const vector<vector<double>>& A) {
    if (A.empty()) return {};
    int m = A.size();
    int n = A[0].size();
    vector<vector<double>> U(m, vector<double>(n, 0.0));
    
    for (int j = 0; j < n; ++j) {
        vector<double> a_j(m), u_j(m);
        for (int i = 0; i < m; ++i) a_j[i] = u_j[i] = A[i][j];
        
        for (int k = 0; k < j; ++k) {
            vector<double> u_k(m);
            for (int i = 0; i < m; ++i) u_k[i] = U[i][k];
            double uk_dot_uk = dotProduct(u_k, u_k);
            if (uk_dot_uk > 1e-9) {
                double proj_scalar = dotProduct(a_j, u_k) / uk_dot_uk;
                u_j = vectorSubtract(u_j, scalarMultiply(proj_scalar, u_k));
            }
        }
        for (int i = 0; i < m; ++i) U[i][j] = u_j[i];
    }
    return U;
}

// === 驗證主程式 ===
int main() {
    int N = 101; // 取樣點數 (大於100點)
    vector<vector<double>> A(N, vector<double>(3));
    vector<double> x_vals(N);
    
    // 1. 建立標準基底 1, x, x^2 的取樣矩陣
    for (int i = 0; i < N; ++i) {
        double x = -1.0 + 2.0 * i / (N - 1); // 均勻分佈於 [-1, 1]
        x_vals[i] = x;
        A[i][0] = 1.0;       // 基底 1
        A[i][1] = x;         // 基底 x
        A[i][2] = x * x;     // 基底 x^2
    }

    // 2. 進行葛蘭-史密特正交化
    vector<vector<double>> U = gramSchmidt(A);

    // 3. 輸出結果與理論值(雷建德多項式)進行驗證比對
    cout << "雷建德多項式正交化驗證 (取樣點數: " << N << " 點)\n";
    cout << "-----------------------------------------------------------------------\n";
    cout << setw(8) << "x" 
         << setw(15) << "U0 (應為1)" 
         << setw(15) << "U1 (應為x)" 
         << setw(25) << "U2 (近似 x^2 - 1/3)" << "\n";
    cout << "-----------------------------------------------------------------------\n";
    
    // 只印出部分代表性的點位 (頭、中間、尾) 避免畫面過長
    int sample_indices[] = {0, 25, 50, 75, 100};
    
    for (int idx : sample_indices) {
        double x = x_vals[idx];
        double theoretical_P2 = x * x - 1.0 / 3.0; // 理論的 P2(x)
        
        cout << fixed << setprecision(4);
        cout << setw(8) << x 
             << setw(15) << U[idx][0] 
             << setw(15) << U[idx][1] 
             << setw(15) << U[idx][2] 
             << "  (理論值: " << setw(7) << theoretical_P2 << ")\n";
    }

    return 0;
}
