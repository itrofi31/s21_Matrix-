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
  S21Matrix() noexcept;
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other) noexcept;
  ~S21Matrix() noexcept;

  // setters and getters
  int GetRows() noexcept;
  int GetCols() noexcept;
  void SetRows(int rows);
  void SetCols(int cols);

  // assignment operator overload
  S21Matrix& S21Matrix::operator=(const S21Matrix& other);
  S21Matrix& S21Matrix::operator=(S21Matrix&& other);

  // index operator overload
  double& S21Matrix::operator()(int row, int col);
};

// default constructors

S21Matrix::S21Matrix() noexcept : rows_(0), cols_(0), matrix_(nullptr) {}

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (rows_ < 0 || cols_ < 0)
    throw std::invalid_argument("Rows and columns must be positive!");
  createMatrix();
}

// copy constructor
S21Matrix::S21Matrix(const S21Matrix& other)
    : rows_(other.rows_), cols_(other.cols_) {
  createMatrix();
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
};

// move constructor
S21Matrix::S21Matrix(S21Matrix&& other) noexcept
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  other.rows_ = 0;
  other.cols_ = 0;
  other.matrix_ = nullptr;
}

// destructor
S21Matrix::~S21Matrix() noexcept {
  if (matrix_) {
    for (int i = 0; i < rows_; i++)
      if (matrix_[i]) delete[] matrix_[i];
    delete[] matrix_;
  }
}

// assignment operator overload
S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
  if (this == &other) return *this;

  S21Matrix copy(other);
  *this = std::move(copy);
  return *this;
}

S21Matrix& S21Matrix::operator=(S21Matrix&& other) {
  if (this != &other) {
    if (matrix_) {
      for (int i = 0; i < rows_; i++)
        if (matrix_[i]) delete[] matrix_[i];
      delete[] matrix_;
      matrix_ = nullptr;
    }

    std::swap(rows_, other.rows_);
    std::swap(cols_, other.cols_);
    std::swap(matrix_, other.matrix_);
  }
  return *this;
}

// index operator overload
double& S21Matrix::operator()(int row, int col) {
  if (row < 0 || col < 0 || row >= rows_ || col >= cols_)
    throw std::out_of_range("Out of range");

  return matrix_[row][col];
}

// setters and getters
int S21Matrix::GetRows() noexcept { return rows_; }

int S21Matrix::GetCols() noexcept { return cols_; }

void S21Matrix::SetRows(int rows) {
  if (rows < 0) {
    throw std::length_error("Rows must be a positive number");

    if (rows != rows_) {
      S21Matrix copy(rows, cols_);
      for (int i = 0; i < rows && i < rows_; i++)
        for (int j = 0; j < cols_; j++) copy(i, j) = (*this)(i, j);
    }
  }
}

void S21Matrix::SetCols(int cols) {
  if (cols < 0) {
    throw std::length_error("Cols must be a positive number");

    if (cols != cols_) {
      S21Matrix copy(rows_, cols);
      for (int i = 0; i < rows_; i++)
        for (int j = 0; j < cols_ && j < cols; j++) copy(i, j) = (*this)(i, j);
    }
  }
}

bool S21Matrix::EqMatrix(const S21Matrix& other) const noexcept {
  if (rows_ != other.rows_ || cols_ != other.cols_) return false;
  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_; j++)
      if (std::fabs(this->matrix_[i][j] - other.matrix_[i][j]) > 1e-7)
        return false;
  return true;
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_)
    throw std::logic_error("Matrices have different size");
  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_; j++) {
      (*this)(i, j) += other(i, j);
    }
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_)
    throw std::logic_error("Matrices have different size");
  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_; j++) {
      (*this)(i, j) -= other(i, j);
    }
}

void S21Matrix::MulNumber(const double num) noexcept {
  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_; j++) {
      (*this)(i, j) *= num;
    }
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (cols_ != other.rows_)
    throw std::logic_error(
        "Incorrect size of matrices, rows must be equal to columns");

  S21Matrix result(rows_, other.cols_);
  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < other.cols_; j++) {
      result(i, j) = 0;
      for (int k = 0; k < cols_; k++)
        result(i, j) += (*this)(i, k) * other(k, j);
    }
  *this = std::move(result);
}

S21Matrix S21Matrix::Transpose() {
  S21Matrix result(cols_, rows_);
  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_; j++) {
      result(j, i) = (*this)(i, j);
    }
  return result;
}

S21Matrix S21Matrix::CalcComplements() {}
double S21Matrix::Determinant() {}
S21Matrix S21Matrix::InverseMatrix() {}

void S21Matrix::createMatrix() {
  if (rows_ == 0 && cols_ == 0)
    matrix_ = nullptr;
  else if (rows_ > 0 && cols_ > 0) {
    matrix_ = new double*[rows_];
    for (int i = 0; i < rows_; i++) matrix_[i] = new double[cols_]{};
  }
}
#endif