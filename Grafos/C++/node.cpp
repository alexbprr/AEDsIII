#include "node.h"

Node::Node(int i){
    id = i;
    graphic = nullptr; 
}

Node::Node(int i, string n, string d, int s, double iniv){
    id = i;
    name = n;
    desc = d;
    status = s;
    initialvalue = iniv;
    graphic = nullptr; 
}

Node::~Node(){}

void Node::addInteraction(Node::LinkDirection d, int id){
    this->interactions.push_back(make_pair(d,id));
}

int Node::getId(){ return id; }
string Node::getName(){ return name; }
float Node::getInitialValue(){ return initialvalue; }
void Node::setName(string n){ name = n; }
void Node::setDesc(string d){ desc = d; }
void Node::setStatus(int s){ status = s; }
void Node::setInitialValue(float v){ initialvalue = v; }
void Node::setGraphic(GuiGraphic* g) { graphic = g; }

ostream& operator<<(ostream& out, const Node& n){
    out << "node (";
    out << "id = " << n.id;
    out << ", name = " << n.name;
    out << ", desc = " << n.desc;
    out << ", status = " << n.status;
    out << ", initial value = " << n.initialvalue;
    out << ")" << endl;   
    return out; 
}

void Node::removeInteraction(int id){
    int j= 0;        
    for (pair<Node::LinkDirection,int> p: interactions){
        if (get<1>(p) == id){
            interactions.erase(interactions.begin()+j);
            break; 
        }
        j++; 
    }    
}