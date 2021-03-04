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
    void setParameters(vector<pair<string,float>> p); 
    void setVars(vector<int> ids);
    void setText(string t); 
    void addParameter(pair<string,float> p);
    void addVar(int id); 
    friend ostream& operator<<(ostream& os, const Equation& i);

private: 
    //Os valores iniciais dos parâmetros serão armazenados em outro arquivo?
    //string name; 
    vector<pair<string,float>> parameters; 
    vector<int> nodeIds; //variables of the equation 
    string text; 
}; 

#endif 
