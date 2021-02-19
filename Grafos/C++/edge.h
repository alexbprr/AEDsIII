#ifndef EDGE_H
#define EDGE_H

#include "node.h"

class Edge {    
public:
    Edge(int id, int origin_id, int destiny_id);
    Edge(int id, int origin_id, int destiny_id, int status, string expr);
    ~Edge();
    int getId();
    int getOrigin();
    int getDestiny();    
    void setOrigin(int id);
    void setDestiny(int id);
    void setStatus(int s); //todo
    void setExpr(string e);//todo  

    friend ostream& operator<<(ostream& os, const Edge& e);
private:
    int id;
    int origin_id;
    int destiny_id;
    int status; //0: inactive, 1: active
    string expr; 
};

#endif // EDGE_H
