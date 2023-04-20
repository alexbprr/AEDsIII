#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/resource.h>

typedef struct TElemento {
    int ch; //chave
    char* str;
    float f1;
} elemento;

int particiona_struct(elemento* vetor, int inicio, int fim)
{
    int esq, dir;
    elemento pivo, aux;
    esq = inicio;
    dir = fim;
    pivo = vetor[inicio];
    while(esq < dir)
    {
            while(vetor[esq].ch <= pivo.ch && esq < fim)
                    esq++;

            while(pivo.ch < vetor[dir].ch)
                    dir--;

            if(esq < dir)
            {
                    aux = vetor[esq]; // troca vetor[esq] com vetor[dir]
                    vetor[esq] = vetor[dir];
                    vetor[dir] = aux;
            }
    }
    vetor[inicio] = vetor[dir];
    vetor[dir] = pivo;
    printf("Vetor ordenado entre %d e %d\n", inicio, fim);
    for (int i=inicio; i <= fim; i++)
         printf("%d ", vetor[i].ch);
    printf("\n");
    //retorna dir, que é o novo pivo
    return dir;
}

void quick_struct(elemento *vetor, int inicio, int fim, int *cont)
{
    (*cont)++;
    int pivo;
    if(inicio < fim)
    {
        pivo = particiona_struct(vetor,inicio,fim); // encontra um pivo que "divide" o vetor em dois
        quick_struct(vetor, inicio, pivo-1, cont); // realiza a partição para a parte da esquerda
        quick_struct(vetor, pivo+1, fim, cont); // e realiza a partição para a parte de direita
    }
}

int particiona_int(int vetor[], int inicio, int fim)
{
    int esq, dir;
    int pivo, aux;
    esq = inicio;
    dir = fim;
    pivo = vetor[inicio];

    printf("\nVetor entre %d e %d\n", inicio, fim);
    for (int i=inicio; i <= fim; i++)
         printf("%d ", vetor[i]);
    printf("\n");
    printf("Pivo: %d\n", pivo);

    while(esq < dir)
    {
        while(vetor[esq] <= pivo && esq<fim) // vetor[esq] <= pivo
            esq++;

        while(pivo < vetor[dir]) //  vetor[dir] > pivo
            dir--;

        if(esq < dir)
        {
            printf("Troca %d e %d\n", vetor[esq], vetor[dir]);
            aux = vetor[esq]; // troca vetor[esq] com vetor[dir]
            vetor[esq] = vetor[dir];
            vetor[dir] = aux;
        }
    }
    vetor[inicio] = vetor[dir];
    vetor[dir] = pivo;
    printf("Vetor entre %d e %d\n", inicio, fim);
    for (int i=inicio; i <= fim; i++)
         printf("%d ", vetor[i]);
    printf("\n");
    printf("Novo pivo: %d\n", vetor[dir]);
    return dir;               //retorna dir, que é o índice que vai dividir o vetor
}

void quick_int(int vetor[], int inicio, int fim, int *cont)
{
    (*cont)++;
    int pivo;
    if(inicio < fim)
    {
        pivo = particiona_int(vetor,inicio,fim); // encontra um pivo que "divide" o vetor em dois
        quick_int(vetor, inicio, pivo-1, cont); // realiza a partição para a parte da esquerda
        quick_int(vetor, pivo+1, fim, cont); // e realiza a partição para a parte de direita
    }
}

int main(int argc, char* argv[])
{
    struct rusage resources;
    int rc;
    double utime, stime, total_time;
    if (argc > 1)
    {
            srand(time(NULL));
            int SIZE = atoi(argv[1]);
            int K = 10;
            //int vetor[7] = {23,4,67,-8,90,54,21};

            int vetor[8] = {35, 50, 40, 57, 9, 6, 7, 14};

            // elemento* vetor = (elemento*)malloc(SIZE*sizeof(elemento));
            //
            // char letras[10] = {'a','b','c','d','e','f','g','h','i','j'};
            //int *vetor = (int*) malloc(SIZE*sizeof(int));
            // for (int i=0; i < SIZE; i++)
            // {
            //     vetor[i].ch = abs(rand()%(100*SIZE));
            //     //Lógica para preencher str e f1
            //     vetor[i].f1 = (float)rand()/RAND_MAX;
            //     vetor[i].str = (char*)malloc(K*sizeof(char));
            //     for (int j=0; j < K; j++)
            //     {
            //         vetor[i].str[j] = letras[rand()%K];
            //     }
            // }
            //
            // for (int i=0; i < SIZE; i++)
            // {
            //     vetor[i] = abs(rand()%(10*SIZE));
            // }
            int numAtivacoes = 0;
            //SIZE = 8;
            printf("Vetor inicial:\n");
            for (int i=0; i < SIZE; i++)
                    printf("%d ", vetor[i]);
            printf("\n");

            //quick_struct(vetor,0,SIZE-1,&numAtivacoes);
            quick_int(vetor,0,SIZE-1,&numAtivacoes);

            // printf("Vetor ordenado:\n");
            // for (int i=0; i < SIZE; i++)
            //         printf("%d %f %s\n", vetor[i].ch, vetor[i].f1, vetor[i].str);
            // printf("\n");
            // printf("Número de ativações: %d\n", numAtivacoes);

            // for (int i=0; i < SIZE; i++)
            //     free(vetor[i].str);
            // free(vetor);
    }
    else
            printf("Digite o tamanho do vetor na linha de argumento\n");
    return 0;
}
