/*
 * Implementation for matrix_operators.h
 * Author: Armand Rathgeb
 * Last modified: 9/05/2021
 */

#include "matrix_operators.h"
#include <stdio.h>
#include <stdlib.h>

// Dynamically allocate memory for matrix arrays
int ma_alloc(Matrix *matrix, size_t m, size_t n){
    matrix->row = m;
    matrix->col = n;
    matrix->array = (float**)calloc(m, sizeof(float*));
    if(!matrix->array){
        printf("Allocation failed at %lu bytes!\n", sizeof(float*)*m);
        return FAIL;
    }

    for(int i = 0; i < m; i++){
        matrix->array[i] = (float*)calloc(n, sizeof(float));
        if(!matrix->array[i]){
          printf("Allocation failed at %lu bytes!\n", sizeof(float)*i*n);
          return FAIL;
        }
    }
    return SUCCESS;
}

/*
 * Dynamic reallocation of memory
 */
int ma_realloc(Matrix *matrix, size_t m, size_t n){
    matrix->row = m;
    matrix->col = n;
    matrix->array = (float**)realloc(matrix->array, m*sizeof(float*));
    if(!matrix->array){
        printf("Rellocation failed at %lu bytes!\n", sizeof(float*) * m);
        return FAIL;
    }

    for(int i = 0; i < m; i++){
        matrix->array[i] = (float*)realloc(matrix->array[i], m*sizeof(float));
        if(!matrix->array[i]){
            printf("Reallocation failed at %lu bytes!\n", sizeof(float)*m*i);
            return FAIL;
        }
    } 
    return SUCCESS;
}

/*
 * Always free dynamically allocated memory
 */
void ma_free(Matrix *m){
    for(int i = 0; i < m->row; i++){
        free(m->array[i]);
        m->array[i] = NULL;
    }
    free(m->array);
    m->array = NULL;
}

Matrix add(Matrix *m1, Matrix *m2){
    
    if((m1->row != m2->row) || (m1->col != m2->col)){
        return *m1;
    }
    Matrix ret;
    ma_alloc(&ret,m1->col,m1->row);
    for(int i = 0; i < m1->row; i++){
        for(int j = 0; j < m1->col; j++){
            ret.array[i][j] = 
            m1->array[i][j] + m2->array[i][j];
        }
    }
    return ret;
} 

Matrix subtract(Matrix *m1, Matrix *m2){
    if( (m1->row != m2->row) || (m1->col != m2->row)){
        return *m1;
    }
    Matrix ret;
    ma_alloc(&ret,m1->row, m1->col);
    for(int i = 0; i < m2->row; i++)
        for(int j = 0; j < m2->col; j++)
            ret.array[i][j] = 
                m1->array[i][j] - m2->array[i][j];
    return ret;
}

Matrix multiply(Matrix *m1, Matrix *m2){
    if(m1->col != m2->row) return *m1;
    Matrix ret;
    ma_alloc(&ret,m1->row,m2->col);

    for(int i = 0; i < m1->row; ++i){
        for(int j = 0; j < m2->col; ++j){
            for(int k = 0; k < m1->row; ++k){

                ret.array[j][k] += 
                    m1->array[j][i] * m2->array[i][k];

            }
        }
    }
    return ret;
}

Matrix divide(Matrix *m1, Matrix *m2){
    if(m2->row != m2->col){
        printf("Divisor must be a square matrix!\n");
        return *m1;
    }
    //Matrix ret = cat(m2, identityMatrix(m2->row),0);
    /* float factor = 1/det(&m2); */
    /* for(int i = 0; i < m2.row; i++){ */
    /*   for(int j = 0; j < m2.col; j++){ */
    /*     if( (j+1+i) % 2 == 0) */
    /*       m2.array[i][j] *= -1; */
    /*   } */
    /* } */



    return multiply(m1,m2);
}

void transpose(Matrix* m){
    Matrix temp = *m;
    ma_realloc(m, m->col, m->row);
    for(int i = 0; i < m->row; i++){
        for(int j = 0; j < m->col; j++){
            m->array[i][j] = temp.array[j][i];    
        }
    }
}

void printMatrix(Matrix *m){
    for(int i = 0; i < m->row; i++){
        for(int j = 0; j < m->col; j++){
            printf("%f ", m->array[i][j]);
        }
        printf("\n");
    }
}

Matrix identityMatrix(size_t size){
    Matrix ret;
    ma_alloc(&ret,size,size);
    for(int i = 0; i < size; i++)
        ret.array[i][i] = 1;
    return ret;
}

Matrix ones(size_t m, size_t n){
    Matrix one;
    ma_alloc(&one, m, n);
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++)
            one.array[i][j] = 1;
    }
    return one;
}

Matrix cat(const Matrix *m, const Matrix *n, int order){
    Matrix ret;
    switch(order){
    case 0:
        // Rows must be the same height
        if(m->row != n->row) break;

        ma_alloc(&ret,m->row,m->col+n->col); 

        for(int i = 0; i < ret.row; i++){
            for(int j = 0; j < ret.col; j++){
                int coltemp = j - n->col;
                if(coltemp < 0){
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
        if(m->col != n->col) break;
        ma_alloc(&ret, m->row+n->row,m->col);

        for(int i = 0; i < ret.row; ++i){
            for(int j = 0; j < ret.col; ++j){
                int rowtemp = i - n->row;
                if(rowtemp < 0){
                    ret.array[i][j] = m->array[i][j];
                } else {
                    ret.array[i][j] = n->array[rowtemp][j];
                }
            }
        }

        return ret;
    default:
        printf("Bad order option.\n");
    }
    return *m;
}

Matrix getCofactor(Matrix* m, size_t rowPos, size_t colPos){
    if(m->row > 2 && m->col > 2) {
        Matrix cofactor;
        ma_alloc(&cofactor, m->row-1, m->col-1);
        for(int i = 0, mi = 0; mi < m->row; ++mi) {
            for(int j = 0, mj = 0; mj < m->col; ++mj) {
                if(mj != colPos) {
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
        return *m;
    }
}

float det(Matrix* m){
    if(m->row > 2 && m->col > 2) {
        float determinant = 0;
        int sign = 1;
        Matrix cofmat;

        for(size_t i = 0; i < m->col; ++i){
            cofmat = getCofactor(m, 0, i);
            determinant += sign*m->array[0][i] * det(&cofmat);
            sign = -sign;
        }
        return determinant;
    } else {
        return m->array[0][0] * m->array[1][1] - m->array[0][1] * m->array[1][0];
    }
}
