#include "equation.h" 

Equation::Equation(){ }

Equation::Equation(vector<pair<string,float>> p, vector<int> ids, string t){
    parameters = p; 
    node_ids = ids; 
    text = t; 
}

Equation::~Equation(){ }

vector<pair<string,float>> Equation::getParameters(){ return parameters; }
string Equation::getText(){return text; }

ostream& operator<<(ostream& out, const Equation& e){       
    out << "\nVars:\n";     
    for (int id: e.node_ids){                
        out << " " << id << endl;
    }
    string name; 
    float value; 
    out << "Parameters:\n"; 
    for (pair<string,float> p: e.parameters){
        name = get<0>(p); 
        value = get<1>(p); 
        out << "param (name = " << name;
        out << ", value = " << name << ")\n";
    }    
    out << "Equation text = " << e.text << endl; 
    return out; 
}