#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <functional>
#include <vector>
#include <algorithm>
using namespace std;

double integrand(double u, double p) {
    if (u <= 0.0 || u >= 1.0) {
        return 0.0;
    }
    double tmp1 = pow(u, 1.0 - p);
    double tmp2 = pow(1.0 - u, 1.0 - p);
    return pow(tmp1 + tmp2, 1.0 / p);
}

double adaptiveSimpson(function<double(double)> f, double a, double b, double epsilon, int maxDepth) {
    function<double(double, double, double, int)> adaptive = 
        [&](double a, double b, double whole, int depth){
            double c = (a + b) / 2;
            double left = (c - a) / 6 * (f(a) + 4 * f((a + c) / 2) + f(c));
            double right = (b - c) / 6 * (f(c) + 4 * f((c + b) / 2) + f(b));
            double total = left + right;
            
            if (depth >= maxDepth || fabs(total - whole) <= 15 * epsilon) {
                return total + (total - whole) / 15;
            }
            
            return adaptive(a, c, left, depth + 1) + adaptive(c, b, right, depth + 1);
        };
    
    double whole = (b - a) / 6 * (f(a) + 4 * f((a + b) / 2) + f(b));
    return adaptive(a, b, whole, 0);
}

double calculatePi(double p) {
    if (p > 2.0) {
        double q = p / (p - 1.0);
        return calculatePi(q);
    }

    double delta = 1e-15;
    double epsilon = 1e-20;
    int maxDepth = 50;      
    auto f = [p](double u){ return integrand(u, p);};

    double integral = adaptiveSimpson(f, delta, 1.0 - delta, epsilon, maxDepth);
    return 2.0 / p * integral;
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

    double p;
    fin >> p;

    double pi_p = calculatePi(p);
    cout << fixed << setprecision(9) << pi_p << endl;

    // double ps[6];
    // for (int i = 0; i < 6; i++) {
    //     fin >> ps[i];
    // }

    // for (int i = 0; i < 6; i++) {
    //     double p = ps[i];
    //     double pi_p = calculatePi(p);
    //     cout << fixed << setprecision(9) << pi_p << endl;
    // }

    fin.close();
    return 0;
}