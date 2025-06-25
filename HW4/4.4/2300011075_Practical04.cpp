#include <iostream>
#include <iomanip>
#include <fstream>
#include <ostream>
#include <Eigen/Core>
#include <cmath>
using namespace std;

//幂法
double powerMethod(Eigen::MatrixXd A, Eigen::VectorXd& x, int n, double tol, int maxIter) {
    Eigen::VectorXd y = Eigen::VectorXd::Zero(n);
    double error = tol + 1;
    double lambda;
    int iter = 0;
    double mu = 0.0;
    
    while (iter < maxIter and error > tol) {
        y = x;
        x = A * y;
        for (int i = 0; i < n; ++i) {
            if (abs(x[i]) > abs(lambda)){
                lambda = x[i];
            }
        }
        x /= lambda; // Normalize the vector
        error = abs(mu - lambda);
        mu = lambda;
        lambda = 0.0;
        ++iter;
    }
    
    return mu;
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
    double a;
    for (int i = 0; i < n; ++i){
        fin >> a;
        A(0, i) = -a;
    }
    for (int i = 1; i < n; ++i){
        A(i, i - 1) = 1;
    }

    // for (int i = 0; i < n; ++i) {
    //     for (int j = 0; j < n; ++j) {
    //         fin >> A(i, j);
    //     }
    // }

    // double lambda0;
    // fin >> lambda0;

    Eigen::VectorXd x = Eigen::VectorXd::Ones(n);
    double tol = 1e-9;
    int maxIter = 10000;
    double lambda = powerMethod(A, x, n, tol, maxIter);
    cout << setprecision(8) << scientific;
    cout << lambda << endl;
    // if (abs(lambda0 - lambda) < tol) {
    //     cout << "Eigenvalue is correct!" << endl;
    // } else {
    //     cout << "Eigenvalue is wrong!" << endl;
    // }
}