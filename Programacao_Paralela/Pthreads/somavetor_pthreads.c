#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define A_SIZE 10

//Variáveis globais compartilhadas entre todas as threads
pthread_t* threads;
pthread_mutex_t mutex;
int N, somaglobal;

typedef struct param
{
    int id;
    int* A;
}parameters;

void *somaVetor(void* p){
    int meuid, q, inicio, fim, minhasoma = 0; //Variáveis privadas: cada thread tem a sua cópia
    parameters* p2 = (parameters*) p;
    meuid = p2->id;
    q = (A_SIZE/N);
    inicio = q*meuid;
    printf("meuid: %d\n", meuid);
    printf("inicio: %d\n", inicio);
    if (meuid == N-1)
        fim = A_SIZE;
    else
        fim = inicio + q;
    printf("fim: %d\n", fim);

    for (int i=inicio; i < fim; i++)
        minhasoma += p2->A[i];

    printf("Meu id é %d e minha soma é %d\n", meuid, minhasoma);
    pthread_mutex_lock(&mutex);//Cria uma seção crítica //adquire o lock 
    printf("Thread %d adquiriu o lock\n", meuid);
    somaglobal += minhasoma; //Somente uma thread executa essa atribuição 
    printf("Soma global %d\n", somaglobal);
    pthread_mutex_unlock(&mutex); //Libera o lock 
    return &(somaglobal);
}

int main(int argc, char* argv[])
{
    if (argc == 1){
        printf("Digite a quantidade de threads.\n");
        exit(1);
    }
    N = strtol(argv[1], NULL, 10);
    threads = malloc(N*sizeof(pthread_t));
    parameters *p = malloc(N*sizeof(parameters));
    //Define os parâmetros de cada thread
    for (int i=0; i < N; i++)
    {
        p[i].A = malloc(A_SIZE*sizeof(int));
        printf("Vetor A:");
        for (int j=0; j < 10; j++)
        {
            p[i].A[j] = 10-j;
            printf("%d ", p[i].A[j]);
        }
        printf("\n");
        p[i].id = i; //O id da primeira thread criada é 0, da segunda é 1 e, assim por diante.
    }
    int *somaglobal;
    //Cria as threads para executar somaVetor em paralelo
    for (int i=0; i < N; i++)
        pthread_create(&threads[i], NULL, somaVetor, (void*) &(p[i]));

    //Termina as threads
    for (int i=0; i < N; i++)
        pthread_join(threads[i],(void*)&somaglobal);
    printf("A soma total é %d\n", *somaglobal);

    for (int i=0; i < N; i++)
        free(p[i].A);
    free(p);
    free(threads);
  return 0;
}
