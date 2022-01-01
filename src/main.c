#include "matrix_operators.h"

int main(){
    Matrix k,k1; 
    int status = ma_alloc(&k,5,5);
    status = ma_alloc(&k1,5,5);
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            k.array[i][j] = j;
            k1.array[i][j] = j;
        }
    }
    printMatrix(&k);
    printf("\n");
    printMatrix(&k1);
    printf("\n");
    Matrix k6 = ones(4,5);
    printMatrix(&k6);
    printf("\n");
    ma_realloc(&k6,6,5);
    printMatrix(&k6);
    k6 = cat(&k,&k1,1);
    printf("\n");
    printMatrix(&k6);
    ma_free(&k);
    ma_free(&k1);
    ma_free(&k6);
}
