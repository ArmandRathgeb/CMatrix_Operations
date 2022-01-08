// Contains implementations of regular mathematical matrix operators
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include "matrix_operators.h"

extern int errno;

Matrix add(Matrix *m1, Matrix *m2) {
    if((m1->row != m2->row) || (m1->col != m2->col)) {
        errno = EINVAL;
        perror("Matrices must be the same size");
        return *m1;
    }
    Matrix ret;
    ma_alloc(&ret,m1->col,m1->row);
    for(int i = 0; i < m1->row; i++) {
        for(int j = 0; j < m1->col; j++) {
            ret.array[i][j] = 
                m1->array[i][j] + m2->array[i][j];
        }
    }
    errno = 0;
    return ret;
} 

Matrix subtract(Matrix *m1, Matrix *m2) {
    if((m1->row != m2->row) || (m1->col != m2->row)) {
        errno = EINVAL;
        perror("Matrices must be the same size");
        return *m1;
    }
    Matrix ret;
    ma_alloc(&ret,m1->row, m1->col);
    for(int i = 0; i < m2->row; i++)
        for(int j = 0; j < m2->col; j++)
            ret.array[i][j] = 
                m1->array[i][j] - m2->array[i][j];
    errno = 0;
    return ret;
}

Matrix multiply(Matrix *m1, Matrix *m2) {
    if(m1->col != m2->row) {
        errno = EINVAL;
        perror("Column of matrix 1 must be equal to column of matrix 2");
        return *m1;
    }
    Matrix ret;
    ma_alloc(&ret,m1->row,m2->col);

    for(int i = 0; i < m1->row; ++i) {
        for(int j = 0; j < m2->col; ++j) {
            for(int k = 0; k < m1->row; ++k) {
                ret.array[j][k] += 
                    m1->array[j][i] * m2->array[i][k];
            }
        }
    }
    errno = 0;
    return ret;
}

Matrix divide(Matrix *m1, Matrix *m2) {
    if(m2->row != m2->col) {
        errno = EINVAL;
        perror("Matrix must be square");
        return *m1;
    }
    Matrix ident = identityMatrix(m2->row);
    Matrix ret = cat(m2, &ident,0);
    float factor = 1/det(m2); 
    for(int i = 0; i < m2->row; i++) { 
        for(int j = 0; j < m2->col; j++) { 
            if( (j+1+i) % 2 == 0) 
                m2->array[i][j] *= -1; 
        } 
    } 
    errno = 0;
    return multiply(m1,m2);
}