#include "grafo.h"

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