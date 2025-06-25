#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <Eigen/Core>
using namespace std;

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

    // ifstream fin("input.dat");

    int n;
    double lambda;
    fin >> n >> lambda;

    Eigen::MatrixXd S = Eigen::MatrixXd::Zero(n, n);
    Eigen::MatrixXd T = Eigen::MatrixXd::Zero(n, n);
    Eigen::VectorXd b = Eigen::VectorXd::Zero(n);
    Eigen::VectorXd x = Eigen::VectorXd::Zero(n);
    Eigen::VectorXd z = Eigen::VectorXd::Zero(n);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            fin >> S(i, j);
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            fin >> T(i, j);
        }
    }

    for (int i = 0; i < n; ++i) {
        fin >> b[i];
    }

    for (int i = n - 1; i >= 0; i--){
        double sumT = 0.0;
        for (int j = i + 1; j < n; j++){
            sumT += T(i, j) * x[j];
        }

        double sumS = 0.0;
        for (int j = i + 1; j < n; j++){
            sumS += S(i, j) * z[j];
        }

        double denominator = S(i, i) * T(i, i) - lambda;
        double numerator = b[i] - sumS - S(i, i) * sumT;
        x[i] = numerator / denominator;

        z[i] = T(i, i) * x[i] + sumT;
    }

    cout << scientific << setprecision(9);
    for (int i = 0; i < n; i++){
        cout << x[i] << " ";
    }
    cout << endl;
    return 0;
}