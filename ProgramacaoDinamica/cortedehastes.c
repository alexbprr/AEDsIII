#include <stdio.h>
#include <stdlib.h>

#define max(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })

#define N 10

int Corte(int *p, int *r, int n)
{
    int q, aux;
    q = 0;
    for (int i=1; i <= n; i++)
    {
        if (r[n-i] > 0)
            q = max(q, p[i] + r[n-i]);
        else
            q = max(q, p[i] + Corte(p, r, n-i));
    }
    r[n] = q;
    return q;
}

int Corte2(int *p, int *r, int n)
{
    int q, aux;
    if (r[n] > 0)
        return r[n];
    q = 0;
    for (int i=1; i <= n; i++)
        q = max(q, p[i] + Corte2(p, r, n-i));
    r[n] = q;
    return q;
}

int main()
{
    int *p = (int*) malloc((N+1)*sizeof(int));
    int *r = (int*) malloc((N+1)*sizeof(int));

    p[0] = 0;
    p[1] = 1;
    p[2] = 5;
    p[3] = 8;
    p[4] = 9;
    p[5] = 10;
    p[6] = 17;
    p[7] = 17;
    p[8] = 20;
    p[9] = 24;
    p[10] = 30;
    r[0] = 0;

    int i;
    for (i=1; i < N+1; i++)
        r[i] = -1;

    Corte(p, r, N);
    printf("Resultados Corte\n");
    for (i=1; i < N+1; i++)
        printf("r[%d] = %d\n", i, r[i]);

    p[0] = 0;
    p[1] = 1;
    p[2] = 5;
    p[3] = 8;
    p[4] = 9;
    p[5] = 10;
    p[6] = 17;
    p[7] = 17;
    p[8] = 20;
    p[9] = 24;
    p[10] = 30;
    r[0] = 0;

    Corte2(p, r, N);
    printf("Resultados Corte2\n");
    for (i=1; i < N+1; i++)
        printf("r[%d] = %d\n", i, r[i]);


    free(p);
    free(r);
    return 0;
}
