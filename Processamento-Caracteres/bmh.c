#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

void le_sequencia(char *nome_arquivo, char *seq, int tam){
    FILE *arq;
    arq = fopen(nome_arquivo, "r");
    fscanf(arq, "%s", seq);
}

void bmh(char *texto, char *padrao, int *posicoes, int M, int N, int lastOcc[]){
    int i0 = 0, j, cont = 0;
    while (i0 < N-M){
        j = M - 1;
        while (texto[i0 + j] == padrao[j]){
            j--;
        }
        if(j < 0){
            printf("Casamento do padrao no indice: %d \n",i0);
            posicoes[cont] = 1;
            cont++;
        }        
        i0 = i0 + (M-1 - lastOcc[texto[i0+M-1]]);        
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

    int lastOcc[255];
    for (i=0; i < 255; i++)
        lastOcc[i] = -1;
    for (i=0; i < M-1; i++)
        lastOcc[padrao[i]] = i;
        
    le_sequencia("dna.txt", texto, N);
    tInicio = clock();
    bmh(texto, padrao, posicoes, M, N, lastOcc);
    tFim = clock();
    tDecorrido = ((double)(tFim - tInicio) / CLOCKS_PER_SEC );
    printf("Tempo de Execucao do BMH %f\n",tDecorrido);
    free(padrao);
    free(texto);    
    //free(posicoes);

    return 0; 
}
