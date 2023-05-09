#include <vector>
#include <map>
#include <string>
#include <queue>
#include <iostream> 
#include "random.h"
using namespace std;

typedef struct TEdge {
    int id; 
    int src;
    int dest; 
    float weight; 
    //other info 
    TEdge(){}
    TEdge(int s, int d, float w = 1){
        src = s;
        dest = d;
        weight = w;
    }
    void print(){
        std::cout << "Edge (src = " << src << ", dest = " << dest << ", weight = " << weight << ")" << std::endl;
    }
} Edge; 

typedef struct TVertex {
    int id; 
    std::string name; 
    std::vector< int > adjacents; 
    TVertex(){}
    TVertex(int vid): id(vid){}
    TVertex(int vid, std::string n): id(vid), name(n){}
    bool isAdjacent(int vid){
        for (int v: adjacents)
            if (v == vid)
                return true;
        return false;
    }
    void print(){
        std::cout << "Vertex (id = " << id << ", name = " << name << ")" << std::endl;
    }
} Vertex;

typedef struct TGraph {
    std::string name;
    enum graphtype {undirected = 0, directed = 1} gtype;
    int nv;
    
    std::vector< bool > visited;

    std::vector< Edge > edgeList;
    std::map<int, Vertex > vertexList; 

    TGraph(){ nv = 0; gtype = undirected; }
    TGraph(std::string n): name(n){ nv = 0; gtype = undirected; }
    TGraph(std::string n, int v): name(n), nv(v){ nv = v; gtype = undirected; visited.reserve(v); visited.resize(v); }
    ~TGraph(){}
    void setType(graphtype t){
        gtype = t;
    }
    void addVertex(int id){
        if (id >= nv) return;
        Vertex v = {id,name};
        vertexList[id] = v; 
        nv++;
    }
    void addVertex(int id, std::string name){
        if (id >= nv) return;
        Vertex v = {id,name};
        vertexList[id] = v; 
        nv++;
    }
    Vertex getVertex(std::string n){
        Vertex emptyVertex; 
        emptyVertex.id = -1; 
        for (pair< int, Vertex> p: vertexList)
            if (p.second.name == n)
                return p.second;
        return emptyVertex;
    }
    void addEdge(int src, int dest, float w = 1){
        if (src >= nv || dest >= nv) return;
        if (vertexList[src].isAdjacent(dest) == false) {
            vertexList[src].adjacents.push_back(dest);
            Edge e = {src,dest,w};
            edgeList.push_back(e);
        }
        if (gtype == undirected){
            if (vertexList[dest].isAdjacent(src) == false) {
                vertexList[dest].adjacents.push_back(src);
                Edge e = {dest,src,w};
                edgeList.push_back(e);
            }
        }
    }
    bool isConnected(int src = 0, int dest = 0){
        for (Edge e: edgeList)
            if (e.src == src && e.dest == dest)
                return true;
        return false;
    }
    float getEdgeWeight(int src = 0, int dest = 0){
        for (Edge e: edgeList)
            if (e.src == src && e.dest == dest)
                return e.weight;
        return 0;
    }
    Edge getEdge(int src = 0, int dest = 0){
        Edge emptyEdge;
        emptyEdge.id = -1; 
        for (Edge e: edgeList)
            if (e.src == src && e.dest == dest)
                return e;
        return emptyEdge;
    }
    void printVertexList(){
        for (std::pair<int, Vertex> v: vertexList)
            v.second.print();
    }
    void printEdgeList(){
        for (Edge e: edgeList)
            e.print();
    }
    void printGraph(){
        std::cout << "Adjacent list: " << std::endl;
        for (std::pair<int, Vertex> v: vertexList){
            int id = v.first;
            std::cout << id << ": {";             
            for (int a: v.second.adjacents)
                std::cout << a << ", "; 
            cout << "}" << std::endl;
        }        
    }
    void init(){
        for (int i = 0; i < nv; i++)
            visited[i] = false;
    }
    void DFS_Rec(int id){
        Vertex v = vertexList[id];        
        visited[id] = true;
        std::cout << id << ", ";        
        for (int nid: v.adjacents){
            if (visited[nid] == false){
                std::cout << "{";
                DFS_Rec(nid);
                std::cout << "}";
            }
        }        
    }
    void DFS(int id){
        init();
        std::cout << "DFS for vertex " << id << ": ";
        std::cout << "{";
        DFS_Rec(id);
        std::cout << "}";
        std::cout << std::endl;
    }
    void BFS(int id){
        init();
        queue<int> vertexQueue; 
        visited[id] = true;
        vertexQueue.push(id);
        std::cout << "BFS for vertex " << id << ": ";
        while (vertexQueue.empty() == false){
            int vid = vertexQueue.front();
            Vertex v = vertexList[vid];
            vertexQueue.pop();
            std::cout << "{";
            for (int nid: v.adjacents){
                if (visited[nid] == false){
                    visited[nid] = true;
                    vertexQueue.push(nid);
                    std::cout << nid << ", ";
                }
            }
            std::cout << "}";
        }
        std::cout << std::endl;
    }
    struct CostComparator{
    public:
        int operator() ( pair<int,float> v1, pair<int,float> v2){
            return (v1.second > v2.second);
        }
    };
    void minimalPath(int src, int dest){
        float minCost = -1;
        std::vector< int > minPath;
        std::priority_queue < pair<int,float>, std::vector< pair<int,float> >, CostComparator > queue;
        init();
        queue.push(make_pair(src,0));
        while(queue.empty() == false){
            pair<int,float> v = queue.top();
            queue.pop();

            int vid = v.first;
            visited[vid] = true;
            float minCostToV = v.second;

            if (vid == dest) { //reached the destination 
                minCost = minCostToV;
                break;
            }
            
            for (int uid: vertexList[vid].adjacents){
                if (visited[uid] == false){
                    float minCostToU = minCostToV + getEdgeWeight(vid,uid);
                    queue.push(make_pair(uid,minCostToU));
                }
            }
        }
        std::cout << "The cost of the minimal path from " << src << " to " << dest << " is " << minCost << std::endl; 
    }
    Edge getEdgeWithMinCost(){
        int minCost = 1e7;
        int src = -1, dest = -1;
        for (int v = 0; v < nv; v++){
            if (visited[v]){
                for (int u: vertexList[v].adjacents){
                    if (visited[u] == false){
                        float c = getEdgeWeight(v,u);
                        if (c < minCost){
                            minCost = c;
                            src = v;
                            dest = u;
                        }
                    }
                }
            }
        }
        return getEdge(src,dest);
    }
    void MST_Prim(int v){
        std::vector< Edge > mst;
        float mstCost = 0; //total cost of all edges in mst  
        init();

        int n = vertexList.size();

        bool allVerticesVisited = false; 
        visited[v] = true;
        while (mst.size() < (n - 1) && allVerticesVisited == false){ 
            Edge e = getEdgeWithMinCost();
            if (e.id == -1)
                allVerticesVisited = true; 
            else {
                mst.push_back(e);
                mstCost += e.weight;
                visited[e.dest] = true;
            }
        }

        std::cout << "Minimal spanning tree:" << std::endl; 
        for (Edge e: mst)
            e.print();

        /*if (mst.size() != (n - 1))
            std::cout << "Prim's algorithm failed" << std::endl; 
        else {
            std::cout << "Minimal spanning tree:\n" << std::endl; 
            for (Edge e: mst)
                e.print();
        }*/
    }
} Graph;

