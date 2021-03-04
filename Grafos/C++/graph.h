#ifndef GRAPH_H
#define GRAPH_H

#include <algorithm>
#include <vector>
#include <chrono>
#include <iostream> 
#include <cstring>
#include <fstream>
#include <sstream>
#include <map> 
#include "itemgraphic.h"
#include "xml/rapidxml-1.13/rapidxml.hpp"
#include "xml/rapidxml-1.13/rapidxml_print.hpp"
#include "xml/rapidxml-1.13/rapidxml_utils.hpp"
#include "node.h"
#include "interaction.h"
#include "edge.h"

using namespace std; 

typedef struct TGraphicInfo {
    float x;
    float y;
    string color; 
} graphicinfo; 

typedef struct TNodeInfo {
    string id;
    string name;
    int status;    
    double initial_value;
    graphicinfo *graphic; 
} nodeinfo;

typedef struct TLinkInfo {
    int edge_id;
    int node_id;
    string link_direction; //fromNode or toNode 
} linkinfo;

typedef struct TEquation {
    vector<pair<string,float>> parameters; 
    vector<int> node_ids; 
    string text; 
} equationinfo; 

typedef struct TInteractionInfo {
    string id;
    string name;
    string type;
    int mainNode; 
    vector<int> sourceNodes;
    int sinkNode; 
    vector<int> positiveInfluences; 
    vector<int> negativeInfluences; 
    int joinRule; 
    equationinfo *equation; 
    float p; 
    int status;    
    int num_of_links;
    int max_links; 
    linkinfo *links;
    graphicinfo *graphic; 
} interactioninfo;

typedef struct TEdgeInfo {
    string id;
    int origin_id;
    int destiny_id;
    string expr;
    int status; 
} edgeinfo;

class Graph {
public:
    Graph();
    ~Graph();
    //bool hasNodeLinked(Edge *e);
    //bool hasInteractionLinked(Edge *e);
    Node* getNode(int id);
    Node* getNode(string name);
    int getNodePos(int id);
    int getInteractionPos(int id);
    Interaction* getInteraction(int id);
    Edge* getEdge(int id);
    vector<Interaction*> getInLinks(int id);//retorna todas as arestas de entrada do nó dado
    vector<Interaction*> getOutLinks(int id);//retorna todas as arestas de saída do nó dado
    vector<Node*> getNodes();
    vector<Interaction*> getInteractions(); 
    vector<Edge*> getEdges(); 
    bool searchEdge(int origin, int dest);

    Node* createNode();
    Node* createNodeWithValues(string name, string desc, int status, double inivalue);    
    Node* createNodeWithValues(int id, string name, string desc, int status, double inivalue);
    Node* createNodeWithValues(int id, string name, string desc, int status, double inivalue, ItemGraphic *g);
    Interaction* createInteraction();
    Interaction* createInteractionWithValues(string name, string type, int status, Equation *eq);    
    Interaction* createInteractionWithValues(string name, string type, int status, Equation *eq, float p);
    Interaction* createInteractionWithValues(int id, string name, string type, int status, int mn, 
            vector<int> srcn, int sn, vector<int> posI, vector<int> negI, int rule, Equation *eq, float p = 1);
    Interaction* createInteractionWithValues(int id, string name, string type, int status, int mn, 
            vector<int> srcn, int sn, vector<int> posI, vector<int> negI, int rule, Equation *eq, float p = 1, ItemGraphic *ig = nullptr);
    Edge* createEdge(int origin_id, int destiny_id);
    Edge* createEdgeWithValues(int origin_id, int destiny_id, int status, string expr);
    void editNode(int id, string name, string desc, int status, double inivalue);
    void editInteraction(int id, string name, string type, int status, Equation *eq, float p = 1);

    void addNode(Node* n); //Resize nodes vector if necessary
    void addEdge(Edge* e);    

    void removeNode(int id); //Remove o nó de todas as interações e do grafo 
    void removeInteraction(int id); //Remove as interações de todos os nós e do grafo 

    //void removeObject(int id, int type); //remove um objeto node, interaction ou edge do grafo

    void printNodes();
    void printInteractions();
    void printEdges();
    void readModelXml(string filename); //Lê as informações do xml e cria um grafo a partir delas
    void saveGraphToXml(string filename); //salva as informações do grafo em um xml    
    void generateODEIR(); //cria a representação intermediária das EDOs 
    void generateCAIR(); //cria a representação intermediária do autômato celular
    
    //Separar na classe CodeGeneration
    string replaceLocalString(string str, string pattern, string newstr);
    void replaceString(string pattern, string newstr);
    void replaceString(string pattern, vector<string> newstrvector);    
    void generateODEPythonCode();

private:
    //Separar na classe CodeGeneration
    string buildNumerator(Interaction *in); 
    string buildDenominator(Interaction *in); 
    void generateODEImports();
    void generateODEInitialization();
    void generateODEEquations();
    void generateODEPlotFile();
    void generateG_Constants();
    void generateG_Rates();
    void generateG_SumAndIfs();    

    int nodes_size; 
    int interactions_size;
    int edges_size; 
    static int counter; //All objects (nodes,interactions and edges) receive the id from the Graph class
    vector<Node*> nodes; //vetor de nós
    vector<Interaction*> interactions; //vetor de interações (outro tipo de nó do grafo)
    vector<Edge*> edges; //vetor de arestas     

    nodeinfo* xmlnodes;
    interactioninfo* xmlinteractions;
    edgeinfo* xmledges;
    static ofstream logfile; 
    static ofstream outfile; 
    int N0, F_edge; 

    //Attributes to code generation 
    int T; //simulation time 
    //int dt; //time increment 
    float defaultValue = 0.01; 
    map<int,vector<string>> nodeEquations; //(node id, equacoes)
    vector<pair<string,float>> vars;
    vector<pair<string,float>> parameters;     
    vector<string> equationNames; 
    vector<string> varNames; 
    vector<string> paramNames; 
    stringstream outputStream;     
    string odetemplate_filename;
    string odeplot_filename; 
    string odeoutput_filename;    
    std::ifstream inputFile; 
    std::ofstream outputFile; 
};

#endif
