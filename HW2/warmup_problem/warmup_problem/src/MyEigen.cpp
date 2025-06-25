#include <iostream>
#include <fstream>  
#include <iomanip>  // 为了使用 std::setprecision  

#include "..\src\MyEigen.h"  

// 读取一个矩阵的函数实现
bool read_matrix_mxn_from_ifstream(std::ifstream& ifs, Eigen::MatrixXd& matrix)
{
  //// 根据文件路径打开文件, 并确认文件路径是否合法
  //std::ifstream file(filename);  
  //if (!file.is_open()) {  
  //  return false;  
  //}

  // 读入矩阵的 行数 列数
  unsigned nrow, ncol;
  ifs >> nrow >> ncol;

  matrix = Eigen::MatrixXd::Zero(nrow, ncol);
  for (int i = 0; i < matrix.rows(); ++i) {  
    for (int j = 0; j < matrix.cols(); ++j) {  
      ifs >> matrix(i, j);
    }
  }  
  
  return true;  
}

// 读取一个方阵的函数实现
bool read_matrix_nxn_from_ifstream(std::ifstream& ifs, Eigen::MatrixXd& matrix)
{
  // 读入矩阵的 行数
  unsigned nrow, ncol;
  ifs >> nrow;
  ncol = nrow;

  matrix = Eigen::MatrixXd::Zero(nrow, ncol);
  for (int i = 0; i < matrix.rows(); ++i) {
    for (int j = 0; j < matrix.cols(); ++j) {
      ifs >> matrix(i, j);
    }
  }

  return true;
}

// 打印矩阵的函数实现  
void print_matrix2screen(const Eigen::MatrixXd& matrix)
{  
  for (int i = 0; i < matrix.rows(); ++i) {  
    for (int j = 0; j < matrix.cols(); ++j) {  
      std::cout << std::scientific << std::setprecision(9) << matrix(i,j) << " ";
    }
    std::cout << std::endl;
  }  
}

void print_matrix2file(std::ofstream& ofs, const Eigen::MatrixXd& matrix)
{
  for (int i = 0; i < matrix.rows(); ++i) {
    for (int j = 0; j < matrix.cols(); ++j) {
      ofs << std::scientific << std::setprecision(9) << matrix(i, j) << " ";
    }
    ofs << std::endl;
  }
}

