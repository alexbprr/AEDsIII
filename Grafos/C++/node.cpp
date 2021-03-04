#include "node.h"
#include "itemgraphic.h"

Node::Node(int i){
    id = i;
    status = 1; 
    initialvalue = 0; 
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

Node::Node(int i, string n, string d, int s, double iniv, ItemGraphic *g){
    id = i;
    name = n;
    desc = d;
    status = s;
    initialvalue = iniv;
    graphic = g; 
}

Node::~Node(){
    delete graphic; 
}

bool Node::hasInteraction(){
    if (this->interactions.size() > 0)
        return true; 
    else 
        return false; 
}

void Node::addInteraction(Node::LinkDirection d, int id){
    this->interactions.push_back(make_pair(d,id));
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

int Node::getId(){ return id; }
string Node::getName(){ return name; }
int Node::getStatus(){ return status; }
float Node::getInitialValue(){ return initialvalue; }
ItemGraphic *Node::getItemGraphic(){ return graphic; }
void Node::setName(string n){ name = n; }
void Node::setDesc(string d){ desc = d; }
void Node::setStatus(int s){ status = s; }
void Node::setInitialValue(float v){ initialvalue = v; }
void Node::setItemGraphic(ItemGraphic* g) { graphic = g; }

ostream& operator<<(ostream& out, const Node& n){
    out << "node (";
    out << "id = " << n.id;
    out << ", name = " << n.name;
    out << ", desc = " << n.desc;
    out << ", status = " << n.status;
    out << ", initial value = " << n.initialvalue;
    out << ", pos = (" << n.graphic->getX() << "," << n.graphic->getY() << ")";
    out << ", color = " << n.graphic->getColor(); 
    out << ")" << endl;   
    return out; 
}