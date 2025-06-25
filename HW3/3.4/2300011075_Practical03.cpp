#include <iostream>
#include <iomanip>
#include <fstream>
#include <ostream>
#include <string>
#include <Eigen/Core>
using namespace std;

int GuassSeidal(Eigen::MatrixXd A, Eigen::VectorXd b, Eigen::VectorXd& x, int n, double tol, int maxIter) {
    Eigen::VectorXd y = Eigen::VectorXd::Zero(n);
    int iter = 0;
    double error = tol + 1;
    while (error > tol && iter < maxIter) {
        y = x;
        for (int i = 0; i < n; ++i) {
            x[i] = b[i];
            for (int j = 0; j < i; ++j) {
                x[i] -= A(i, j) * x[j];
            }
            for (int j = i + 1; j < n; ++j) {
                x[i] -= A(i, j) * y[j];
            }
            x[i] /= A(i, i);
        }
        error = (x - y).norm();
        ++iter;
    }
    return iter;
}

int homework(Eigen::MatrixXd A, Eigen::VectorXd b, Eigen::VectorXd& x, int n, double tol, int maxIter) {
    Eigen::VectorXd y = Eigen::VectorXd::Zero(n);
    int iter = 0;
    double error = tol + 1;
    while (error > tol && iter < maxIter) {
        y = x;
        for (int i = 0; i < n; ++i) {
            x[i] = b[i];
            for (int j = 0; j < i; ++j) {
                x[i] -= A(i, j) * x[j];
            }
            for (int j = i + 1; j < n; ++j) {
                x[i] -= A(i, j) * y[j];
            }
            x[i] /= A(i, i);
        }
        y = x;
        for (int i = n - 1; i >= 0; i--){
            x[i] = b[i];
            for (int j = 0; j < i; ++j){
                x[i] -= A(i, j) * y[j];
            }
            for (int j = i + 1; j < n; j++){
                x[i] -= A(i, j) * x[j];
            }
            x[i] /= A(i, i);
        }
        error = (x - y).norm();
        ++iter;
    }
    return iter;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        std::exit(EXIT_FAILURE);  
    }
      
    string filename = argv[1];
    ifstream fin(filename);   
    if (!fin.is_open()) {
        cout << "Error: Could not open " << filename << endl;
        return 0;
    }

    int n;
    fin >> n;

    Eigen::MatrixXd A = Eigen::MatrixXd::Zero(n, n);
    Eigen::VectorXd b = Eigen::VectorXd::Zero(n);
    Eigen::VectorXd x1 = Eigen::VectorXd::Zero(n);
    Eigen::VectorXd x2 = Eigen::VectorXd::Zero(n);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            fin >> A(i, j);
        }
    }

    for (int i = 0; i < n; ++i) {
        fin >> b[i];
    }

    double tol = 1e-9;
    int maxIter = 10000;

    int iter1 = GuassSeidal(A, b, x1, n, tol, maxIter);
    int iter2 = homework(A, b, x2, n, tol, maxIter);

    cout << iter1 << endl;
    cout << scientific << setprecision(8);
    for (int i = 0; i < n; ++i) {
        cout << x1[i] << " ";
    }
    cout << endl;
    cout << iter2 << endl;
    cout << scientific << setprecision(8);
    for (int i = 0; i < n; ++i) {
        cout << x2[i] << " ";
    }
    cout << endl;

    return 0;
}