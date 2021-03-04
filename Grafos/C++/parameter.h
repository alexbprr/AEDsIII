#ifndef PARAMETER_H
#define PARAMETER_H 

#include <string> 

using namespace std; 

class Parameter {
public: 
    Parameter(int id, string name, float value); 
    ~Parameter(); 

private: 
    static int counter; 
    int id; 
    std::string name; 
    float value; 

}; 


#endif 