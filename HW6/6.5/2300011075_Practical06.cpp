#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
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

    int n;
    fin >> n;

    int ans[n + 1][n + 1];
    for (int i = 0; i <= n; i++){
        for (int j = 0; j <= n; j++){
            ans[i][j] = 0;
        }
    }
    ans[1][1] = 1;

    for (int i = 2; i <= n; i++){
        ans[i][0] = ans[i - 1][1];
        ans[i][1] = ans[i - 1][2] + ans[i - 1][0] * 2;
        for (int j = 2; j < i; j++){
            ans[i][j] = ans[i - 1][j + 1] + ans[i - 1][j - 1];
        }
        ans[i][i] = ans[i - 1][i - 1];
    }

    for (int k = n; k <= n; k++){
        cout << "n = " << k << ": ";
        for (int i = k; i >= 0; i -= 2){
            cout << ans[k][i] << " ";
            }
        cout << endl;
    }
    
    fin.close();
    return 0;
}