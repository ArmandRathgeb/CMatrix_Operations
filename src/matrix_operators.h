/*
 * Header file for matrix operations.
 * Author: Armand Rathgeb
 * Last modified: 1/1/2022 
 */

#ifndef _MATRIX_OPERATORS_H_
#define _MATRIX_OPERATORS_H_
#include <stdlib.h>

// Always make sure to check errno values 
// when they get returned

#define FAIL 0
#define SUCCESS 1 

typedef struct Matrices {
  size_t row;    // Row size
  size_t col;    // Column size
  float **array; // 2-D array pointer
} Matrix;

// @params Matrix* to allocate, row size, column size
// @return FAIL or SUCCESS
// @description Allocates an m x n chunk of memory to
// a matrix
int ma_alloc(Matrix*, size_t, size_t);

// @params Matrix* to reallocate, row size, column size
// @return FAIL or SUCCESS
// @description Reallocates a matrix to a new m x n
// chunk of memory
int ma_realloc(Matrix*, size_t, size_t);

// @params Matrix* to delete
// @return void
// @description Frees dynamically allocated memory and
// deletes matrices
void ma_free(Matrix*);

// @params Matrix* A, Matrix* B
// @return Matrix A + Matrix B
// @description Adds two matrices of the same size
Matrix add(Matrix*, Matrix*);

// @params Matrix* A, Matrix* B
// @return Matrix A - Matrix B
// @description Subtracts two matrices of the same size
Matrix subtract(Matrix*, Matrix*);

// @params Matrix* A, Matrix* B
// @return Matrix A * Matrix B
// @description Multiplies two matrices. The columns of matrix
// A must be the same size as the rows of matrix B
Matrix multiply(Matrix*, Matrix*);

// @params Matrix* A, Matrix* B
// @return Matrix A / Matrix B
// @description Divides two matrices
Matrix divide(Matrix*, Matrix*);

// @params Matrix* A
// @return void
// @description Transposes a matrix. It will
// alter the matrix that gets sent to it
void transpose(Matrix*);

// @params Matrix* A
// @return void
// @description Prints a matrix
void printMatrix(Matrix*);

// @params Square size for the matrix
// @return Identity matrix
// @description Creates an m x m identity
// matrix
Matrix identityMatrix(size_t);

// @params Row size, Column size
// @return Matrix of ones
// @description Creates an m x n matrix full 
// of ones
Matrix ones(size_t, size_t);

 // @params Matrix A, Matrix B, 0 to concatenate along rows
 // 1 to concatenate along columns
 // @return Returns concenated matrix
 // @description Concatenates two matrices along either the 
 // rows or columns. Matrices must be the same size along either
 // their rows or columns.
Matrix cat(const Matrix*, const Matrix*, int);

// @params Matrix A, row position of coefficient, column position
// of coefficient
// @return Returns cofactor matrix
// @description Gets the 2x2 cofactor of a matrix at a point given 
// by the latter two parameters. Matrices must be 2x2 or greater,
// and must be square
Matrix getCofactor(Matrix*, size_t, size_t);

// @params Matrix A
// @return Determinant of matrix
// @description Gets the determinant of a matrix. Matrix A
// must be a square matrix and be 2x2 or greater.
float det(Matrix*);

#endif
