#include <stdio.h>
#include <stdlib.h>

int movePos(int L[8][8], int V[8][8], int x, int y, int cont)
{
    printf("Estou tentando ir para %d,%d\n",x,y);
    int sucesso;
    if(x == 7 && y == 7)
    {
        printf("Encontrei a saída!");
        printf("Realizei %d movimentos.\n", cont);
        exit(0);
    }
    if(x >= 0 && x <= 7 && y >= 0 && y <= 7)
        if(L[x][y] == 0 && V[x][y] == 0)
        {
            printf("Movi para a posiçao %d,%d\n",x,y);
            movePos(L,V,x,y+1, cont+1); ///Para direita
            V[x][y] = 1;
            movePos(L, V, x+1, y, cont+1); ///Para baixo
            movePos(L, V, x, y-1, cont+1); ///Para esquerda
            movePos(L, V, x-1, y, cont+1); ///Para cima
        }
        else return 0;
}


int main()
{
    int L[8][8], V[8][8];

    for(int i=0;i<8;i++)
        for(int j=0; j<8;j++)
            V[i][j] = 0;

    L[0][0] = 0;
    L[0][1] = 0;
    L[0][2] = 1;
    L[0][3] = 0;
    L[0][4] = 0;
    L[0][5] = 0;
    L[0][6] = 0;
    L[0][7] = 0;
    L[1][0] = 1;
    L[1][1] = 0;
    L[1][2] = 0;
    L[1][3] = 0;
    L[1][4] = 0;
    L[1][5] = 0;
    L[1][6] = 0;
    L[1][7] = 0;
    L[2][0] = 0;
    L[2][1] = 0;
    L[2][2] = 1;
    L[2][3] = 0;
    L[2][4] = 1;
    L[2][5] = 0;
    L[2][6] = 1;
    L[2][7] = 0;
    L[3][0] = 0;
    L[3][1] = 0;
    L[3][2] = 0;
    L[3][3] = 0;
    L[3][4] = 0;
    L[3][5] = 0;
    L[3][6] = 1;
    L[3][7] = 0;
    L[4][0] = 0;
    L[4][1] = 1;
    L[4][2] = 0;
    L[4][3] = 0;
    L[4][4] = 1;
    L[4][5] = 1;
    L[4][6] = 1;
    L[4][7] = 0;
    L[5][0] = 0;
    L[5][1] = 0;
    L[5][2] = 0;
    L[5][3] = 0;
    L[5][4] = 0;
    L[5][5] = 0;
    L[5][6] = 0;
    L[5][7] = 1;
    L[6][0] = 0;
    L[6][1] = 0;
    L[6][2] = 1;
    L[6][3] = 0;
    L[6][4] = 0;
    L[6][5] = 1;
    L[6][6] = 0;
    L[6][7] = 0;
    L[7][0] = 0;
    L[7][1] = 0;
    L[7][2] = 0;
    L[7][3] = 0;
    L[7][4] = 0;
    L[7][5] = 1;
    L[7][6] = 0;
    L[7][7] = 0;
    int x=0,y=0;
    movePos(L,V,x,y,0);

    return 0;
}
