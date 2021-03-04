#include "interaction.h"
#include "itemgraphic.h"

Interaction::Interaction(int i, string t){
    id = i;
    type = t;
    status = 1;
    mainNode = -1; 
    sinkNode = -1; 
    joinRule = 0; 
    probability = 1;
    equation = nullptr; 
} 

Interaction::Interaction(int i, string n, string t, int s, Equation *eq, float p){
    id = i;
    name = n;
    type = t;
    status = s;
    mainNode = -1; 
    sinkNode = -1; 
    joinRule = 0; //and 
    equation = eq;
    probability = p;
    graphic = nullptr; 
}

Interaction::Interaction(int i, string n, string t, int s, int mn, vector<int> srcn, 
        int sn, vector<int> posI, vector<int> negI, int rule, Equation *eq, float p, ItemGraphic *ig){
    id = i;
    name = n;
    type = t;
    status = s;
    mainNode = mn; 
    sourceNodes = srcn; 
    sinkNode = sn; 
    positiveInfluences = posI;
    negativeInfluences = negI; 
    joinRule = rule; 
    equation = eq;
    probability = p;
    graphic = ig; 
}

Interaction::~Interaction(){
    delete equation; 
    delete graphic; 
}

bool Interaction::hasNode(int id){
    for (tuple<int,Node::LinkDirection,Node*> t: linkedNodes){
        Node* n = get<2>(t); 
        if (n != nullptr && n->getId() == id)
            return true; 
    }
    return false; 
}

void Interaction::addNode(int edge_id, Node::LinkDirection d, Node *n){
    this->linkedNodes.push_back(make_tuple(edge_id,d,n));
}

void Interaction::removeNode(int id){    
    //for (std::vector<tuple<int,Node::LinkDirection,Node*>>::iterator it=linkedNodes.begin(); 
            //it!=linkedNodes.end(); ++it) {        
    for (int j = 0; j < linkedNodes.size(); j++){
        tuple<int,Node::LinkDirection,Node*> t = linkedNodes.at(j);
        Node* n = get<2>(t); 
        if (n != nullptr && n->getId() == id){                    
            //it = linkedNodes.erase(it);
            linkedNodes.erase(linkedNodes.begin()+j);
            get<0>(t) = -1;
            get<2>(t) = nullptr; 
            break; 
        }
    }
}

int Interaction::getId(){return id;}
string Interaction::getName(){return name;}
string Interaction::getType(){return type;}
int Interaction::getStatus(){ return status; }
ItemGraphic *Interaction::getItemGraphic(){ return graphic; }
Node::LinkDirection Interaction::getLinkDirection(int nodeid){ 
    for (tuple<int,Node::LinkDirection,Node*> t: linkedNodes){
        Node* n = get<2>(t); 
        if (n != nullptr && n->getId() == nodeid)
            return get<1>(t); 
    }
    return Node::LinkDirection::none; 
}

vector<Node*> Interaction::getLinkedNodes(){
    vector<Node*> nodes; //definir tamanho inicial? 
    for (tuple<int,Node::LinkDirection,Node*> t: linkedNodes){        
        Node* n = get<2>(t); 
        if (n != nullptr)
            nodes.push_back(n); 
    }
    return nodes; 
}
int Interaction::getMainNode(){ return mainNode; }
vector<int> Interaction::getSources() { return sourceNodes; }
int Interaction::getSink(){ return sinkNode; }
vector<int> Interaction::getPositiveInfluences(){ return positiveInfluences; }
vector<int> Interaction::getNegativeInfluences(){ return negativeInfluences; } 
int Interaction::getJoinRule(){ return joinRule; }
Equation* Interaction::getEquation(){ return equation; }

void Interaction::setName(string n) { name = n; }
void Interaction::setType(string t){ type = t; }
void Interaction::setStatus(int s){ status = s; }
void Interaction::setEquation(Equation *eq) { equation = eq; }
void Interaction::setProbability(float p){ probability = p; }
void Interaction::setItemGraphic(ItemGraphic* g) { graphic = g; }

ostream& operator<<(ostream& out, const Interaction& i){
    out << "interaction (";
    out << "id = " << i.id;
    out << ", name = " << i.name;
    out << ", type = " << i.type;
    out << ", status = " << i.status;
    out << ", equation info: " << (*i.equation) << endl;
    out << ", linked nodes:{ "; 
    for (tuple<int,Node::LinkDirection,Node*> t: i.linkedNodes){
        out << "Edge id: " << get<0>(t); 
        if (get<1>(t) == Node::LinkDirection::fromNode)
            out << ", Link direction: fromNode"; 
        else 
            out << ", Link direction: toNode"; 
        Node* n = get<2>(t);            
        if (n != nullptr) 
            out << ", Node id: " << n->getId();
    }
    out << "}";   
    out << ", pos = (" << i.graphic->getX() << "," << i.graphic->getY() << ")";
    out << ", color = " << i.graphic->getColor(); 
    out << ")" << endl; 
    return out; 
}
