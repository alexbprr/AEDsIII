#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define A_SIZE 10

int somaVetor(int N, int *A)
{
    int i;
    int somaglobal = 0;
    #pragma omp parallel num_threads(N) shared(A) 
    {
        int minha_soma = 0; //privada
        #pragma omp for private(i, minha_soma) //schedule(static,2)
        for(i=0; i < A_SIZE; i++)
	    {
            minha_soma += A[i];
            printf("Meu id é %d e meu i é %d\n", omp_get_thread_num(), i);
            printf("Minha soma é %d\n", minha_soma);
	        fflush(stdout);
	    }

        #pragma omp critical
        somaglobal += minha_soma;
    }
    return somaglobal;
}

int main(int argc, char* argv[]){
    if (argc == 1){
        printf("Digite a quantidade de threads.\n");
        exit(1);
    }
    int N = strtol(argv[1], NULL, 10);
    int *A = malloc(A_SIZE*sizeof(int));
    printf("Vetor A:");
    for (int j=0; j < A_SIZE; j++) {
        A[j] = A_SIZE-j;
        printf("%d ", A[j]);
    }
    printf("\n");
    printf("A soma total é %d\n", somaVetor(N,A));
    return 0;
}
