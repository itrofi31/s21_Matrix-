#include <gtest/gtest.h>

#include "../s21_matrix_oop.h"

TEST(getters, get_cols_get_rows) {
  S21Matrix matrix(2, 2);
  matrix(1, 1) = 1.000;
  EXPECT_EQ(matrix.GetCols(), 2);
  EXPECT_EQ(matrix.GetRows(), 2);
  EXPECT_DOUBLE_EQ(matrix(1, 1), 1.000);
}

TEST(setters, set_cols) {
  S21Matrix matrix(2, 2);
  matrix(1, 1) = 1.000;
  matrix.SetCols(3);
  matrix(1, 2) = 1;
  matrix.SetCols(3);
  EXPECT_EQ(matrix.GetCols(), 3);
  EXPECT_DOUBLE_EQ(matrix(1, 1), 1.000);
  EXPECT_EQ(matrix(1, 2), 1);
  matrix.SetCols(2);
}
TEST(setters, setrows) {
  S21Matrix m1(2, 2);
  m1(1, 0) = 1.000;
  m1.SetRows(3);
  m1(2, 0) = m1(1, 0);
  EXPECT_EQ(m1.GetRows(), 3);
  EXPECT_EQ(m1.GetCols(), 2);
  EXPECT_DOUBLE_EQ(m1(1, 0), m1(2, 0));
}

TEST(constructors, all_types) {
  S21Matrix m1;
  EXPECT_EQ(m1.GetCols(), 0);
  EXPECT_EQ(m1.GetRows(), 0);

  S21Matrix m2(2, 2);
  m2(1, 1) = 1.000;
  EXPECT_EQ(m2.GetCols(), 2);
  EXPECT_EQ(m2.GetRows(), 2);
  EXPECT_DOUBLE_EQ(m2(1, 1), 1.000);

  S21Matrix m3(m2);
  EXPECT_EQ(m2.EqMatrix(m3), true);

  S21Matrix m4(std::move(m3));
  EXPECT_EQ(m4.GetRows(), 2);
  EXPECT_EQ(m4.GetCols(), 2);
  EXPECT_EQ(m4(1, 1), m2(1, 1));

  S21Matrix m5(0, 0);
  EXPECT_EQ(m5.GetRows(), 0);
  EXPECT_EQ(m5.GetCols(), 0);
}

TEST(functions, eq) {
  S21Matrix m1(100, 100);
  S21Matrix m2(m1);
  S21Matrix m3;
  S21Matrix m4(1, 1);
  S21Matrix m5(1, 1);
  m4(0, 0) = 1.0;
  m5(0, 0) = 2.0;

  EXPECT_EQ(m1.EqMatrix(m2), true);
  EXPECT_EQ(m1.EqMatrix(m3), false);
  EXPECT_EQ(m4.EqMatrix(m5), false);
}

TEST(functions, assign_sum) {
  S21Matrix m1(3, 3);
  S21Matrix m2(m1);

  m1(0, 0) = 21;
  m1(0, 1) = 42;

  m2 += m1;
  EXPECT_EQ(m2(0, 0), 21);
  EXPECT_EQ(m2(0, 1), 42);
}
TEST(functions, sum) {
  S21Matrix m1(3, 3);
  S21Matrix m2(m1);

  m1(0, 0) = 21;
  m1(0, 1) = 42;

  m1 = m2 + m1;
  EXPECT_EQ(m1(0, 0), 21);
  EXPECT_EQ(m1(0, 1), 42);
}

TEST(functions, assign_sub) {
  S21Matrix m1(3, 3);
  S21Matrix m2(3, 3);
  m1(0, 0) = 21;
  m1(0, 1) = 21;

  m2(0, 0) = 42;
  m2(0, 1) = 42;

  m2 -= m1;
  EXPECT_EQ(m2(0, 0), 21);
  EXPECT_EQ(m2(0, 1), 21);
}

TEST(functions, sub) {
  S21Matrix m1(3, 3);
  S21Matrix m2(3, 3);
  m1(0, 0) = 21;
  m1(0, 1) = 21;

  m2(0, 0) = 42;
  m2(0, 1) = 42;

  m1 = m2 - m1;
  EXPECT_EQ(m1(0, 0), 21);
  EXPECT_EQ(m1(0, 1), 21);
}

TEST(functions, assign_mul_mat) {
  S21Matrix m1(3, 3);
  S21Matrix m2(3, 3);
  m1(0, 0) = 21;
  m1(0, 1) = 21;

  m2(0, 0) = 2;
  m2(1, 0) = 2;

  m2 *= m1;
  EXPECT_EQ(m2(0, 0), 42);
  EXPECT_EQ(m2(0, 1), 42);
}

TEST(functions, mul_mat) {
  S21Matrix m1(3, 3);
  S21Matrix m2(3, 3);
  m1(0, 0) = 21;
  m1(0, 1) = 21;

  m2(0, 0) = 2;
  m2(1, 0) = 2;

  S21Matrix res = m2 * m1;
  EXPECT_EQ(res(0, 0), 42);
  EXPECT_EQ(res(0, 1), 42);
}

