#ifndef _MATRIX_OPERATORS_H_
#define _MATRIX_OPERATORS_H_
/*!
 * \headerfile <>
 * \brief Contains all of the functions to deal with Matrices
 * \author Armand Rathgeb
 */

#include <stdlib.h>

// Always make sure to check errno values 
// when they get returned

#define FAIL 0
#define SUCCESS 1 

/*!
 * \struct Matrix
 * \brief Main class for 2D matrix
 */
typedef struct Matrices {
  size_t row;    /**< Row size */
  size_t col;    /**< Column size */
  float **array; /**< 2D array of floats */
} Matrix;

/*!
 * \struct Point
 * \brief Contains a point
 * \details coords start at the top left of the matrix
 */
typedef struct Points {
  size_t x; /**< x position */
  size_t y; /**< y position */
} Point;

/*!
 * \brief Allocate matrices
 * \details Uses calloc() under the hood to allocate a 2D matrix
 * \param matrix Pointer to matrix to allocate
 * \param m Row size
 * \param n Column size
 * \return FAIL or SUCCESS
 */
int ma_alloc(Matrix* matrix, size_t m, size_t n);

/*!
 * \brief Reallocate and resize a matrix
 * \details Uses realloc() under the hood to reallocate it.
 * \param matrix Pointer to matrix to allocate
 * \param m Row size
 * \param n Column size
 * \return FAIL or SUCCESS
 */
int ma_realloc(Matrix* matrix, size_t m, size_t n);

/*!
 * \brief Frees a matrix
 * \details Uses free() under the hood to deallocate
 * \param m Matrix to deallocate
 */
void ma_free(Matrix* m);

/*!
 * \brief Adds two matrices
 * \param m1 Pointer to first matrix
 * \param m2 Pointer to second matrix
 * \return m1 + m2
 */
Matrix add(const Matrix* m1, const Matrix* m2);

/*!
 * \brief Subtracts two matrices
 * \param m1 Pointer to first matrix
 * \param m2 Pointer to second matrix
 * \return m1 - m2
 */
Matrix subtract(const Matrix* m1, const Matrix* m2);

/*!
 * \brief Multiplies two matrices
 * \details Column of m1 must be the same size as the rows of m2
 * \param m1 Pointer to first matrix
 * \param m2 Pointer to second matrix
 * \return m1 * m2
 */
Matrix multiply(const Matrix* m1, const Matrix* m2);

/*!
 * \brief Divides two matrices
 * \param m1 Pointer to first matrix
 * \param m2 Pointer to second matrix
 * \return m1 / m2
 */
Matrix divide(const Matrix* m1, const Matrix* m2);

/*!
 * \brief Transposes a matrix
 * \details The matrix passed will be transposed. It will be affected
 * \param m Matrix to transpose
 */
void transpose(Matrix* m);

/*!
 * \brief Prints a matrix
 * \param m Pointer to matrix to print
 */
void printMatrix(const Matrix* m);

/*!
 * \brief Creates a size*size identity matrix
 * \param size Size for the sides of square identity matrix
 * \return Identity matrix
 */
Matrix identityMatrix(size_t size);

/*!
 * \brief Creates an m*n matrix of ones
 * \param m Row size
 * \param n Column size
 * \return m*n matrix of ones
 */
Matrix ones(size_t m, size_t n);

 /*!
  * \brief Concatenate two matrices
  * \details Concatenates two matrices. The sides being concatenated must be the same size
  * \param m Pointer to first matrix
  * \param n Pointer to second matrix
  * \param order 0 to concatenate along rows, 1 to concatenate along columns
  * \return Concatenated matrix
  */
Matrix cat(const Matrix* m, const Matrix* n, int order);

/*!
 * \brief Gets 2x2 cofactor matrix at a point given by rowPos and colPos
 * \param m Pointer to matrix to use
 * \param rowPos Row position of coefficient
 * \param colPos Column position of coefficient
 * \return 2x2 cofactor matrix
 */
Matrix getCofactor(const Matrix* m, size_t rowPos, size_t colPos);

/*!
 * \brief Determinant of matrix
 * \param m Pointer to matrix to use
 * \return Determinant
 */
float det(const Matrix* m);

/*!
 * \brief Finds the saddle point of a matrix
 * \details The saddle point is the minimum in its row, and max in its column
 * \param m Pointer to matrix
 * \return Point where sadddle is
 */
Point saddle(const Matrix* m);

/*!
 * \brief Fill a matrix with random numbers
 * \param m Pointer to matrix
 * \param min Minimum
 * \param max Max
 */
void ma_rand(Matrix* m, int min, int max);

#endif
