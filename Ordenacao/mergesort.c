#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

void merge(int* V, int inicio, int meio, int fim)
{
    int* temp, p1, p2, tamanho, i, j, k;
    int fim1 = 0, fim2 = 0;
    tamanho = fim - inicio + 1;
    p1 = inicio;
    p2 = meio + 1;
    temp = (int*) malloc(tamanho*sizeof(int));
    if (temp != NULL)
    {
        for(i=0; i < tamanho; i++)
        {
            if (!fim1 && !fim2)
            {
                if (V[p1] < V[p2])
                    temp[i] = V[p1++];
                else
                    temp[i] = V[p2++];

                if (p1 > meio) fim1 = 1;  //Flag que indica se a partição esquerda acabou
                if (p2 > fim) fim2 = 1;  //Flag que indica se a partição direita acabou
            }
            else
            {
                if (!fim1)
                    temp[i] = V[p1++];
                else
                    temp[i] = V[p2++];
            }
        }
        printf("Resultado do merge para (inicio,meio,fim)=(%d,%d,%d)\n", inicio,meio,fim);
        //Copia os dados intercalados de volta para V
        for (j=0, k=inicio; j < tamanho; j++,k++)
        {
            printf("%d ", temp[j]);
            V[k] = temp[j];
        }
        printf("\n");
        free(temp);
    }
}

void mergesort(int *V, int inicio, int fim, int *cont){
    (*cont)++;
    printf("Ativação de mergesort para inicio = %d, fim = %d\n", inicio, fim);
    int meio;
    if (inicio < fim){
        meio = floor((inicio+fim)/2);
        mergesort(V, inicio, meio, cont);
        mergesort(V, meio+1, fim, cont);
        merge(V,inicio,meio,fim);
    }
}

int main(int argc, char* argv[])
{
    if (argc > 1)
    {
        srand(time(NULL));
        int SIZE = atoi(argv[1]);
        int *meuVetor = (int*) malloc(SIZE*sizeof(int));
        for (int i=0; i < SIZE; i++)
        {
            meuVetor[i] = rand()%(100*SIZE);
        }
        int numAtivacoes = 0;
        printf("Vetor inicial:\n");
        for (int i=0; i < SIZE; i++)
            printf("%d ", meuVetor[i]);
        printf("\n");

        mergesort(meuVetor,0,SIZE-1,&numAtivacoes);

        printf("Vetor ordenado:\n");
        for (int i=0; i < SIZE; i++)
            printf("%d ", meuVetor[i]);
        printf("\n");
        printf("Número de ativações: %d\n", numAtivacoes);
        free(meuVetor);
    }
    else
        printf("Digite o tamanho do vetor na linha de argumento\n");
    return 0;
}
