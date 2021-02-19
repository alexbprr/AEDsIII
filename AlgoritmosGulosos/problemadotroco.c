#include <stdio.h>
#include <stdlib.h>

void Troco(int troco, int moedas[])
{
    int soma = 0, cont = 0, num_moedas = 0;
    while (soma < troco)
    {
        if (soma + moedas[cont] <= troco)
        {
            soma = soma + moedas[cont];
            num_moedas++;
        }
        else
            cont++;
    }
    if (soma == troco)
        printf("O número mínimo de moedas é: %d\n",num_moedas);
}

void Troco2(int valor, int i, int moedas[], int num_moedas)
{
    if (valor == 0)
    {
        printf("O número mínimo de moedas é: %d\n",num_moedas);
        exit(0);
    }
    else if (valor >= moedas[i])
    {
        valor = valor - moedas[i];
        num_moedas++;
        Troco2(valor, i, moedas, num_moedas);
    }
    else
        Troco2(valor, i+1, moedas, num_moedas);
}

int main()
{ 
    int moedas[6] = {100,50,25,10,5,1};
    int troco;
    printf("Digite o valor do troco\n");
    scanf("%d", &troco);
    Troco(troco, moedas);
    Troco2(troco, 0, moedas, 0);

    return 0;
}
