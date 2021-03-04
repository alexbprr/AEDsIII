#include <iostream>
#include <fstream>
#include <string.h> 

#include "graph.h"
#include "codegeneration.h"
using namespace std; 

int main(int argv, char *args[]){
    char vet[8] = {'A','B','c','d','e','f','g','h'};
	int k = 0;
    
    /*Graph *g = new Graph();            
	for (k = 0; k < 20; k++){
        string s(1,vet[rand()%8]);
        Node* n = g->createNodeWithValues(s,s,1,k);
        g->createInteractionWithValues("int"+s,"teste",1,""); 
        g->createEdge(4*k,4*k+1);
        g->createEdge(4*k+1,4*k); 
    }
    
    g->removeNode(0); 
    g->removeNode(4); 
    g->removeNode(8);     
    
    g->printNodes();
    g->printInteractions();
    g->printEdges();   

    g->saveGraphToXml("models/model_saved.xml");

    delete g;*/

    Graph *g2 = new Graph();
    //g2->readModelXml("models/model1.xml");  
    g2->readModelXml("models/model2.xml");  
    /*g2->removeNode(0);
    g2->removeNode(-1);
    g2->removeNode(8);
    g2->removeInteraction(2);  
    g2->removeInteraction(4);  
    g2->removeNode(1);
    g2->removeNode(5);*/
    g2->printNodes();
    g2->printInteractions();
    g2->printEdges();    

    g2->saveGraphToXml("models/model_saved.xml"); 
 
    //g2->generateODEPythonCode(); 

    CodeGeneration *codeGenerator = new CodeGeneration(g2);
    //codeGenerator->generateODEIR();    
    codeGenerator->generateODEPythonCode(); 
    codeGenerator->generateGillespieCode(); 
     
    delete g2; 

    return 0; 
}