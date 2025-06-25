#include <iostream>
#include <fstream>  
#include "MyEigen.h"

int main(int argc, char* argv[]) {

  // 确认从命令行传递的输入项的项数是否为 2
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
    std::exit(EXIT_FAILURE);        // 如果参数数量不正确，则退出程序  
  }

  std::string filename = argv[1];   // 从命令行参数中获取文件名 
  std::ifstream file(filename);     // 定义输入流
  if (!file.is_open()) {  
    return false;  
  }

  // 定义空矩阵并 读取矩阵  
  Eigen::MatrixXd matrix;
  if (!read_matrix_nxn_from_ifstream(file, matrix)) {
    std::cerr << "Failed to read matrix from file." << std::endl;
    std::exit(EXIT_FAILURE); // 如果读取失败，则退出程序  
  }
  file.close();

  // LU 分解
  for (int k = 0; k < matrix.cols() - 1; k++) {
    for (int i = k + 1; i < matrix.cols(); i++) {
      matrix(i, k) = matrix(i, k) / matrix(k, k);
    }
    for (int i = k + 1; i < matrix.cols(); i++) {
      for (int j = k + 1; j < matrix.cols(); j++) {
        matrix(i, j) = matrix(i, j) - matrix(i, k) * matrix(k, j);
      }
    }
  }

  // 打印矩阵  
  print_matrix2screen(matrix);

  return 0;
}

