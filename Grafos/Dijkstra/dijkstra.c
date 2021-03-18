#include <stdio.h> 
#include <stdlib.h> 
#include "grafo.h"

void adjacentes(int v, Grafo* g, int **adjs, int *num_adj){
    int n_columns = g->qv;
    *num_adj = 0;
    (*adjs) = (int*) malloc(n_columns*sizeof(int));
    for(int i = 0; i < n_columns; i++){
        if (g->matrizadj[v][i] > 0)
            (*adjs)[(*num_adj)++] = i;
    }
}

int minDistance(Grafo* g, int **selecionados, int source){
    int V = g->qv;
    int min_index, max_dist = 1E08;    
    float value, min = max_dist;
    for (int v = 0; v < V; v++){
        value = g->dist[source][v];
        if (selecionados[source][v] == 0 && value < min){
            min = g->dist[source][v];
            min_index = v;
        }
    }
    return min_index;
}

void dijkstra(Grafo* g, int source){
    int V = g->qv, v, max_dist = 1E08;
    //para cada vértice eu armazeno o predecessor dele no caminho mínimo até a fonte
    int **pred = (int**) malloc(V*sizeof(int*));
    int **selecionados = (int**) malloc(V*sizeof(int*));
    g->dist = (int**) malloc(V*sizeof(int*));
    int *adjs, num_adj = 0;
    for (int i = 0; i < V; i++){
        pred[i] = (int*) malloc(V*sizeof(int));
        selecionados[i] = (int*) malloc(V*sizeof(int));
        g->dist[i] = (int*) malloc(V*sizeof(int));
    }

    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++){
            selecionados[i][j] = 0; 
            pred[i][j] = -1;
            g->dist[i][j] = max_dist; 
        }
    }

    g->dist[source][source] = 0;
    for (int count = 0; count < V-1; count++){
        int u = minDistance(g, selecionados, source);
        printf("escolha gulosa: u = %d\n", u);
        selecionados[source][u] = 1;
        adjacentes(u,g,&adjs,&num_adj);
        for (int i = 0; i < num_adj; i++){
            v = adjs[i];
            if (!selecionados[source][v] && g->dist[source][u] != max_dist
                && g->dist[source][u] + g->matrizadj[u][v] < g->dist[source][v]){
                g->dist[source][v] = g->dist[source][u] + g->matrizadj[u][v];
                pred[source][v] = u;
            }
        }
    }

    printf("Origem = %d:\n", source);
    printf("Distâncias mínimas:\n");
    for (int i = 0; i < V; i++){
        printf("para %d: d = %d\n", i, g->dist[source][i]);
    }

    int pos, u, j, k, u0;
    int shortest_path_aux[V];
    for (int i = 0; i < V; i++){
        for (j = 0; j < V; j++){
            shortest_path_aux[j] = -1;
        }
        //Imprime o caminho minimo
        pos = 0;
        u = pred[source][i];
        u0 = u;
        while (u != -1){
            shortest_path_aux[pos] = u;
            u = pred[source][u];
            pos++;
        }
        //Testa se não existe vertice no menor caminho e se o destino não é adjacente à origem.
        if (u0 == -1 && g->matrizadj[source][i] == 0)
            continue;

        printf("Caminho mínimo para o vertice %d:\n", i);
        for(k = pos-1; k >= 0; k--){
            printf("%d - ", shortest_path_aux[k]);
        }
        printf("%d", i);
        printf("\n--------//------\n");
    }

    for (int i = 0; i < V; i++){
        free(pred[i]);
        free(selecionados[i]);
        free(g->dist[i]);
    }
    free(pred);
    free(selecionados);
    free(g->dist);
}

int main(){
    Grafo *g = criaGrafo(0, 5);
    inicializaMatrizAdj(g);
    
    g->matrizadj[0][1] = 10;
    g->matrizadj[1][0] = 10;
    g->matrizadj[0][2] = 5;
    g->matrizadj[2][0] = 5;
    g->matrizadj[1][2] = 6;
    g->matrizadj[2][1] = 6;
    g->matrizadj[1][3] = 1;
    g->matrizadj[3][1] = 1;
    g->matrizadj[2][3] = 2;
    g->matrizadj[3][2] = 2;
    g->matrizadj[2][4] = 1;
    g->matrizadj[4][2] = 1;
    g->matrizadj[4][3] = 2;
    g->matrizadj[3][4] = 2;

    dijkstra(g,0);
    //dijkstra(g,1);
    //dijkstra(g,3);
    free(g);
}