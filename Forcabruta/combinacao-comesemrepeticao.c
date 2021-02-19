#include <stdio.h>
#include <stdlib.h>

void combinacao_simples(int n, int r, int x[], int next, int k){
    int i;
    if (k == r){
        for (i = 0; i < r; i++)
            printf("%d ", x[i] + 1);
        printf("\n");
    }
    else{
        for (i = next; i < n; i++){
            x[k] = i;
            combinacao_simples(n, r, x, i + 1, k + 1);
        }
    }
}

void combinacao_comrepeticao(int n, int r, int x[], int next, int k)
{
    int i;
    if (k == r)
    {
        for (i = 0; i < r; i++)
            printf("%d ", x[i] + 1);
        printf("\n");
    }
    else
    {
        for (i = 0; i < n; i++)
        {
            x[k] = i;
            combinacao_comrepeticao(n, r, x, i + 1, k + 1);
        }
    }
}

int main()
{
    int n, r, x[1000];
    printf("Entre com o valor de n: ");
    scanf("%d", &n);
    printf("Entre com o valor de r: ");
    scanf("%d", &r);    
    combinacao_simples(n, r, x, 0, 0); 
    return 0;
}
