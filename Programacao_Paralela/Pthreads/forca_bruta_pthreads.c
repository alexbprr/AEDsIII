#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>
#include <sys/types.h>

typedef struct{
    int inicio;
    int fim;
    int tamM;
    int num_thread;
    int soma;
}parametros, *Parametros;

char *P, *T;

void* forcaBruta(void *argumentos){
    Parametros args = (Parametros)argumentos;
    printf("Posição de inicio (Thread %d): %d\n", args->num_thread, args->inicio);
    printf("Posição de fim (Thread %d): %d\n", args->num_thread, args->fim);
    int i, j, k, cont = 0;
    for(i= args->inicio; i < args->fim; i++){
        k = i;
        j = 0;
        while (T[k] == P[j] && j < args->tamM){
            k++;
            j++;
        }
        if(j == args->tamM){
            cont++;
            printf("Padrão encontrado na posição %d, thread %d\n", i, args->num_thread);	        
        }
    }
    printf("Thread %d, %d ocorrencias\n", args->num_thread,cont);
    args->soma = cont;
    return NULL;
}

int main(int argc, char **argv){
    int i, n, m, num_threads = atoi(argv[1]);
    if (argc == 1){
        printf("Passe o numero de threads como argumento.\n");
        exit(1);
    }

    int ocorrencias = 0;
    struct timeval tv1, tv2;
    double t1, t2;

    struct timespec start, finish;
    double elapsed;

    FILE* texto = fopen("texto_de_entrada.txt", "r");

    fseek(texto, 0, SEEK_END);                // { descobre
    n = ftell(texto);                // o tamanho
    fseek(texto, 0, SEEK_SET);     // do arquivo }

    printf("tamanho do arquivo %d\n",n);

    T = (char*) malloc(n*sizeof(char));
    fread(T,sizeof(char),n,texto);
    fclose(texto);

    printf("Digite o tamanho do padrão:");
    scanf("%d",&m);
    P = (char*) malloc(m*sizeof(char));
    printf("Digite o padrão buscado: ");
    scanf("%s",P);
    printf("\n");

    gettimeofday(&tv1, NULL);
    t1 = (double)(tv1.tv_sec) + (double)(tv1.tv_usec)/ 1000000.00;

    clock_gettime(CLOCK_MONOTONIC, &start);

    pthread_t threads[num_threads];
    parametros args[num_threads];
    int tamanho = n/num_threads; //Quantidade de caracteres cada thread vai processar 
    printf("Tamanho do \"pedaço\" de cada thread: %d\n", tamanho);
    for(i = 0; i < num_threads; i++){
        args[i].inicio = tamanho*i;
        if (i == (num_threads-1)) 
            args[i].fim = n - m;
        else 
            args[i].fim = args[i].inicio + tamanho + m; //o fim "avança" m caracteres sobre o intervalo da próxima thread
        args[i].tamM = m;
        args[i].num_thread = i;
        args[i].soma = 0;
        pthread_create(&(threads[i]), NULL, forcaBruta, &(args[i])); //cria uma thread para executar o força bruta em um pedaço do texto 
    }

    for(i=0;i<num_threads;i++){
        pthread_join(threads[i], NULL); //finaliza as threads filhas 
    }

    for(i=0;i<num_threads;i++)
        ocorrencias = ocorrencias + args[i].soma;

    gettimeofday(&tv2, NULL);
    t2 = (double)(tv2.tv_sec) + (double)(tv2.tv_usec)/ 1000000.00;
    clock_gettime(CLOCK_MONOTONIC, &finish);

    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;

    printf("Tivemos %d ocorrencias da palavra %s\n",ocorrencias,P);
    //printf("Tempo de execução em milisegundos: %lf\n",(double)(t2-t1)*1000 );
    printf("Tempo de execução em segundos: %lf\n",elapsed );
}
