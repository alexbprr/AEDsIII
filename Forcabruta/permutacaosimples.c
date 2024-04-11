#include <stdio.h>
#include <stdlib.h>
#include<stdio.h>

void permutacao(int n, int x[], int used[], int k){
    int i;
    if (k == n){
        for (i = 0; i < n; i++)
            printf("%d ", x[i] + 1);
        printf("\n");
    }
    else{
        for (i = 0; i < n; i++){
            if (!used[i]){
                used[i] = 1;
                x[k] = i;
                permutacao(n, x, used, k + 1);
                used[i] = 0;
            }
        }
    }
}

int main(){
    int i, n;
    printf("Entre com o valor de n: ");
    scanf("%d", &n);
    int x[n], used[n];
    /* se um elemento i estiver em uso, entao used[i] = 1,
    caso contrario, used[i] = 0. */
    for (i = 0; i < n; i++)
        used[i] = 0;
    permutacao(n, x, used, 0);
    return 0;
}
