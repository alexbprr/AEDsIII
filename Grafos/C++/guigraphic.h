#ifndef Graphic_H
#define Graphic_H

#include <tuple> 
#include <string> 
using namespace std; 

class GuiGraphic {
public: 
    GuiGraphic(string x, string y, string color); 
    ~GuiGraphic();     

private: 
    float x, y;  
    //tuple<int,int,int> color;
    string color; 
}; 

#endif 