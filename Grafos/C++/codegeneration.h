#ifndef H_CodeGeneration
#define H_CodeGeneration

#include "graph.h"

class CodeGeneration {
public:
    CodeGeneration(Graph *g);
    ~CodeGeneration(); 

    void generateODEIR(); //cria a representação intermediária das EDOs 
    void generateCAIR(); //cria a representação intermediária do autômato celular            
    void generateODEPythonCode();
    void generateGillespieCode(); 

private:    
    string replaceLocalString(string str, string pattern, string newstr);
    void replaceString(string pattern, string newstr);
    void replaceString(string pattern, vector<string> newstrvector);    
    string buildNumerator(Interaction *in); 
    string buildDenominator(Interaction *in); 
    void generateODEImports();
    void generateODEInitialization();
    void generateODEEquations();
    void generateODEPlotFile();
    void generateG_Constants();
    void generateG_Rates();
    void generateG_SumAndIfs(); 
    Graph *graph; //Reference to the graph model 
    vector<Node*> nodes; 
    vector<Interaction*> interactions; 
    vector<Edge*> edges; 

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