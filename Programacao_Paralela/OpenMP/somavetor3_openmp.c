#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

#define VETSIZE 20

int main(int argc, char **argv)
{
    int nums[VETSIZE];
    int thread_count = strtol(argv[1],NULL,10);
    int sum = 0, i;
    for(i=0; i< VETSIZE; i++)
        nums[i] = i;
    ///Toda variável declarada fora da seção parallel é por padrão shared
    #pragma omp parallel for num_threads(thread_count) reduction(+:sum) 
    for(i=0; i< VETSIZE; i++)
    {
        sum += nums[i];
    }

    ///O mestre imprime a soma final
    printf("A soma dos elementos do vetor eh %d\n", sum);
}