TEST(operator_overloads, mul_matrix_by_number) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 1;
  matrix(0, 1) = 2;

  double multiplier = 3.0;
  S21Matrix result = multiplier * matrix;

  EXPECT_DOUBLE_EQ(result(0, 0), 3.0);
  EXPECT_DOUBLE_EQ(result(0, 1), 6.0);
}

TEST(functions, mul_num) {
  S21Matrix m1(2, 2);
  m1(0, 0) = 1.1;
  m1(0, 1) = 1.2;

  m1 *= 21;
  EXPECT_EQ(m1(0, 0), 1.1 * 21);
  EXPECT_EQ(m1(0, 1), 1.2 * 21);
}

TEST(functions, transpose) {
  S21Matrix m1(3, 3);
  m1(0, 0) = 1;
  m1(0, 1) = 2;
  m1(0, 2) = 3;

  S21Matrix mt = m1.Transpose();
  EXPECT_EQ(mt(0, 0), 1);
  EXPECT_EQ(mt(1, 0), 2);
  EXPECT_EQ(mt(2, 0), 3);
}

TEST(functions, complements_with_errors) {
  S21Matrix m(3, 12);
  EXPECT_ANY_THROW(m.CalcComplements());
}

TEST(functions, det) {
  S21Matrix m(5, 5);

  for (int i = 0; i < 5; i++)
    for (int j = 0; j < 5; j++) m(i, j) = j;

  ASSERT_NEAR(0, m.Determinant(), 1e-06);
}

TEST(functions, det2) {
  int size = 5;
  S21Matrix m(size, size);

  m(0, 1) = 6;
  m(0, 2) = -2;
  m(0, 3) = -1;
  m(0, 4) = 5;
  m(1, 3) = -9;
  m(1, 4) = -7;
  m(2, 1) = 15;
  m(2, 2) = 35;
  m(3, 1) = -1;
  m(3, 2) = -11;
  m(3, 3) = -2;
  m(3, 4) = 1;
  m(4, 0) = -2;
  m(4, 1) = -2;
  m(4, 2) = 3;
  m(4, 4) = -2;

  double res = m.Determinant();
  ASSERT_NEAR(res, 2480, 1e-6);
}

TEST(functions, complements1) {
  int rows = 3;
  int cols = 3;

  S21Matrix given(rows, cols);
  S21Matrix expected(rows, cols);

  given(0, 0) = 1.0;
  given(0, 1) = 2.0;
  given(0, 2) = 3.0;
  given(1, 0) = 0.0;
  given(1, 1) = 4.0;
  given(1, 2) = 2.0;
  given(2, 0) = 5.0;
  given(2, 1) = 2.0;
  given(2, 2) = 1.0;

  expected(0, 0) = 0.0;
  expected(0, 1) = 10.0;
  expected(0, 2) = -20.0;
  expected(1, 0) = 4.0;
  expected(1, 1) = -14.0;
  expected(1, 2) = 8.0;
  expected(2, 0) = -8.0;
  expected(2, 1) = -2.0;
  expected(2, 2) = 4.0;

  S21Matrix res = given.CalcComplements();

  ASSERT_TRUE(res == expected);
}

TEST(functions, complements2) {
  int rows = 1;
  int cols = 2;

  S21Matrix m(rows, cols);

  EXPECT_THROW(m.CalcComplements(), std::logic_error);
}

TEST(functions, inverse) {
  int size = 3;
  S21Matrix given(size, size);
  S21Matrix expected(size, size);

  expected(0, 0) = 44300.0 / 367429.0;
  expected(0, 1) = -236300.0 / 367429.0;
  expected(0, 2) = 200360.0 / 367429.0;
  expected(1, 0) = 20600.0 / 367429.0;
  expected(1, 1) = 56000.0 / 367429.0;
  expected(1, 2) = -156483.0 / 367429.0;
  expected(2, 0) = 30900.0 / 367429.0;
  expected(2, 1) = 84000.0 / 367429.0;
  expected(2, 2) = -51010.0 / 367429.0;

  given(0, 0) = 2.8;
  given(0, 1) = 1.3;
  given(0, 2) = 7.01;
  given(1, 0) = -1.03;
  given(1, 1) = -2.3;
  given(1, 2) = 3.01;
  given(2, 0) = 0;
  given(2, 1) = -3;
  given(2, 2) = 2;

  ASSERT_TRUE(expected.InverseMatrix() == given);
}

TEST(operators, assignment_operator) {
  S21Matrix m1(2, 2);
  m1(0, 0) = 1;
  m1(0, 1) = 2;
  m1(1, 0) = 3;
  m1(1, 1) = 4;

  // Test assignment from another matrix
  S21Matrix m2;
  m2 = m1;
  EXPECT_DOUBLE_EQ(m2(0, 0), 1);
  EXPECT_DOUBLE_EQ(m2(0, 1), 2);
  EXPECT_DOUBLE_EQ(m2(1, 0), 3);
  EXPECT_DOUBLE_EQ(m2(1, 1), 4);
}

int main() {
  testing::InitGoogleTest();
  if (RUN_ALL_TESTS()) {
    std::cout << "ERRORS" << std::endl;
  }
  return RUN_ALL_TESTS();
}