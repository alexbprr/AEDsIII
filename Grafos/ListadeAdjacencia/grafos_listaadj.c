#include <stdio.h>
#include <stdlib.h> 

typedef struct TListaAdj{
	int id; //id do vértice adjacente
    float peso; //peso da aresta 
	struct TListaAdj *prox;
} ListaAdj;

typedef struct TGrafo{
  int dir;       	   //0 não direcionado, 1 direcionado, -1 grafo nao criado  
  int qv;              //quantidade de vértices 
  ListaAdj** lista_adj; //lista de adjacência alocada dinamicamente 
} Grafo;

Grafo* criaGrafo(int dir, int qv){
    Grafo* g = (Grafo*) malloc(sizeof(Grafo)); 
    g->dir = dir; 
    g->qv = qv; 
    //Aloca a lista de tamanho |V| 
    g->lista_adj = (ListaAdj**) malloc(qv*sizeof(ListaAdj*));
    for (int i = 0; i < qv; i++) 
        g->lista_adj[i] = NULL; 
    return g; 
}

void criaAresta(Grafo* g, int u, int v, float peso){
    if (u < 0 || u >= g->qv) return;
    if (v < 0 || v >= g->qv) return;
    //Aloca um novo nó para guardar as informações (v,peso) na lista de u 
    ListaAdj* no = (ListaAdj*) malloc(sizeof(ListaAdj));
    no->id = v;
    no->peso = peso; 
    no->prox = NULL; 
    if (g->dir) {
        if (g->lista_adj[u] == NULL)
            g->lista_adj[u] = no; 
        else {
            no->prox = g->lista_adj[u];
            g->lista_adj[u] = no; 
        } 
    }
    else {
        if (g->lista_adj[u] == NULL)
            g->lista_adj[u] = no; 
        else {
            no->prox = g->lista_adj[u];
            g->lista_adj[u] = no; 
        }
        ListaAdj* nou = (ListaAdj*) malloc(sizeof(ListaAdj));
        nou->id = u;
        nou->peso = peso; 
        nou->prox = NULL; 
        if (g->lista_adj[v] == NULL)
            g->lista_adj[v] = nou; 
        else {
            nou->prox = g->lista_adj[v];
            g->lista_adj[v] = nou; 
        }
    } 
}

void imprimeListasAdj(Grafo* g){
    printf("Listas de adjacência:\n"); 
    for (int i = 0; i < g->qv; i++) {
        printf("Adjacentes de %d:\n", i);
        if (g->lista_adj[i] != NULL){
            ListaAdj* p = g->lista_adj[i]; 
            while (p != NULL){
                printf(" vertice: %d, peso: %f;", p->id, p->peso);
                p = p->prox; 
            }
        }            
        printf("\n");
    }
}

void liberaGrafo(Grafo* g){
    for (int i = 0; i < g->qv; i++) {
        ListaAdj* p = g->lista_adj[i], *q;         
        while (p != NULL){
            q = p;
            p = p->prox; 
            free(q); 
        }        
    }
    free(g->lista_adj);
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
    int u = 0, v;
    float peso;  
    while (u != -1){
        printf("Digite os vertices de origem, destino e o peso da aresta (origem -1 para sair):\n");         
        scanf("%d %d %f", &u, &v, &peso);
        criaAresta(grafo,u,v,peso);         
    }
    imprimeListasAdj(grafo); 

    liberaGrafo(grafo); 
    return 0; 
}