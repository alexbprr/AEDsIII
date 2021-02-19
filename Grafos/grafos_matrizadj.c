#include <stdio.h>
#include <stdlib.h> 

typedef struct TGrafo{
  int dir;       		//0 não direcionado, 1 direcionado, -1 grafo nao criado
  int qv;    		    //quantidade de vértices
  int **matrizadj; //matriz de adjacência alocada dinamicamente
} Grafo;

Grafo* criaGrafo(int dir, int qv){
    Grafo* g = (Grafo*) malloc(sizeof(Grafo)); 
    g->dir = dir; 
    g->qv = qv; 
    //Aloca a matriz |V|x|V| 
    g->matrizadj = (int**) malloc(qv*sizeof(int*));
    for (int i = 0; i < qv; i++)
        g->matrizadj[i] = (int*) malloc(qv*sizeof(int));
    return g; 
}

void inicializaMatrizAdj(Grafo* g){
    for (int i = 0; i < g->qv; i++) 
        for (int j = 0; j < g->qv; j++)
            g->matrizadj[i][j] = 0;
}

void criaAresta(Grafo* g, int u, int v, int peso){
    if (u < 0 || u >= g->qv) return;
    if (v < 0 || v >= g->qv) return;
    if (g->dir)
        g->matrizadj[u][v] = peso; 
    else {
        g->matrizadj[u][v] = peso; 
        g->matrizadj[v][u] = peso; 
    } 
}

void imprimeMatrizAdj(Grafo* g){
    printf("Matriz de adjacência:\n"); 
    for (int i = 0; i < g->qv; i++) {
        for (int j = 0; j < g->qv; j++)
            printf(" %d ", g->matrizadj[i][j]);
        printf("\n");
    }
}

void liberaGrafo(Grafo *g){
    for (int i = 0; i < g->qv; i++) 
        free(g->matrizadj[i]);
    free(g->matrizadj); 
    free(g); 
}

int main(){
    int qv, dir; 
    printf("Qual a quantidade de vertices do grafo:\n"); 
    scanf("%d", &qv);
    printf("O grafo é direcionado (1) ou não (0):\n");
    scanf("%d", &dir);

    if (qv <= 0){
        printf("Digite um valor válido para a quantidade de vertices\n");
        exit(1); 
    }
    if (dir != 0 && dir != 1){
        printf("Digite um valor válido para o tipo de grafo\n");
        exit(1); 
    }

    Grafo* grafo = criaGrafo(dir,qv); 
    inicializaMatrizAdj(grafo); 
    int u = 0, v, peso; 
    while (u != -1){
        printf("Digite os vertices de origem, destino e o peso da aresta (origem -1 para sair):\n");         
        scanf("%d %d %d", &u, &v, &peso);
        criaAresta(grafo,u,v,peso);         
    }
    imprimeMatrizAdj(grafo); 

    liberaGrafo(grafo);
    return 0; 
}