#include <stdio.h>

#define N 5

void BuscaSequencial(int ch, int tab[N]){
    int i = 0, achou = 0, pos = -1;
        do {
          if (tab[i] == ch)
              achou = 1;
        i++;     //duas instruções: atribuição e soma
    } while (!achou && i < N); //duas instruções: operador de negação e
                               //                     operador <
    if (achou)
          pos = i - 1;
    printf("%d\n", pos);
}

int main(){
    int vetor[5] = {1,3,4,8,6}; 
    BuscaSequencial(6, vetor); 
}