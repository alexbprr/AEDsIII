#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 10

typedef struct paciente {
    char nome[100];
    int prio;
} elemento;

typedef struct TFilaPrioridade{
    int qtd;
    elemento dados[MAX];
} FilaPrio;

/*Corrige violações na heap "promovendo" um elemento caso a sua prioridade é
maior do que a prioridade de seu pai*/
void promoverElemento(FilaPrio* fp, int filho)
{
    int pai;
    elemento temp;
    pai = (filho - 1)/2;
    while (filho > 0 && fp->dados[pai].prio < fp->dados[filho].prio)
    {
        temp = fp->dados[filho];
        fp->dados[filho] = fp->dados[pai];
        fp->dados[pai] = temp;
        filho = pai;
        pai = (filho - 1)/2;
    }
}

int insereFilaPrio(FilaPrio* fp, char* nome, int prio)
{
    if (fp == NULL)
        return 0;
    if (fp->qtd == MAX)
        return 0;
    strcpy(fp->dados[fp->qtd].nome, nome);
    fp->dados[fp->qtd].prio = prio;
    promoverElemento(fp,fp->qtd);
    fp->qtd++;
    return 1;
}

/*Corrige violações na heap "rebaixando" um elemento caso a prioridade de um dos
 seus filhos seja maior*/
void rebaixarElemento(FilaPrio* fp, int pai)
{
    elemento temp;
    int filho = 2*pai + 1;
    while (filho < fp->qtd)
    {
        if (filho < fp->qtd-1)
            if (fp->dados[filho].prio < fp->dados[filho+1].prio)
                filho++;
        if (fp->dados[pai].prio >= fp->dados[filho].prio)
            break;

        temp = fp->dados[filho];
        fp->dados[filho] = fp->dados[pai];
        fp->dados[pai] = temp;

        pai = filho;
        filho = 2*pai + 1;
    }
}

int removeFilaPrioridade(FilaPrio* fp)
{
    if (fp == NULL) return 0;
    if (fp->qtd == 0) return 0;
    fp->qtd--;
    fp->dados[0] = fp->dados[fp->qtd];
    rebaixarElemento(fp,0);
    return 1;
}

void printFilaPrioridade(FilaPrio* fp)
{
    printf("Fila de prioridades:\n");
    for (int i=0; i < fp->qtd; i++)
        printf("prio: %d; nome: %s \n", fp->dados[i].prio, fp->dados[i].nome);
    printf("\n");
}

/*É igual à função rebaixarElemento, exceto que passamos um parâmetro fim que
  define até qual posição o array não foi ordenado ainda. */
void criaHeap(FilaPrio* fp, int pai, int fim)
{
    elemento aux;
    int filho = 2*pai + 1;
    while (filho <= fim)
    {
        if (filho < fim)
            if (fp->dados[filho].prio < fp->dados[filho+1].prio)
                filho++;
        if (fp->dados[pai].prio >= fp->dados[filho].prio)
            break;

        /*Se a prioridade do filho for maior, troca pai e filho.
        Atualiza os indices pai e filho        */
        aux = fp->dados[pai];
        fp->dados[pai] = fp->dados[filho];
        fp->dados[filho] = aux;
        pai = filho;
        filho = 2*pai + 1;
    }
}

//fp: Fila de prioridades; N: número de elementos na fila (fp->qtd)
void heapsort(FilaPrio* fp, int N) {
    int i;
    elemento aux;
    for (i=N-1; i >= 1; i--)
    {
        aux = fp->dados[0];
        fp->dados[0] = fp->dados[i];
        fp->dados[i] = aux;
        printf("[Fila antes da reconstrução]");
        printFilaPrioridade(fp);
        criaHeap(fp, 0, i-1);
        printf("[Fila depois da reconstrução]");
        printFilaPrioridade(fp);
    }
}

int main(int argc, char* argv[])
{
    //23, 4, 67, -8, 90, 54, 21
    //35, 5, 2, 57, 9, 6, 7, 14
    // int vetor[8] = {35, 50, 40, 57, 9, 6, 7, 14};
    FilaPrio* fp = (FilaPrio*)malloc(sizeof(FilaPrio));
    insereFilaPrio(fp,"Carla",21);
    insereFilaPrio(fp,"Bob",12);
    insereFilaPrio(fp,"Alice",32);
    insereFilaPrio(fp,"Jent",41);
    insereFilaPrio(fp,"Alan",18);
    insereFilaPrio(fp,"Eduardo",67);
    insereFilaPrio(fp,"Beto",79);
    insereFilaPrio(fp,"re",26);
    insereFilaPrio(fp,"cx",35);
    //removeFilaPrioridade(fp);
    //removeFilaPrioridade(fp);
    printf("Antes da ordenação:\n\n");
    printFilaPrioridade(fp);
    heapsort(fp,fp->qtd);
    printf("Após ordenação:\n\n");
    printFilaPrioridade(fp);
    free(fp);
    return 0;
}
