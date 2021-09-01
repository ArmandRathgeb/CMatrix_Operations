/*
 * Implementation for matrix_operators.h
 * Author: Armand Rathgeb
 * Last modified: 9/01/2021
 */

#include "matrix_operators.h"

// Dynamically allocate memory for matrix arrays
Matrix ma_alloc(Matrix m){
  m.array = (float**)malloc(m.row * sizeof(float*));
  for(int i = 0; i < m.col; i++)
    m.array[i] = (float*)malloc(m.col * sizeof(float));
  return m;
}

Matrix add(Matrix m1, Matrix m2){
  Matrix returnMatrix = {m1.col, m1.row};
    
  if((m1.row != m2.row) && (m1.col != m2.col)){
    return m1;
  }
  returnMatrix = ma_alloc(returnMatrix);
  for(int i = 0; i < m1.row; i++){
    for(int j = 0; j < m1.col; j++){
      returnMatrix.array[i][j] = 
        m1.array[i][j] + m2.array[i][j];
    }
  }
  return returnMatrix;
} 

Matrix subtract(Matrix m1, Matrix m2){
  for(int i = 0; i < m2.row; i++)
    for(int j = 0; j < m2.col; j++)
      m2.array[i][j]  = -m2.array[i][j];
  // Subtraction is negative addition
  return add(m1,m2);
}

Matrix multiply(Matrix m1, Matrix m2){
  Matrix returnMatrix = {m1.row, m2.col};
  returnMatrix = ma_alloc(returnMatrix);
  if(m1.col != m2.row) return m1;

  return returnMatrix;
}

Matrix divide(Matrix m1, Matrix m2){

}

void printMatrix(Matrix m){
  for(int i = 0; i < m.row; i++){
    for(int j = 0; j < m.col; j++){
      printf("%f ", m.array[i][j]);
    }
    printf("\n");
  }
}

Matrix identityMatrix(size_t row, size_t col){
  Matrix returnMatrix = {row, col};
  returnMatrix = ma_alloc(returnMatrix);
  if(row != col) return returnMatrix;
  for(int i = 0; i < row; i++){
    for(int j = 0; j < col; j++){
      returnMatrix.array[i][j] = 0;
      returnMatrix.array[i][i] = 1;
    }
  }
  return returnMatrix;
}
