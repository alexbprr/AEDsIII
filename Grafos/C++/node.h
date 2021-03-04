#ifndef NODE_H
#define NODE_H

#include <iostream> 
#include <fstream> 
#include <string>
#include <vector> 
#include <list> 
#include <tuple> 
#include "itemgraphic.h"

using namespace std;

/*enum class InteractionType{ none = 0,
           rep = 1,
           phag = 2,
           mig = 3,
           apoptosis = 4,
           n_death = 5,
           death_caused_by = 6,
           activ = 7,
           deactiv = 8,
           prod = 9,
           consume = 10,
           reprod = 11, };*/ //All interactions have a type 

//Class Node represents a biological entity of the system 
class Node{
public:    
    enum class LinkDirection { toNode = 0, fromNode = 1, none = 2};
    enum class Status {inactive = 0, active = 1};
    Node(int id); //Toda vez que um nó é criado ele recebe um id único
    Node(int id, string name, string desc, int status, double iniv);
    Node(int id, string name, string desc, int status, double iniv, ItemGraphic *g);
    ~Node();
    bool hasInteraction(); 
    void addInteraction(Node::LinkDirection d, int id);
    void removeInteraction(int id);
    int getId();
    string getName();
    int getStatus();
    float getInitialValue(); 
    ItemGraphic *getItemGraphic();    
    void setName(string n); 
    void setDesc(string d);
    void setStatus(int s);
    void setInitialValue(float v);
    void setItemGraphic(ItemGraphic* g); 
    friend ostream& operator<<(ostream& os, const Node& n);
    void generateCAIR(); //gera o xml para o nó baseado no tipo de interação 
    //void generateCACode(); //gera o código em Python considerando o estado igual a id 
private:
    int id; //indice do nó no vetor de nodes
    string name;
    string desc;
    int status;    
    float initialvalue;
    ItemGraphic* graphic; 
    vector<pair<Node::LinkDirection,int>> interactions; 
};

#endif // NODE_H
