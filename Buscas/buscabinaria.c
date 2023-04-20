#include <stdio.h>

#define N 9

int buscaBinaria(int vetor[N], int ch) {
    int inicio = 0, fim = N - 1, meio = -1;

    while (inicio <= fim) {

        meio = (inicio + fim) / 2;
        printf("%d %d %d\n", inicio, meio, fim);
        printf("%d\n", vetor[meio]);
        if (ch == vetor[meio]) {
            return meio;
        } else if (ch < vetor[meio]) {
            fim = meio - 1;
        } else {
            inicio = meio + 1;
        }
    }
    return -1;
}

int main(){
    int vetor[N] = {-8,4,7,21,23,54,67,82,90};
    int r = buscaBinaria(vetor,1);
    if (r != -1)
        printf("Chave encontrada na posição %d\n", r); 
    else 
        printf("Chave não encontrada\n"); 
    return 0; 
}