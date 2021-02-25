// Busca em profundidade em C++ 
#include <iostream> 
#include <list> 
using namespace std;
 
class Graph { 
public:
    Graph(int d, int V);
    ~Graph(); 
    void addEdge(int u, int v); //(origem,destino)
    void DFS(int v);
private:     
    int dir; //Direcionado ou não direcionado 
    int V; //num de vertices 
    list<int>* adj; //Vetor de ponteiros para as listas de adjacência 
    void DFSUtil(int v, bool visited[]);
};
 
Graph::Graph(int d, int V){
    dir  = d;
    this->V = V;    
    adj = new list<int>[V]; //Aloca espaço 
}

Graph::~Graph(){
    delete[] adj;
}
 
void Graph::addEdge(int u, int v) {
    if (dir == 0) {
        adj[u].push_back(v); 
        adj[v].push_back(u); 
    }
    else 
        adj[u].push_back(v); 
}
 
void Graph::DFSUtil(int v, bool visited[]){
    visited[v] = true;
    cout << v << " ";
    list<int>::iterator i;
    for (int i: adj[v])
        if (!visited[i])
            DFSUtil(i, visited);
}
 
void Graph::DFS(int v){
    bool* visited = new bool[V];
    for (int i = 0; i < V; i++)
        visited[i] = false;
 
    DFSUtil(v, visited);
}
 
int main(){
    // Create a graph given in the above diagram
    Graph *g = new Graph(0, 4);
    g->addEdge(0, 1);
    g->addEdge(0, 2);
    g->addEdge(1, 2);
    //g->addEdge(2, 0);
    g->addEdge(2, 3);
    g->addEdge(3, 3);
 
    int v = 3;
    cout << "Busca em profundidade começando do vértice " << v << ":" << endl;             
    g->DFS(v);
    delete g; 
    return 0;
}