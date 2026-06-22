#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

// 1. 計算兩向量內積 (Dot Product)
// 對應數學公式中的 <a, b>
double dotProduct(const vector<double>& a, const vector<double>& b) {
    double sum = 0;
    for (size_t i = 0; i < a.size(); ++i) {
        sum += a[i] * b[i];
    }
    return sum;
}

// 2. 向量的純量乘法
// 將算出的分數比例乘上基準向量
vector<double> scalarMultiply(double scalar, const vector<double>& vec) {
    vector<double> result(vec.size());
    for (size_t i = 0; i < vec.size(); ++i) {
        result[i] = scalar * vec[i];
    }
    return result;
}

// 3. 向量減法
// 用於扣除投影影子: u - proj
vector<double> subtract(const vector<double>& a, const vector<double>& b) {
    vector<double> result(a.size());
    for (size_t i = 0; i < a.size(); ++i) {
        result[i] = a[i] - b[i];
    }
    return result;
}

int main() {
    int dim;
    
    // --- 輸入設定 ---
    cout << "請輸入陣列的維度 (例如 3 代表三個 3 維向量): ";
    cin >> dim;

    if (dim <= 0) {
        cout << "維度必須大於 0 喔！" << endl;
        return 1;
    }

    // 建立二維的 vector 來儲存初始基底 u 與正交基底 v
    vector<vector<double>> u(dim, vector<double>(dim));
    vector<vector<double>> v(dim, vector<double>(dim));

    cout << "\n請依序輸入 " << dim << " 個基底向量的數值：" << endl;
    for (int i = 0; i < dim; ++i) {
        cout << "請輸入第 " << i + 1 << " 個向量 (請以空白分隔 " << dim << " 個數值): ";
        for (int j = 0; j < dim; ++j) {
            cin >> u[i][j];
        }
    }

    // --- 核心演算法：葛蘭-史密特正交化程序 ---
    for (int i = 0; i < dim; ++i) {
        v[i] = u[i]; // 先假設新向量 v_i 就是初始向量 u_i
        
        // 進入內層迴圈：依序減去前面所有已經求出的 v_j 的投影
        for (int j = 0; j < i; ++j) {
            double num = dotProduct(u[i], v[j]);     // 分子：<u_i, v_j>
            double den = dotProduct(v[j], v[j]);     // 分母：<v_j, v_j>
            
            if (den == 0) {
                // 避免分母為 0 的崩潰 (通常代表使用者輸入了平行或全為 0 的向量)
                continue;
            }
            
            double coeff = num / den;                // 計算投影比例 (純量)
            vector<double> proj = scalarMultiply(coeff, v[j]); // 生成投影向量
            v[i] = subtract(v[i], proj);             // 扣除該投影影子
        }
    }

    // --- 輸出 ---
    cout << "\n--- 計算完成：各維度的正交基底 ---" << endl;
    cout << fixed << setprecision(4); // 設定小數點後顯示四位，版面比較整齊
    for (int i = 0; i < dim; ++i) {
        cout << "v" << i + 1 << " = [ ";
        for (int j = 0; j < dim; ++j) {
            // 若數字非常趨近於 0 (例如 -0.0000)，強制顯示為 0 避免混淆
            if (abs(v[i][j]) < 1e-9) v[i][j] = 0.0;
            cout << v[i][j] << " ";
        }
        cout << "]" << endl;
    }

    return 0;
}
