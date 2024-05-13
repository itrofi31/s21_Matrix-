# s21_matrix+

Implementation of the s21_matrix_oop.h library using C++ programming language.


## Contents

1. [Introduction](#introduction) 
2. [Matrix operations](#matrix-operations) 
3. [Build](#build) 

## Introduction

In this project, I implement the matrix library using the object-oriented approach (see materials). The object-oriented approach allows to implement a library for matrices as a separate class whose objects have defined operations, that can be represented both as methods and as standard operators +, -, *, etc.


## Matrix operations

Below is a brief description of the matrix operations implemented in the development library.


| Operation | Description
| ----------- | ----------- 
| `bool EqMatrix(const S21Matrix& other)` | Checks matrices for equality with each other.|
| `void SumMatrix(const S21Matrix& other)` | Adds the second matrix to the current one |
| `void SubMatrix(const S21Matrix& other)` | Subtracts another matrix from the current one |
| `void MulNumber(const double num) ` | Multiplies the current matrix by a number. |
| `void MulMatrix(const S21Matrix& other)` | Multiplies the current matrix by the second matrix.|
| `S21Matrix Transpose()` | Creates a new transposed matrix from the current one and returns it.|
| `S21Matrix CalcComplements()` | Calculates the algebraic addition matrix of the current one and returns it.|
| `double Determinant()` | Calculates and returns the determinant of the current matrix. |
| `S21Matrix InverseMatrix()` | Calculates and returns the inverse matrix.|

Constructors and destructors:

| Method | Description |
| ----------- | ----------- |
| `S21Matrix()` | A basic constructor that initialises a matrix of some predefined dimension. |  
| `S21Matrix(int rows, int cols) ` | Parametrized constructor with number of rows and columns. |
| `S21Matrix(const S21Matrix& other)` | Copy constructor. |
| `S21Matrix(S21Matrix&& other)` | Move constructor. |
| `~S21Matrix()` | Destructor. |

Overload operators:

| Operator | Description |
| ----------- | ----------- |
| `+`      | Addition of two matrices. |
| `-`   | Subtraction of one matrix from another. |
| `*`  | Matrix multiplication and matrix multiplication by a number. |first matrix does not equal the number of rows of the second matrix. |
| `==`  | Checks for matrices equality (`EqMatrix`). |
| `=`  | Assignment of values from one matrix to another one. |
| `+=`  | Addition assignment (`SumMatrix`) |
| `-=`  | Difference assignment (`SubMatrix`) |
| `*=`  | Multiplication assignment (`MulMatrix`/`MulNumber`). |matrix does not equal the number of rows of the second matrix. |
| `(int i, int j)`  | Indexation by matrix elements (row, column). |

## Build
* Build library

   ```
   make all
   ```
* Build and run tests

   ```
   make test
   ```
* Clean library

   ```
   make clean
   ```
* Run test coverage check

   ```
   make gcov_report
   ```
* Run docker with valgrind leaks check

   ```
   make docker_valgrind
   ```