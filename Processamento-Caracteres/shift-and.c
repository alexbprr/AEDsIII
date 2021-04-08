#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Maxchar 5

int comparacoes = 0;

int ShiftAndExato(char* T, int *n, char* P, int *m, int linha)
{
    //printf("%s %s %d %d\n", T, P, *m, *n);
    long Masc[Maxchar];
    long i;
    long R = 0;
    for (i=0; i < Maxchar; i++)
        Masc[i] = 0;
    for(i=1; i <= *m; i++){
        Masc[ P[i-1] + 127] = Masc[ P[i-1] + 127] | 1 << (*m - i);
    }
    for(i =0; i < *n; i++)
    {
        comparacoes++;
        R = ((((unsigned long)R) >> 1) | (1 << (*m - 1))) & Masc[T[i] + 127];
        if((R & 1) != 0)
            return i - *m + 1;
    }
    return -1;
}

int main()
{
    char t[50] = "Hello world!";
    int n = sizeof(t)/sizeof(char);
    char p[3] = "llo";
    int m = sizeof(p)/sizeof(char);
    int pos = ShiftAndExato(t,&n,p,&m,0);
    if(pos != -1)
        printf("Padrão encontrado na posição %d\n", pos);

    //char *pattern = (char*)malloc(3*sizeof(char));
    //pattern = strcpy(pattern,"wor");
    char p1[3] = "wor";
    m = sizeof(p1)/sizeof(char);
    pos = ShiftAndExato(t,&n,p1,&m,0);
    if(pos != -1)
        printf("Padrão encontrado na posição %d\n", pos);

    return 0;
}
