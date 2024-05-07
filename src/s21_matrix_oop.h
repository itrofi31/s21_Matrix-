#ifndef S21_MATRIX_OOP_H
#define S21_MATRIX_OOP_H

#include <iostream>
#include <utility>

class S21Matrix {
 private:
  int rows_, cols_;
  double** matrix_;
  void createMatrix();

 public:
  // default constructors
  S21Matrix();
  S21Matrix(int rows, int cols);

  // copy constructor
  S21Matrix(const S21Matrix& other);

  // move constructor

  // destructor
};

S21Matrix::S21Matrix() : rows_(0), cols_(0), matrix_(nullptr) {}

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (rows_ < 0 || cols_ < 0)
    throw std::invalid_argument("Rows and columns must be positive!");
  createMatrix();
}

S21Matrix::S21Matrix(const S21Matrix& other)
    : rows_(other.rows_), cols_(other.cols_) {
  createMatrix();
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
};

void S21Matrix::createMatrix() {
  if (rows_ == 0 && cols_ == 0)
    matrix_ = nullptr;
  else if (rows_ > 0 && cols_ > 0) {
    matrix_ = new double*[rows_];
    for (int i = 0; i < rows_; i++) matrix_[i] = new double[cols_];
  }
}
#endif