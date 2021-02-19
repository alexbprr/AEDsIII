#include "edge.h"

Edge::~Edge(){ }

Edge::Edge(int i, int origin, int destiny){
    id = i;
    origin_id = origin;
    destiny_id = destiny;
    status = 1;
    expr = ""; 
}

Edge::Edge(int i, int origin, int destiny, int s, string e){
    id = i;
    origin_id = origin;
    destiny_id = destiny;
    status = s; 
    expr = e; 
}

int Edge::getId(){ return id; }
int Edge::getOrigin(){ return  origin_id;}
int Edge::getDestiny(){ return destiny_id; }
void Edge::setOrigin(int id){ origin_id = id; }
void Edge::setDestiny(int id){ destiny_id = id;};

ostream& operator<<(ostream& os, const Edge& e){    
    os << "edge ("; 
    os << "id = " << e.id; 
    os << ", status = " << e.status;
    os << ", origin_id = " << e.origin_id;
    os << ", destiny_id = " << e.destiny_id;
    os << ", expr = " << e.expr;
    os << ")" << endl; 
    return os; 
}
