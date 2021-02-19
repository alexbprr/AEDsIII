#include <stdio.h>
#include <stdlib.h>

#define max(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })

void forcaBruta(int *a, int *I, int *J, int *soma_max, int n)
{
    int soma, primeiro, ultimo;
    for (primeiro = 0; primeiro < n; primeiro++)
    {
        soma = 0;
        for (ultimo = primeiro; ultimo < n; ultimo++)
        {
            soma = soma + a[ultimo];
            if (soma > *soma_max)
            {
                *soma_max = soma;
                *I = primeiro;
                *J = ultimo;
            }
        }
    }
}

int divisaoEConquista(int *a, int left, int right, int *soma_max)
{
    if (left == right){
        if (a[left] > 0)
            *soma_max = a[left];
        else
            *soma_max = 0;
        return *soma_max;
    }
    else
    {
        int meio = (left + right)/2;
        int soma_max_bordEsq = 0, soma = 0, k;
        for (k = meio; k >= left; k--)
        {
            soma = soma + a[k];
            if (soma > soma_max_bordEsq)
                soma_max_bordEsq = soma;
        }
        int soma_max_bordDir = 0;
        soma = 0; 
        for (k = meio + 1; k <= right; k++)
        {
            soma = soma + a[k];
            if (soma > soma_max_bordDir)
                soma_max_bordDir = soma;
        }

        *soma_max = max(divisaoEConquista(a, left, meio, soma_max), divisaoEConquista(a, meio+1, right, soma_max));
        *soma_max = max(*soma_max, soma_max_bordEsq+soma_max_bordDir);
        return *soma_max;
    }
}

void guloso(int *a, int *I, int *J, int* soma_max, int n)
{
    int primeiro = 0, ultimo, soma = *soma_max = *I = *J = 0;
    for (ultimo = 0; ultimo < n; ultimo++)
    {
        soma = soma + a[ultimo];
        if(soma > *soma_max)
        {
            *soma_max = soma;
            *I = primeiro;
            *J = ultimo;
        }
        else if (soma < 0)
        {
            primeiro = ultimo + 1;
            soma = 0;
        }
    }
}

int main()
{
    //int a[6] = {-2, 6, -14, 2, -5, 7};
    //int a[7] = {-2, 11, -4, 13, -5, -2, 0};
    int a[7] = {3, -6, 2, -10, 4, -2, 5};
    int I = 0, J = 0, soma_max = 0, n = sizeof(a)/sizeof(a[0]);
    forcaBruta(a, &I, &J, &soma_max, n);
    printf("Força bruta: \n");
    printf("  Soma maxima: %d\n", soma_max);
    printf("\t I: %d", I);
    printf("\t J: %d\n", J);

    int left = 0, right = 6;
    soma_max = 0;
    divisaoEConquista(a, left, right, &soma_max);
    printf("Divisão e Conquista\n");
    printf("  Soma maxima: %d\n", soma_max);

    soma_max = 0;
    I = 0, J = 0;
    guloso(a, &I, &J, &soma_max, n);
    printf("Guloso: \n");
    printf("  Soma maxima: %d\n", soma_max);
    printf("\t I: %d", I);
    printf("\t J: %d\n", J);


    return 0;
}
