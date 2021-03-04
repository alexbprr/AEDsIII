#include "equation.h" 

Equation::Equation(){ }

Equation::Equation(vector<pair<string,float>> p, vector<int> ids, string t){
    parameters = p; 
    nodeIds = ids; 
    text = t; 
}

Equation::~Equation(){ }

vector<pair<string,float>> Equation::getParameters(){ return parameters; }
string Equation::getText(){return text; }
void Equation::setParameters(vector<pair<string,float>> p){ parameters = p; } 
void Equation::setVars(vector<int> ids){ nodeIds = ids; }
void Equation::setText(string t){ text = t; }
void Equation::addParameter(pair<string,float> p){parameters.push_back(p);}
void Equation::addVar(int id){ nodeIds.push_back(id); }

ostream& operator<<(ostream& out, const Equation& e){       
    out << "{Vars: [";     
    for (int id: e.nodeIds){
        out << " " << id << ",";
    }
    out << "],";
    string name; 
    float value; 
    out << "Parameters:["; 
    for (pair<string,float> p: e.parameters){
        name = get<0>(p); 
        value = get<1>(p); 
        out << "(name = " << name;
        out << ", value = " << value << ")";
    }    
    out << "],"; 
    out << "Equation text:" << e.text << "}"; 
    return out; 
}