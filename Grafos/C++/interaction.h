#ifndef INTERACTION_H
#define INTERACTION_H

#include "node.h"
#include "edge.h" 
#include "equation.h"

//Class Interaction represents an interaction between one or more biological entities 
class Interaction {
public:    

    Interaction(int id, string t = "");
    Interaction(int id, string name, string type, int status, Equation *eq, float prob = 1);  
    Interaction(int id, string name, string type, int status, int mn, vector<int> srcn, 
        int sn, vector<int> posI, vector<int> negI, int rule, Equation *eq, float prob = 1); 
    ~Interaction();
    bool hasNode(int id);
    void addNode(int edge_id, Node::LinkDirection d, Node* n);
    void removeNode(int id); 
    int getId();
    string getType();
    string getName();
    vector<Node*> getLinkedNodes();
    Equation* getEquation();
    
    void setName(string n);
    void setType(string type);
    void setStatus(int s);
    void setMainNode(int m);
    void setEquation(Equation *eq);     
    void setProbability(float p);
    void setGraphic(GuiGraphic* g); 
    friend ostream& operator<<(ostream& os, const Interaction& i);    

private:
    int id;
    string name;
    string type;
    int status;
    int mainNode; 
    vector<int> sourceNodes;
    int sinkNode; 
    vector<int> positiveInfluences; 
    vector<int> negativeInfluences; 
    int joinRule; //0: and, 1: or 
    Equation *equation;
    float probability; 
    GuiGraphic* graphic; 
    //Type type;
    //Status status;
    vector<tuple<int,Node::LinkDirection,Node*>> linkedNodes; 
};

#endif // INTERACTION_H
