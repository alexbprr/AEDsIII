#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define N 20 //Número máximo de registros que cabem na memória.
#define M 100 //Número de linhas no arquivo de entrada.

int particiona_int(int vetor[], int inicio, int fim)
{
    int esq, dir;
    int pivo, aux;
    esq = inicio;
    dir = fim;
    pivo = vetor[inicio];
    while(esq<dir)
    {
            while(vetor[esq] <= pivo && esq<fim) // vetor[esq] <= pivo
                    esq++;

            while(pivo < vetor[dir]) //  vetor[dir] > pivo
                    dir--;

            if(dir < inicio || esq > fim) printf("\nERRO\n\n");
            if(esq < dir)
            {
                    aux = vetor[esq]; // troca vetor[esq] com vetor[dir]
                    vetor[esq] = vetor[dir];
                    vetor[dir] = aux;
            }
    }
    vetor[inicio] = vetor[dir];
    vetor[dir] = pivo;
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

typedef struct Tarquivo {
    FILE *f;
    int pos, MAX, *buffer;
} arquivo;

void preencheBuffer(arquivo* arq, int T);
int procuraMenor(arquivo* arq, int K, int T, int *menor);
void salvaArquivo(char* nome, int *V, int tam, int mudaLinhaFinal);
int criaArquivosOrdenados(char* nome);

//Gera um arquivo com valores inteiros aleatórios
void criaArquivoTeste(char* nome)
{
    int i;
    FILE* f = (FILE*)fopen(nome, "w");
    srand(time(NULL));
    for(i=1; i < M; i++)
        fprintf(f, "%d\n", rand()%(50*M));
    fprintf(f, "%d", rand()%(50*M));
    fclose(f);
    char command[100];
    sprintf(command, "cp %s teste_backup.txt\n", nome);
    system(command);
}

void merge(char* nome, int K, int T)
{
    char novo[20];
    int i;
    int *saida = (int*)malloc(T*sizeof(int));
    arquivo *arq;
    arq = (arquivo*) malloc(K*sizeof(arquivo));
    for (i=0; i < K; i++)
    {
        sprintf(novo,"Temp%d.txt", i+1);
        arq[i].f = (FILE*) fopen(novo,"r");
        arq[i].buffer = (int*)malloc(T*sizeof(int));
        preencheBuffer(&arq[i],T);
    }
    int menor, qtdSaida = 0;
    while(procuraMenor(arq,K,T,&menor) == 1)
    {
        saida[qtdSaida] = menor;
        qtdSaida++;
        if (qtdSaida == T)
        {
            salvaArquivo(nome,saida,T,1);
            qtdSaida = 0;
        }
    }
    if (qtdSaida != 0)
        salvaArquivo(nome,saida,qtdSaida,1);

    for(i=0; i < K; i++)
        free(arq[i].buffer);
    free(arq);
    free(saida);
}

void preencheBuffer(arquivo* arq, int T)
{
    int i;
    if (arq->f == NULL) return;
    arq->pos = 0;
    arq->MAX = 0;
    for(i=0; i < T; i++)
    {
        if (!feof(arq->f))
        {
            fscanf(arq->f,"%d",&arq->buffer[arq->MAX]);
            arq->MAX++;
        }
        else
        {
            fclose(arq->f);
            arq->f = NULL;
            break;
        }
    }
}

/*
A função procuraMenor() percorre todos os buffers de entrada que ainda
contém dados e os compara para verificar qual deles tem o menor valor.
O índice do buffer com menor elemento é retornado em idx.
 . Caso foi encontrado, o menor elemento é copiado para a variável passada por
referência e a posição atual do buffer é incrementada. Quando o buffer acaba de ser processado
(arq[idx].pos == arq[idx].MAX), ele é preenchido com novos dados do arquivo.
 . Caso o menor elemento não foi encontrado, significa que não existem mais dados
 nos buffers de entrada e o processo de intercalação deve terminar.
A função retorna 1 para indicar sucesso e 0 para indicar falha.
*/
int procuraMenor(arquivo* arq, int K, int T, int *menor)
{
    int i, idx = -1;
    for (i=0; i < K; i++)
    {
        if (arq[i].pos < arq[i].MAX)
        {
            if (idx == -1)
                idx = i;
            else {
                if (arq[i].buffer[arq[i].pos] < arq[idx].buffer[arq[idx].pos])
                    idx = i; //Define o novo indice do menor valor
            }
        }
    }
    if (idx != -1) //Se foi encontrado um menor valor
    {
        *menor = arq[idx].buffer[arq[idx].pos];
        arq[idx].pos++;
        if (arq[idx].pos == arq[idx].MAX)
            preencheBuffer(&arq[idx],T);
        return 1;
    }
    else
        return 0;
}

int criaArquivosOrdenados(char* nome)
{
    int V[N], K = 0, total = 0, cont=0;
    char novo[20];
    FILE* f = (FILE*)fopen(nome,"r");
    while(!feof(f))
    {
        fscanf(f, "%d", &V[total]);
        total++;
        if (total == N)
        {
            K++;
            sprintf(novo,"Temp%d.txt",K);
            quick_int(V,0,N-1,&cont);
            salvaArquivo(novo,V,total,0);
            total = 0;
        }
    }
    if (total > 0)
    {
        K++;
        sprintf(novo, "Temp%d.txt", K);
        quick_int(V,0,total-1,&cont);
        salvaArquivo(novo,V,total,0);
    }
    fclose(f);
    return K;
}

//Faz a ordenação externa.
void mergesortExterno(char* nome)
{
    char novo[20];
    int K = criaArquivosOrdenados(nome);
    int i;
    int T = N/(K+1); //Calcula o tamanho T dos K+1 buffers.
    printf("K: %d\n", K);
    printf("T: %d\n", T);
    remove(nome);
    merge(nome,K,T);
    for (i=0; i < K; i++)
    {
        sprintf(novo,"Temp%d.txt", i+1);
        //remove(novo);
    }
}

void salvaArquivo(char* nome, int *V, int tam, int mudaLinhaFinal)
{
    int i;
    FILE* f = (FILE*)fopen(nome,"a");
    for (i=0; i < tam-1; i++)
        fprintf(f, "%d\n", V[i]);
    if (mudaLinhaFinal == 0)
        fprintf(f,"%d",V[tam-1]);
    else
        fprintf(f,"%d\n",V[tam-1]);
    fclose(f);
}

int main(int argc, char* argv[])
{
    criaArquivoTeste("teste2.txt");
    mergesortExterno("teste2.txt");
    return 0;
}
