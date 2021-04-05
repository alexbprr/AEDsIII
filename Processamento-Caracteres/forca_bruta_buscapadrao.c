#include <stdio.h>
#include <stdlib.h>
#define N 20000

void forcaBruta(char* T, char* P, int n, int m){
    int i, j, k, cont = 0;
    for(i=0; i < n - m; i++) {
        k = i;
        j = 0;
        while (j < m && T[k] == P[j]){
            k++;
            j++;
        }
        if(j == m){
            cont++;
            printf("Padrão encontrado na posição %d\n", i); 
        }
    }
    printf("Foram encontradas %d ocorrências do padrão.\n",cont);
}

int main(){
    char *T = (char*) malloc(N*sizeof(char));
    FILE* texto = fopen("texto_de_entrada.txt", "r");
    fread(T,sizeof(char),N,texto);
    fclose(texto);
    int m;
    printf("Digite o tamanho do padrão:");
    scanf("%d",&m);
    char *P = (char*) malloc(m*sizeof(char));
    printf("Digite o padrão buscado: ");
    scanf("%s",P);
    forcaBruta(T,P,N,m);
}