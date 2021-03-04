# -*- coding: utf-8 -*-
import matplotlib.pyplot as plt
import matplotlib.colors as colors
import matplotlib.cm as cmx
import numpy as np

def getMatrixFromFile(filename, u):
    file = open(filename, 'r')
    if (file):
        temp = [content.split(' ') for content in [content.rstrip() for content in file.readlines()]]
        cont = 0
        for j in temp:
            u[cont] = [float(i) for i in j]
            cont+=1
        return u
    else:
        print('Error: it was not possible to open the file!')
        exit

def getArrayFromFile(filename):
    a = []
    file = open(filename, 'r')
    if (file):        
        a = file.readlines()
        a = [content.strip() for content in a]
        a = [float(i) for i in a]
        return a
    else: 
        print('Error: it was not possible to open the file!')
        exit

def createFigure(title, t, maxDensity):
    fig = plt.figure(figsize=(10,7))    
    plt.tick_params(labelsize=18)
    plt.title(title, fontsize=19)
    plt.xlabel('time',fontsize=18)
    plt.ylabel('concentration',fontsize=18)
    ax = fig.gca()
    return [fig,ax]

def saveFig(fig, filename):
    fig.savefig(filename + '.svg', format='svg', bbox_inches='tight')
    
def initializeGraphParameters():
    global scalarMap
    cm = plt.get_cmap('jet')
    cNorm  = colors.Normalize(vmin=0, vmax=100)
    scalarMap = cmx.ScalarMappable(norm=cNorm, cmap=cm)

def getMaxValue(mat):
    maxvalue = 0
    for i in range(0,T):
        for j in mat[i]:
            if(j > maxvalue):
                maxvalue = j
    return maxvalue

initializeGraphParameters()
color_index = 0
colorVal = scalarMap.to_rgba(color_index)

t = getArrayFromFile("t.dat")
B = getArrayFromFile("B.dat")
[fig,ax] = createFigure('B', t, max(B))
ax.plot(t,B,label="B", color=colorVal)
color_index += 8
colorVal = scalarMap.to_rgba(color_index)
ax.legend(loc='upper right', fontsize=15)
ax.grid()
saveFig(fig,'B')

N = getArrayFromFile("N.dat")
[fig,ax] = createFigure('N', t, max(N))
ax.plot(t,N,label="N", color=colorVal)
color_index += 8
colorVal = scalarMap.to_rgba(color_index)
ax.legend(loc='upper right', fontsize=15)
ax.grid()
saveFig(fig,'N')


