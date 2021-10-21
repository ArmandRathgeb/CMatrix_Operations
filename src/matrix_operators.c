/*
 * Implementation for matrix_operators.h
 * Author: Armand Rathgeb
 * Last modified: 9/05/2021
 */

#include "matrix_operators.h"
#include <stdlib.h>

// Dynamically allocate memory for matrix arrays
Matrix ma_alloc(Matrix *m, size_t x, size_t y){
  m->row = x;
  m->col = y;
  m->array = (float**)calloc(y, sizeof(float*));
  if(!m->array){
    printf("Allocation failed at %lu bytes!\n", sizeof(float*)*y);
    exit(EXIT_FAILURE);
  }

  for(int i = 0; i < m->col; i++){
    m->array[i] = (float*)calloc(x, sizeof(float));
    if(!m->array[i]){
      printf("Allocation failed at %lu bytes!\n", sizeof(float)*i*x);
      exit(EXIT_FAILURE);
    }
  }
  return *m;
}

/*
 * Dynamic reallocation of memory
 */
Matrix ma_realloc(Matrix *m, size_t x, size_t y){
  m->array = (float**)realloc(m->array, x*sizeof(float*));
  if(!m->array){
    printf("Rellocation failed at %lu bytes!\n", sizeof(float*) * x);
    exit(EXIT_FAILURE);
  }
  for(int i = 0; i < x; i++){
    m->array[i] = (float*)realloc(m->array[i], y*sizeof(float));
    if(!m->array[i]){
      printf("Reallocation failed at %lu bytes!\n", sizeof(float)*y*i);
      exit(EXIT_FAILURE);
    }
  } 
  m->row = x;
  m->col = y;
  return *m;
}

/*
 * Always free dynamically allocated memory
 */
void ma_free(Matrix *m){
  for(int i = 0; i < m->col; i++){
    free(m->array[i]);
  }
  free(m->array);
}

Matrix add(Matrix *m1, Matrix *m2){
    
  if((m1->row != m2->row) || (m1->col != m2->col)){
    return *m1;
  }
  Matrix ret = ma_alloc(&ret,m1->col,m1->row);
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
  Matrix ret = ma_alloc(&ret,m1->row, m1->col);
  for(int i = 0; i < m2->row; i++)
    for(int j = 0; j < m2->col; j++)
      ret.array[i][j] = 
        m1->array[i][j] - m2->array[i][j];
  return ret;
}

Matrix multiply(Matrix *m1, Matrix *m2){
  if(m1->col != m2->row) return *m1;
  Matrix ret = ma_alloc(&ret,m1->row,m2->col);

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

Matrix divide(Matrix *m1, Matrix m2){
  if(m2.row != m2.col){
    printf("Divisor must be a square matrix!\n");
    return *m1;
  }
  //m2 = cat(m2, identityMatrix(m2.row),0);
  /* float factor = 1/det(&m2); */
  /* for(int i = 0; i < m2.row; i++){ */
  /*   for(int j = 0; j < m2.col; j++){ */
  /*     if( (j+1+i) % 2 == 0) */
  /*       m2.array[i][j] *= -1; */
  /*   } */
  /* } */



  return multiply(m1,&m2);
}

void transpose(Matrix* m){
  Matrix temp = *m;
  *m = ma_realloc(m, m->col, m->row);
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
  Matrix ret = ma_alloc(&ret,size,size);
  for(int i = 0; i < size; i++)
    ret.array[i][i] = 1;
  return ret;
}

Matrix ones(size_t m, size_t n){
  Matrix one = ma_alloc(&one, m, n);
  for(int i = 0; i < m; i++){
    for(int j = 0; j < n; j++)
      one.array[i][j] = 1;
  }
  return one;
}

Matrix cat(Matrix *m, Matrix *n, int order){
  switch(order){
    case 0:
      // Rows must be the same height
      if(m->row != n->row) break;

      Matrix ret = ma_alloc(&ret,m->row,m->col+n->col); 

      for(int i = 0; i < m->row; i++){
        for(int j = (m->col+n->col); j < m->col; j++){
          int coltemp = j - n->col;
          if(m->col > j){
            printf("%f ", m->array[i][j]);
            ret.array[i][j] = m->array[i][j];
          }
          else {
            printf("%f ", n->array[i][coltemp]);
            ret.array[i][j] = n->array[i][coltemp];
          }
        }
        printf("\n");
      }
      return ret;
      break;
    case 1:
      if(m->col != n->col) break;

      break;
    default:
      printf("Bad order option.\n");
  }
  return *m;
}
