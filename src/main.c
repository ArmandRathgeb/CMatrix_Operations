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
    puts("K:\n");
    printMatrix(&k);
    puts("\nK1:\n");
    printMatrix(&k1);
    Matrix k6 = ones(4,5);
    puts("\nK6:\n");
    printMatrix(&k6);
    puts("\nK6 reallocated:\n");
    ma_realloc(&k6,6,5);
    printMatrix(&k6);
    puts("\nK6 as K and K1 concatenated:\n");
    k6 = cat(&k,&k1,1);
    printMatrix(&k6);
    puts("\nK3 as cofactor of K6:\n");
    Matrix k3 = getCofactor(&k6, 0, 0);
    printMatrix(&k3);

    ma_realloc(&k3, 3, 3);
    printf("\nDeterminant of K3: %f\n", det(&k3));

    ma_free(&k);
    ma_free(&k1);
    ma_free(&k3);
    ma_free(&k6);

}
