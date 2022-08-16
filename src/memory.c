// Contains implementations of matrix memory management
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <time.h>
#include "matrix_operators.h"

extern int errno;

// Dynamically allocate memory for matrix arrays
int ma_alloc(Matrix *matrix, size_t m, size_t n) {
    matrix->row = m;
    matrix->col = n;
    matrix->array = (float**)calloc(m, sizeof(float*));
    if (!matrix->array) {
        errno = ENOMEM;
        perror("Allocation failed!");
        return FAIL;
    }

    for (size_t i = 0; i < m; i++) {
        matrix->array[i] = (float*)calloc(n, sizeof(float));
        if (!matrix->array[i]) {
            errno = ENOMEM;
            perror("Allocation failed!");
            return FAIL;
        }
    }
    errno = 0;
    return SUCCESS;
}

/*
 * Dynamic reallocation of memory
 */
int ma_realloc(Matrix *matrix, size_t m, size_t n) {
    matrix->row = m;
    matrix->col = n;
    matrix->array = (float**)realloc(matrix->array, m*sizeof(float*));
    if (!matrix->array) {
        errno = ENOMEM;
        perror("Reallocation failed!");
        return FAIL;
    }

    for (size_t i = 0; i < m; i++) {
        matrix->array[i] = (float*)realloc(matrix->array[i], m*sizeof(float));
        if (!matrix->array[i]) {
            errno = ENOMEM;
            perror("Reallocation failed!");
            return FAIL;
        }
    } 
    errno = 0;
    return SUCCESS;
}

/*
 * Always free dynamically allocated memory
 */
void ma_free(Matrix *m) {
    for (size_t i = 0; i < m->row; i++) {
        free(m->array[i]);
        m->array[i] = NULL;
    }
    free(m->array);
    m->array = NULL;
}

void ma_rand(Matrix* m, int min, int max) {
    srand(time(NULL));
    max = max * 10;
    for (size_t i = 0; i < m->row; ++i) {
        for (size_t j = 0; j < m->col; ++j) {
            m->array[i][j] = ((float)(rand() % max + min)) / 10;
        }
    }
}