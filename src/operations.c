// Contains implementations for operations:
#include "matrix_operators.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

extern int errno;

void transpose(Matrix* m) {
    Matrix temp = *m;
    ma_realloc(m, m->col, m->row);
    for(int i = 0; i < m->row; i++) {
        for(int j = 0; j < m->col; j++) {
            m->array[i][j] = temp.array[j][i];    
        }
    }
}

void printMatrix(Matrix *m) {
    for(int i = 0; i < m->row; i++) {
        for(int j = 0; j < m->col; j++) {
            printf("%f ", m->array[i][j]);
        }
        printf("\n");
    }
}

Matrix identityMatrix(size_t size) {
    Matrix ret;
    ma_alloc(&ret, size, size);
    for(int i = 0; i < size; i++)
        ret.array[i][i] = 1;
    return ret;
}

Matrix ones(size_t m, size_t n) {
    Matrix one;
    ma_alloc(&one, m, n);
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++)
            one.array[i][j] = 1;
    }
    return one;
}

Matrix cat(const Matrix *m, const Matrix *n, int order) {
    Matrix ret;
    errno = 0;
    switch(order) {
    case 0:
        // Rows must be the same height
        if(m->row != n->row) {
            errno = EINVAL;
            perror("Rows must be the same size");
            break;
        }

        ma_alloc(&ret,m->row,m->col+n->col); 

        for(int i = 0; i < ret.row; i++) {
            for(int j = 0; j < ret.col; j++) {
                int coltemp = j - n->col;
                if(coltemp < 0) {
                    ret.array[i][j] = m->array[i][j];
                } else {
                    ret.array[i][j] = n->array[i][coltemp];
                }
            }
            printf("\n");
        }
        return ret;
    case 1:
        // Columns must be the same height
        if(m->col != n->col) {
            errno = EINVAL;
            perror("Columns must be the same size");
            break;
        }
        ma_alloc(&ret, m->row+n->row,m->col);

        for(int i = 0; i < ret.row; ++i) {
            for(int j = 0; j < ret.col; ++j) {
                int rowtemp = i - n->row;
                if(rowtemp < 0) {
                    ret.array[i][j] = m->array[i][j];
                } else {
                    ret.array[i][j] = n->array[rowtemp][j];
                }
            }
        }

        return ret;
    default:
        errno = EINVAL;
        perror("Bad order option");
    }
    return *m;
}

Matrix getCofactor(Matrix* m, size_t rowPos, size_t colPos) {
    if(m->row > 2 && m->col > 2) {
        Matrix cofactor;
        ma_alloc(&cofactor, m->row-1, m->col-1);
        for(int i = 0, mi = 0; mi < m->row; ++mi) {
            for(int j = 0, mj = 0; mj < m->col; ++mj) {
                if(mj != colPos) {
                    // Set cofactor array at position i,j to value at
                    // array mi,mj
                    cofactor.array[i][j] = m->array[mi][mj];
                    j++;
                }
            }
            if(mi != rowPos) {
                i++;
            }
        }
        return cofactor;
    } else {
        // Determinant of a 2x2 matrix is still a 2x2 matrix
        return *m;
    }
}

float det(Matrix* m) {
    errno = 0;
    if((m->row == m->col) && (m->row > 1 && m->col > 1)) {
        if(m->row > 2 && m->col > 2) {
            float determinant = 0;
            int sign = 1;
            Matrix cofmat;

            for(size_t i = 0; i < m->col; ++i) {
                cofmat = getCofactor(m, 0, i);
                determinant += sign*m->array[0][i] * det(&cofmat);
                sign = -sign;
            }
            return determinant;
        } else {
            return m->array[0][0] * m->array[1][1] - m->array[0][1] * m->array[1][0];
        }
    } else {
        errno = EINVAL;
        perror("Matrix must be square");
        return FAIL;
    }
}
