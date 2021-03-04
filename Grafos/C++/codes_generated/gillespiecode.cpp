#include <iostream> 
#include <fstream> 
#include <array>
#include <random>
#include <string> 
#include <cmath> // log
#include <algorithm> // accumulate, fill
using namespace std; 
std::random_device rd; // collects a seed from a random device
std::mt19937 mersenne_engine {rd()}; // Mersenne Twister
std::uniform_real_distribution<double> distribution (0.0,1.0);

double k_b_n = 0.1,
p0 = 0.01,
p1 = 0.01,
p2 = 0.01,
p3 = 0.01,
p4 = 0.01,
p5 = 0.01;
 

double gillespie($varNames) {    
    $rates
    
    double st,x,tau;	
    $sum 
	x = distribution(mersenne_engine);
	tau = -std::log(distribution(mersenne_engine))/st;

    $ifs      

    return tau; 
}

void advanceTime($varNames, double dt){
    double time = 0.0;
    while(time < dt){
        time += gillespie($varNames);
    }
}

int main(){
    $initialization    
    $fileOpening 

    double dt = $dt; 
    const int time_size = (int)($T/dt)+1;
    for(int i=1; i < time_size; i++){
		#pragma omp parallel 
		{
			#pragma omp for 
			for(int j=0; j< n_runs; j++) {
                advanceTime($varNames, dt);
                $saveFiles  
            }
        }
    }

    $fileClosing 
    $finish 
}