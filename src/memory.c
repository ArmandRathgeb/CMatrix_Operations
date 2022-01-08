#include <stdlib.h>
#include <errno.h>
#include "matrix_operators.h"
/*
 * Contains implementaions for matrix memory management
 */

extern int errno;

// Dynamically allocate memory for matrix arrays
int ma_alloc(Matrix *matrix, size_t m, size_t n) {
    matrix->row = m;
    matrix->col = n;
    matrix->array = (float**)calloc(m, sizeof(float*));
    if(!matrix->array) {
        errno = 12;
        perror("Allocation failed!");
        return FAIL;
    }

    for(int i = 0; i < m; i++) {
        matrix->array[i] = (float*)calloc(n, sizeof(float));
        if(!matrix->array[i]) {
            errno = 12;
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
    if(!matrix->array) {
        errno = 12;
        perror("Reallocation failed!");
        return FAIL;
    }

    for(int i = 0; i < m; i++) {
        matrix->array[i] = (float*)realloc(matrix->array[i], m*sizeof(float));
        if(!matrix->array[i]) {
            errno = 12;
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
    for(int i = 0; i < m->row; i++) {
        free(m->array[i]);
        m->array[i] = NULL;
    }
    free(m->array);
    m->array = NULL;
}