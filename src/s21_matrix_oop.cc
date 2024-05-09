#include "s21_matrix_oop.h"

// default constructors
S21Matrix::S21Matrix() noexcept : rows_(0), cols_(0), matrix_(nullptr) {}

// parameterized constructor
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

// move operator overload
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

// getters
int S21Matrix::GetRows() const noexcept { return rows_; }

int S21Matrix::GetCols() const noexcept { return cols_; }

// setters
void S21Matrix::SetRows(int rows) {
  if (rows < 0) {
    throw std::length_error("Rows must be positive");

    if (rows != rows_) {
      S21Matrix copy(rows, cols_);
      for (int i = 0; i < rows && i < rows_; i++)
        for (int j = 0; j < cols_; j++) copy(i, j) = (*this)(i, j);
    }
  }
}

void S21Matrix::SetCols(int cols) {
  if (cols < 0) {
    throw std::length_error("Cols must be positive");

    if (cols != cols_) {
      S21Matrix copy(rows_, cols);
      for (int i = 0; i < rows_; i++)
        for (int j = 0; j < cols_ && j < cols; j++) copy(i, j) = (*this)(i, j);
    }
  }
}

// index operator overload
double& S21Matrix::operator()(int row, int col) const {
  if (row < 0 || col < 0 || row >= rows_ || col >= cols_)
    throw std::out_of_range("Out of range");

  return matrix_[row][col];
}

// addition operator overload
S21Matrix S21Matrix::operator+(const S21Matrix& other) const {
  S21Matrix result(*this);
  result.SumMatrix(other);
  return result;
}

// substraction operator overload
S21Matrix S21Matrix::operator-(const S21Matrix& other) const {
  S21Matrix result(*this);
  result.SubMatrix(other);
  return result;
}

// multiplication matrices operator overload
S21Matrix S21Matrix::operator*(const S21Matrix& other) const {
  S21Matrix result(*this);
  result.MulMatrix(other);
  return result;
}

// multiplication with number operator overload
S21Matrix S21Matrix::operator*(const double num) const {
  S21Matrix result(*this);
  result.MulNumber(num);
  return result;
}

// multiplication another matrix with number operator overload
S21Matrix operator*(const double& value, const S21Matrix& matrix) {
  S21Matrix result(matrix);
  return result *= value;
}

// equality operator overload
bool S21Matrix::operator==(const S21Matrix& other) const {
  return EqMatrix(other);
}

// addition assignment operator overload
S21Matrix& S21Matrix::operator+=(const S21Matrix& other) {
  SumMatrix(other);
  return *this;
}

// substraction assignment operator overload
S21Matrix& S21Matrix::operator-=(const S21Matrix& other) {
  SubMatrix(other);
  return *this;
}

// multiplication assignment operator overload
S21Matrix& S21Matrix::operator*=(const S21Matrix& other) {
  MulMatrix(other);
  return *this;
}

// multiplication assignment with number operator overload
S21Matrix& S21Matrix::operator*=(const double num) {
  MulNumber(num);
  return *this;
}

// equality matrices
bool S21Matrix::EqMatrix(const S21Matrix& other) const noexcept {
  if (rows_ != other.rows_ || cols_ != other.cols_) return false;
  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_; j++)
      if (std::fabs(this->matrix_[i][j] - other.matrix_[i][j]) > 1e-7)
        return false;
  return true;
}

// addition
void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_)
    throw std::logic_error("Matrices have different size");
  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_; j++) {
      (*this)(i, j) += other(i, j);
    }
}

// substraction
void S21Matrix::SubMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_)
    throw std::logic_error("Matrices have different size");
  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_; j++) {
      (*this)(i, j) -= other(i, j);
    }
}

// multiplication
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

// transposition
S21Matrix S21Matrix::Transpose() {
  S21Matrix result(cols_, rows_);
  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_; j++) {
      result(j, i) = (*this)(i, j);
    }
  return result;
}

// calculation of algebraic completements
S21Matrix S21Matrix::CalcComplements() {
  if (rows_ <= 0 || cols_ <= 0)
    throw std::out_of_range("Rows and columns must be positive.");

  S21Matrix result(rows_, cols_);
  if (rows_ == 1 && cols_ == 1)
    result(0, 0) = 1;
  else {
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        result(i, j) = pow(-1, i + j) * GetMinor(i, j).Determinant();
      }
    }
  }
  return result;
}

// calculation of deteerminant
double S21Matrix::Determinant() {
  if (rows_ != cols_) throw std::logic_error("Matrix must be square");

  double result = 0.0;
  if (rows_ == 1)
    result = (*this)(0, 0);
  else {
    for (int i = 0; i < cols_; i++) {
      S21Matrix minor = GetMinor(0, i);
      result += (*this)(0, i) * pow(-1, i) * minor.Determinant();
    }
  }
  return result;
}

S21Matrix S21Matrix::GetMinor(int row, int col) const {
  if (row < 0 || col < 0 || row >= rows_ || col >= cols_)
    throw std::out_of_range("Incorrect size of matrix");
  if (rows_ != cols_) throw std::logic_error("Matrix must be square");

  S21Matrix minor(rows_ - 1, cols_ - 1);
  int m_i = 0;
  for (int i = 0; i < rows_; i++) {
    if (i == row) continue;
    int m_j = 0;

    for (int j = 0; j < cols_; j++) {
      if (j == col) continue;
      minor(m_i, m_j) = (*this)(i, j);
      m_j++;
    }
    m_i++;
  }
  return minor;
}

// matrix inversion
S21Matrix S21Matrix::InverseMatrix() {
  double determinant = this->Determinant();
  if (std::fabs(determinant) < 1e-7) {
    throw std::logic_error("Zero determinant.");
  }
  return CalcComplements().Transpose() * (1 / determinant);
}

// memory allocation for matrix
void S21Matrix::createMatrix() {
  if (rows_ == 0 && cols_ == 0)
    matrix_ = nullptr;
  else if (rows_ > 0 && cols_ > 0) {
    matrix_ = new double*[rows_];
    for (int i = 0; i < rows_; i++) matrix_[i] = new double[cols_]{};
  }
}
