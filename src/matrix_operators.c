/*
 * Implementation for matrix_operators.h
 * Author: Armand Rathgeb
 * Last modified: 9/01/2021
 */

#include "matrix_operators.h"

// Dynamically allocate memory for matrix arrays
Matrix ma_alloc(Matrix *m, size_t x, size_t y){
  m->row = x;
  m->col = y;
  m->array = (float**)malloc(m->col * sizeof(float*));
  for(int i = 0; i < m->col; i++)
    m->array[i] = (float*)malloc(m->row * sizeof(float));

  if(m->array == NULL) return *m;

  // Zero out the memory in case the OS doesn't do it
  // Prevents memory errors and helps portability
  for(int i = 0; i < m->row; i++)
    for(int j = 0; j < m->col; j++)
      m->array[i][j] = 0;
  return *m;
}

Matrix ma_realloc(Matrix *m, size_t x, size_t y){
  if(m->array == NULL) {
    *m = ma_alloc(m, x, y);
  }
  else{
    m->array = (float**)realloc(m->array, x*sizeof(float*));
    for(int i = 0; i < x; i++){
      m->array[i] = (float*)realloc(m->array[i], y*sizeof(float));
    } 
    m->row = x;
    m->col = y;
  }
  return *m;
}

void ma_free(Matrix *m){
  for(int i = 0; i < m->col; i++){
    free(m->array[i]);
  }
  free(m->array);
}

Matrix add(Matrix *m1, Matrix *m2){
    
  if((m1->row != m2->row) && (m1->col != m2->col)){
    return *m1;
  }
  Matrix returnMatrix = ma_alloc(&returnMatrix,m1->col,m1->row);
  for(int i = 0; i < m1->row; i++){
    for(int j = 0; j < m1->col; j++){
      returnMatrix.array[i][j] = 
        m1->array[i][j] + m2->array[i][j];
    }
  }
  return returnMatrix;
} 

Matrix subtract(Matrix *m1, Matrix *m2){
  for(int i = 0; i < m2->row; i++)
    for(int j = 0; j < m2->col; j++)
      m2->array[i][j]  = -m2->array[i][j];
  // Subtraction is negative addition
  return add(m1,m2);
}

Matrix multiply(Matrix *m1, Matrix *m2){
  if(m1->col != m2->row) return *m1;
  register int i,j,k;
  Matrix returnMatrix = ma_alloc(&returnMatrix,m1->row,m2->col);

  for(i = 0; i < m1->row; ++i){
    for(j = 0; j < m2->col; ++j){
      for(k = 0; k < m1->row; ++k){

        returnMatrix.array[j][k] += 
          m1->array[j][i] * m2->array[i][k];

      }
    }
  }
  return returnMatrix;

}

Matrix divide(Matrix *m1, Matrix *m2){

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
  Matrix returnMatrix = ma_alloc(&returnMatrix,size,size);
  for(int i = 0; i < size; i++)
    returnMatrix.array[i][i] = 1;
  return returnMatrix;
}

Matrix ones(size_t m, size_t n){
  Matrix one = ma_alloc(&one, m, n);
  for(int i = 0; i < m; i++){
    for(int j = 0; j < n; j++)
      one.array[i][j] = 1;
  }
  return one;
}
