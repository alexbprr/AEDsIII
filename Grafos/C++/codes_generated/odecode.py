# -*- coding: utf-8 -*-
import numpy as np
from scipy.integrate import odeint 

def odesystem(P, t, k_b_n, p0, p1, p2, p3, p4, p5): 
    B, N = P[0], P[1]

    dB_dt = -(p0*B*N)/(1 + p1*B) +(p2*B) 
    dN_dt = +(p3*B*N)/(1 + p4*B) -(p5*N) 
 
    return [dB_dt,dN_dt] 

B = 50
N = 120
k_b_n = 0.1
p0 = 0.01
p1 = 0.01
p2 = 0.01
p3 = 0.01
p4 = 0.01
p5 = 0.01
 
t=range(100)
P = [B, N]
 
model_args = (k_b_n, p0, p1, p2, p3, p4, p5)
    
results = odeint(odesystem, P, t, args=(model_args)) 

#save results 
print(str(results))

def saveTime(filename, t):
    fd = open(filename, "w")
    for i in t:
        fd.write(str(i) + "\n")        
    fd.close()

def saveData(filename, t, M, index):
    fd = open(filename, "w")
    cont = 0
    for i in t:
        fd.write(str(M[cont][index]) + "\n")
        cont = cont + 1
    fd.close()

saveTime('t.dat', t)
saveData('B.dat', t, results, 0)
saveData('N.dat', t, results, 1)
 
