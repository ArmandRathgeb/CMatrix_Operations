#include "matrix_operators.h"
#include <stdio.h>

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
    printf("\n");
    k6 = cat(&k,&k1,1);
    printMatrix(&k6);
    printf("\n");
    Matrix k3 = getCofactor(&k6, 0, 0);
    printMatrix(&k3);
    printf("\n");
    ma_realloc(&k3, 3, 3);
    printf("%f\n", det(&k3));
    ma_free(&k);
    ma_free(&k1);
    ma_free(&k3);
    ma_free(&k6);
}