int main(){
    int nv = 9;
    Graph *graph = new Graph("Graph 1", nv);
    graph->setType(TGraph::undirected);
    
    for (int i = 0; i < nv; i++)
        graph->addVertex(i, "V" + to_string(i)); 
    
    int min = 1, max = 25;
    graph->addEdge(0, 1, (int)rgen::randint(min,max));
    graph->addEdge(0, 4, (int)rgen::randint(min,max));
    graph->addEdge(1, 2, (int)rgen::randint(min,max));
    graph->addEdge(1, 3, (int)rgen::randint(min,max));
    graph->addEdge(1, 4, (int)rgen::randint(min,max));
    graph->addEdge(2, 3, (int)rgen::randint(min,max));
    graph->addEdge(3, 4, (int)rgen::randint(min,max));
    graph->addEdge(3, 5, (int)rgen::randint(min,max));
    graph->addEdge(3, 7, (int)rgen::randint(min,max));
    graph->addEdge(7, 8, (int)rgen::randint(min,max));
    graph->addEdge(4, 5, (int)rgen::randint(min,max));
    graph->addEdge(5, 8, (int)rgen::randint(min,max));
    graph->addEdge(6, 2, (int)rgen::randint(min,max));

    graph->printVertexList();
    graph->printEdgeList();
    graph->printGraph();

    graph->vertexList[11].print();

    graph->DFS(1);
    graph->DFS(4);
    graph->DFS(3);

    graph->BFS(1);
    graph->BFS(0);

    graph->minimalPath(1, 8);
    graph->minimalPath(3, 8);
    graph->minimalPath(4, 8);

    graph->MST_Prim(8);
    
    delete graph;
    return 0;
}