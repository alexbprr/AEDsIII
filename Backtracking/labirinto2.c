#include<stdio.h>
#define MAX 10
void imprimeLabirinto(int M[MAX][MAX], int n, int m) {
int i, j;
for (i = 0; i <
for (j = 0; j
if (M[i][j]
if (M[i][j]
if (M[i][j]
}
printf("\n");
}
n; i++) {
< m; j++) {
== -2) printf(" XX");
== -1) printf("
");
>= 0) printf(" %02d", M[i][j]);
}

void obtemLabirinto(int M[MAX][MAX], int *n, int *m,
int *Li, int *Ci, int *Lf, int *Cf) {
int i, j, d;
scanf("%d %d", n, m);
/* dimensoes do labirinto */
scanf("%d %d", Li, Ci); /* coordenadas da posicao inicial */
scanf("%d %d", Lf, Cf); /* coordeandas da posicao final (saida) */
/* labirinto: 1
0
for (i = 0; i <
for (j = 0; j
scanf("%d",
if (d == 1)
M[i][j] =
else
M[i][j] =
}
= parede ou obstaculo
= posicao livre */
*n; i++)
< *m; j++) {
&d);
-2;
-1;
}

int labirinto(int M[MAX][MAX], int deltaL[], int deltaC[],
int Li, int Ci, int Lf, int Cf) {
int L, C, k, passos;
if ((Li == Lf) && (Ci == Cf)) return M[Li][Ci];
/* testa
for (k =
L = Li
C = Ci
todos os movimentos a partir da posicao atual */
0; k < 4; k++) {
+ deltaL[k];
+ deltaC[k];
/* verifica se o movimento eh valido e gera uma solucao factivel */
if (M[L][C] == -1) {
M[L][C] = M[Li][Ci] + 1;
passos = labirinto(M, deltaL, deltaC, L, C, Lf, Cf);
if (passos > 0) return passos;
}
}
return 0;
}


/* Versao Branch and Bound: 
void labirinto(int M[MAX][MAX], int deltaL[], int deltaC[],
int Li, int Ci, int Lf, int Cf, int *min) {
int L, C, k;
if ((Li == Lf) && (Ci == Cf)) {
if (M[Lf][Cf] < *min)
*min = M[Li][Ci];
} else {

for (k = 0; k < 4; k++) {
L = Li + deltaL[k];
C = Ci + deltaC[k];

if ((M[L][C] == -1) || (M[L][C] > M[Li][Ci] + 1)) {
M[L][C] = M[Li][Ci] + 1;
if (M[L][C] + abs(L - Lf) + abs(C - Cf) < *min)
labirinto(M, deltaL, deltaC, L, C, Lf, Cf, min);
}
}
}
}

*/