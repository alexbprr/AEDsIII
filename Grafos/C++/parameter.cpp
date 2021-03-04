#include "parameter.h"

int Parameter::counter = 0;  

Parameter::Parameter(int i, string n, float v){
    id = i; 
    name = n; 
    value = v; 
}
    
Parameter::~Parameter(){ 
    
}

