#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

void le_sequencia(char *nome_arquivo, char *seq, int tam){
    FILE *arq;
    arq = fopen(nome_arquivo, "r");
    fscanf(arq, "%s", seq);
}

void bmhs(char *texto, char *padrao, int *posicoes, int M, int N, int lastOcc[]){
    int i0 = 0, j, cont = 0;
    while (i0 < N-M){
        j = M - 1;
        while (texto[i0 + j] == padrao[j])
            j--;
        if(j < 0){
            printf("Casamento do padrao no indice: %d \n",i0);
            posicoes[cont] = 1;
            cont++;
        }                       
        i0 = i0 + M - lastOcc[texto[i0+M]];        
        printf("i0 = %d\n", i0);
    }
    printf("Foram encontradas %d ocorrências do padrão\n", cont);
}

int main(){
    int N, M, i;
    clock_t tInicio, tFim;
    double tDecorrido;
    time_t inicio, fim;
    printf("Digite o tamanho do padrão e do texto:\n");
    scanf("%d %d", &M, &N);
    char* padrao = (char*) malloc(M*sizeof(char));
    char* texto = (char*) malloc(N*sizeof(char));
    int* posicoes = (int*) malloc(N*sizeof(int));
    for (i = 0; i < N; i++)
        posicoes[i] = 0;

    printf("Digite qual o padrão procurado:\n");
    scanf("%s", padrao);

    int lastOcc[128];
    for (i=0; i < 128; i++)
        lastOcc[i] = -1;
    for (i=0; i < M; i++) //Começa a procurar do último caractere do padrão
        lastOcc[padrao[i]] = i;

    le_sequencia("dna.txt", texto, N);
    tInicio = clock();
    bmhs(texto, padrao, posicoes, M, N, lastOcc);
    tFim = clock();
    tDecorrido = ((double)(tFim - tInicio) / CLOCKS_PER_SEC );
    printf("Tempo de Execucao do BMHS %f\n",tDecorrido);
    
    free(padrao);
    free(texto);
    free(posicoes);
    return 0; 
}