#ifndef H_Grafo
#define H_Grafo 
#include <stdio.h>
#include <stdlib.h>

typedef struct TGrafo{
  int dir;       		//0 não direcionado, 1 direcionado, -1 grafo nao criado
  int qv;    		    //quantidade de vértices
  int **matrizadj; //matriz de adjacência alocada dinamicamente
  int **dist;   //Matriz de distâncias
} Grafo;

Grafo* criaGrafo(int dir, int qv);

void inicializaMatrizAdj(Grafo* g);

void criaAresta(Grafo* g, int u, int v, int peso);

void imprimeMatrizAdj(Grafo* g);

void liberaGrafo(Grafo *g);

#endif