#include <stdio.h>
#include <stdlib.h>
#include <time.h>

float maior(int *v, int left, int right){
    if (left == right){ //Caso base 
        return v[left];
    }
    else { //Divide o vetor ao meio e compara na volta    
        int meio = (left + right)/2;
        float maiorleft = maior(v,left,meio);
        float maiorright = maior(v,meio+1,right);
        if (maiorleft > maiorright) {
            printf("O maior entre %d e %d é %f\n", left, right, maiorleft);
            return maiorleft;
        }
        else {
            printf("O maior entre %d e %d é %f\n", left, right, maiorright);
            return maiorright;
        }
    }
}

int main(){
    int N = 50;
    int *v = (int*) malloc(N*sizeof(int));
    srand(time(NULL));
    for(int i=0; i < N; i++){
        v[i] = rand()%(N*100);
        printf("v[%d] = %d\n", i, v[i]);
    }
    printf("O maior elemento do vetor é: %f\n", maior(v,0,N-1));
    free(v);
    return 0;
}
