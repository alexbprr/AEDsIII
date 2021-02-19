#ifndef EQUATION_H
#define EQUATION_H

#include <iostream>
#include <fstream> 
#include <vector>
#include <string>  
#include <tuple> 
using namespace std; 

class Equation {
public:   
    Equation();
    Equation(vector<pair<string,float>> p, vector<int> ids, string t); 
    ~Equation();     
    vector<pair<string,float>> getParameters();
    string getText();
    friend ostream& operator<<(ostream& os, const Equation& i);

private: 
    //Os valores iniciais dos parâmetros serão armazenados em outro arquivo?
    //string name; 
    vector<pair<string,float>> parameters; 
    vector<int> node_ids; //variables of the equation 
    string text; 
}; 

#endif 
