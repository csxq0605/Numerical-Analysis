#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <functional>
#include <vector>
#include <algorithm>
using namespace std;

vector<double> F(const vector<double>& x){
    vector<double> f(3);
    f[0] = -(x[0] * x[0] + x[1] * x[1] + x[2] * x[2] - 1);
    f[1] = -(2 * x[0] * x[0] + x[1] * x[1] - 4 * x[2]);
    f[2] = -(3 * x[0] *x[0] - 4 * x[1] + x[2] * x[2]);
    return f;
}

vector<vector<double>> J(const vector<double>& x){
    vector<vector<double>> j(3, vector<double>(3));
    j[0][0] = 2 * x[0];
    j[0][1] = 2 * x[1];
    j[0][2] = 2 * x[2];
    j[1][0] = 4 * x[0];
    j[1][1] = 2 * x[1];
    j[1][2] = -4;
    j[2][0] = 6 * x[0];
    j[2][1] = -4;
    j[2][2] = 2 * x[2];
    return j;
}

vector<double> Add(const vector<double>& a, const vector<double>& b){
    vector<double> c(a.size());
    for (size_t i = 0; i < a.size(); i++) {
        c[i] = a[i] + b[i];
    }
    return c;
}

double norm(const vector<double>& x){
    double sum = 0;
    for (const double& val : x) {
        sum += val * val;
    }
    return sqrt(sum);
}

vector<double> solveLinearSystem(const vector<vector<double>>& A, const vector<double>& b) {
    int n = A.size();
    vector<vector<double>> augmented(n, vector<double>(n + 1));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            augmented[i][j] = A[i][j];
        }
        augmented[i][n] = b[i];
    }

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            double ratio = augmented[j][i] / augmented[i][i];
            for (int k = i; k < n + 1; k++) {
                augmented[j][k] -= ratio * augmented[i][k];
            }
        }
    }

    vector<double> x(n);
    for (int i = n - 1; i >= 0; i--) {
        x[i] = augmented[i][n];
        for (int j = i + 1; j < n; j++) {
            x[i] -= augmented[i][j] * x[j];
        }
        x[i] /= augmented[i][i];
    }
    return x;
}

vector<double> Newton(const vector<double>& x0, double epsilon, int max_iter){
    vector<double> x = x0;
    for (int i = 0; i < max_iter; i++) {
        vector<double> f = F(x);
        vector<vector<double>> j = J(x);
        vector<double> dx = solveLinearSystem(j, f);
        x = Add(x, dx);
        if (norm(dx) < epsilon) {
            return x;
        }
    }
    return x;
}

int main() {
    vector<double> x0 = {1.0, 1.0, 1.0};
    double epsilon = 1e-7;
    int max_iter = 100;

    vector<double> ans = Newton(x0, epsilon, max_iter);
    for (const double& val : ans) {
        cout << val << endl;
    }

    return 0;
}