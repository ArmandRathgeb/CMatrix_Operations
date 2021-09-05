/*
 * Header file for matrix operations.
 * Author: Armand Rathgeb
 * Last modified: 9/10/2021
 */

#ifndef _MATRIX_OPERATORS_H_
#define _MATRIX_OPERATORS_H_
#include <stdlib.h> // For size_t and malloc
#include <stdio.h> // For printf

typedef struct Matrices {
  size_t row;
  size_t col;
  float **array;
} Matrix;

/* Dynamic array memory allocation
 * Make sure to always free the memory
 * allocated with `free(matrix.array);`
 * Returns array as a NULL if not enough
 * memory. Returns all memory zeroed out.
 */
Matrix ma_alloc(Matrix*, size_t, size_t);

Matrix ma_realloc(Matrix*, size_t, size_t);

void ma_free(Matrix*);

Matrix add(Matrix*, Matrix*);

/* Watch out when calling subtract,
 * it will negate the second array.
 */
Matrix subtract(Matrix*, Matrix*);

Matrix multiply(Matrix*, Matrix*);

Matrix divide(Matrix*, Matrix*);

void printMatrix(Matrix*);

// Create an identity matrix
Matrix identityMatrix(size_t);

// Creates an m*n matrix of ones
Matrix ones(size_t, size_t);

#endif
