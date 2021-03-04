#ifndef ItemGraphic_H
#define ItemGraphic_H

#include <tuple> 
#include <string> 
using namespace std; 

class ItemGraphic {
public: 
    ItemGraphic(float x, float y, string color); 
    ~ItemGraphic();   
    float getX();
    float getY();
    string getColor(); 
    void setX(float x);  
    void setY(float y);
    void setColor(string c);

private: 
    float x, y;  
    //tuple<int,int,int> color;
    string color; 
}; 

#endif 