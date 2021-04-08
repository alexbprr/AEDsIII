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
//schedule(type[,chunk])
//schedule(static,4)
    #pragma omp parallel for num_threads(thread_count) shared(sum) schedule(static,1)
    for(i=0; i< VETSIZE; i++)
    {
        printf("Meu id é %d e meu i é %d\n", omp_get_thread_num(), i);
        fflush(stdout);
        #pragma omp critical
            sum += nums[i];
    }

    ///O mestre imprime a soma final
    printf("A soma dos elementos do vetor eh %d\n", sum);
}
