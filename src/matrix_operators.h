/*
 * Header file for matrix operations.
 * Author: Armand Rathgeb
 * Last modified: 9/05/2021
 */

#ifndef _MATRIX_OPERATORS_H_
#define _MATRIX_OPERATORS_H_
#include <stdlib.h> // For size_t and malloc
#include <stdio.h> // For printf

#define FAIL -1
#define SUCCESS 0

typedef struct Matrices {
  size_t row;
  size_t col;
  float **array;
} Matrix;

/* Dynamic array memory allocation
 * Returns array as a NULL if not enough
 * memory. Returns all memory zeroed out.
 */
int ma_alloc(Matrix*, size_t, size_t);

//Dynamic reallocation of memory
// Parameters: Matrix, m*n matrix
int ma_realloc(Matrix*, size_t, size_t);

// Freeing of dynamically allocated memory
void ma_free(Matrix*);

Matrix add(Matrix*, Matrix*);

Matrix subtract(Matrix*, Matrix*);

Matrix multiply(Matrix*, Matrix*);

/*
 * First one passed by reference for speed.
 * Second passed by value to prevent it from
 * being altered.
 */
Matrix divide(Matrix*, Matrix*);

void transpose(Matrix*);

void printMatrix(Matrix*);

// Create an identity matrix
Matrix identityMatrix(size_t);

// Creates an m*n matrix of ones
Matrix ones(size_t, size_t);

/*
 * Concatenate two matrices.
 * Set the order to 1 to concatenate along the rows.
 * Set the order to 0 to concatenate along the columns.
 */
Matrix cat(const Matrix*, const Matrix*, int);

Matrix getCofactor(Matrix*);

float det(Matrix*);

#endif
