#ifndef MYEIGEN_H    
#define MYEIGEN_H    
  
#include <string>  
#include "Eigen/Core"

// 读取矩阵的函数声明  
bool read_matrix_mxn_from_ifstream(std::ifstream& ifs, Eigen::MatrixXd& matrix);
bool read_matrix_nxn_from_ifstream(std::ifstream& ifs, Eigen::MatrixXd& matrix);

void print_matrix2screen(const Eigen::MatrixXd& matrix);
void print_matrix2file(std::ofstream& ofs, const Eigen::MatrixXd& matrix);

#endif // MYEIGEN_H  

