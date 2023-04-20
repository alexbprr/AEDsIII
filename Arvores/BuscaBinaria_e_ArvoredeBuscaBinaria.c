#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct TElemento {
    int ch; //chave
    char* str;
    float f1;
    struct TElemento* esq;
    struct TElemento* dir;
} elemento, No;

typedef No* arvbin;

int particiona_struct(elemento* vetor, int inicio, int fim)
{
    int esq, dir;
    elemento pivo, aux;
    esq = inicio;
    dir = fim;
    pivo = vetor[inicio];
    while(esq < dir)
    {
            while(vetor[esq].ch <= pivo.ch && esq < fim)
                    esq++;

            while(pivo.ch < vetor[dir].ch)
                    dir--;

            if(dir < inicio || esq > fim) printf("\nERRO\n\n");
            if(esq < dir)
            {
                    aux = vetor[esq]; // troca vetor[esq] com vetor[dir]
                    vetor[esq] = vetor[dir];
                    vetor[dir] = aux;
            }
    }
    vetor[inicio] = vetor[dir];
    vetor[dir] = pivo;
    printf("Vetor ordenado entre %d e %d\n", inicio, fim);
    for (int i=inicio; i < fim; i++)
         printf("%d ", vetor[i].ch);
    printf("\n");
    //retorna dir, que é o índice que vai dividir o vetor
    return dir;
}

void quick_struct(elemento *vetor, int inicio, int fim, int *cont)
{
    (*cont)++;
    int pivo;
    if(inicio < fim)
    {
        pivo = particiona_struct(vetor,inicio,fim); // encontra um pivo que "divide" o vetor em dois
        quick_struct(vetor, inicio, pivo-1, cont); // realiza a partição para a parte da esquerda
        quick_struct(vetor, pivo+1, fim, cont); // e realiza a partição para a parte de direita
    }
}

int buscaBinaria(elemento* V, int N, int ch)
{
    int inicio = 0, fim = N-1, meio, cont = 0;
    while(inicio <= fim)
    {
        meio = (inicio+fim)/2;
        printf("inicio: %d, meio: %d e fim: %d\n", inicio, meio, fim);
        if (ch == V[meio].ch)
            return meio;
        else if (ch > V[meio].ch) //Se a chave é maior, procura na metade direita
            inicio = meio + 1;
        else //A chave é menor, procura na metade esquerda
            fim = meio - 1;
        cont++;
    }
    return -1;
}

arvbin* criaArvbin(){
    arvbin* raiz = (arvbin*) malloc(sizeof(arvbin));
    if(raiz != NULL)
        *raiz = NULL;
    return raiz;
}

void liberaNo(No* n)
{
    if(n == NULL)
        return;
    liberaNo(n->esq);
    liberaNo(n->dir);
    free(n);
    n = NULL;
}

void liberaArvore(arvbin* raiz)
{
    if(raiz == NULL)
        return;
    liberaNo(*raiz);//libera cada nó
    free(raiz);//libera a raiz
}

int alturaNo(No* no)
{
    if (no == NULL)
        return 0;
    int alt_esq = alturaNo(no->esq);
    int alt_dir = alturaNo(no->dir);
    if (alt_esq > alt_dir)
        return alt_esq + 1;
    else
        return alt_dir + 1;
}

void preOrdem(arvbin* raiz)
{
    if (raiz == NULL)
        return;
    if (*raiz != NULL)
    {
        printf("%d\n", (*raiz)->ch);
        preOrdem(&((*raiz)->esq));
        preOrdem(&((*raiz)->dir));
    }
}

void emOrdem(arvbin* raiz)
{
    if (raiz == NULL)
        return;
    if (*raiz != NULL)
    {
        emOrdem(&((*raiz)->esq));
        printf("%d\n", (*raiz)->ch);
        emOrdem(&((*raiz)->dir));
    }
}

void posOrdem(arvbin* raiz)
{
    if (raiz == NULL)
        return;
    if (*raiz != NULL)
    {
        posOrdem(&((*raiz)->esq));
        posOrdem(&((*raiz)->dir));
        printf("%d\n", (*raiz)->ch);
    }
}

No* insereArvbin(arvbin* raiz, int valor)
{
    if (raiz == NULL)
        return NULL;
    No* novo = (No*) malloc(sizeof(No));
    if (novo == NULL)
        return NULL;
    novo->ch = valor;
    printf("end do novo no: %p; chave: %d\n", novo, novo->ch);
    novo->dir = NULL;
    novo->esq = NULL;

    if (*raiz == NULL)
        *raiz = novo;
    else
    {
        No* atual = *raiz;
        No* ant = NULL;
        while (atual != NULL)
        {
            ant = atual;
            if (valor == atual->ch)
            {
                free(novo);
                return 0; //o elemento já existe
            }
            if (valor > atual->ch)
                atual = atual->dir;
            else
                atual = atual->esq;
        }
        if (valor > ant->ch)
            ant->dir = novo;
        else
            ant->esq = novo;
    }
    return novo;
}

void insereArvbinRecursiva(arvbin* raiz, int ch)
{
    if (raiz == NULL)
        return;
    if (*raiz == NULL)//O novo nó sempre é inserido como um nó folha
    {
        *raiz = (No*) malloc(sizeof(No));
        printf("End do novo no(%d): %p\n", ch, *raiz);
        (*raiz)->ch = ch;
        (*raiz)->dir = NULL;
        (*raiz)->esq = NULL;
    }
    else
    {
        //Continuo a procurar aonde inserir
        No* atual = *raiz;
        if (ch == atual->ch)
            return; //o elemento já existe
        if (ch > atual->ch)
            insereArvbinRecursiva(&(atual->dir),ch);
        else
            insereArvbinRecursiva(&(atual->esq),ch);
    }
}


No* removeAtual(No* atual) {
    No *no1, *no2;
    if(atual->esq == NULL)
    {
        /*Não tenho filho da esquerda, então retorno o filho da direita do nó
        que será removido*/
        no2 = atual->dir;
        free(atual);
        return no2;
    }
    printf("end do no a ser removido: %p\n", atual);
    no1 = atual;
    no2 = atual->esq;
    while(no2->dir != NULL){
        printf("end no1: %p\n", no1);
        printf("end no2: %p\n", no2);
        no1 = no2;
        no2 = no2->dir;
    }
    if(no1 != atual){
        no1->dir = no2->esq;
        no2->esq = atual->esq;
    }
    no2->dir = atual->dir;

    free(atual); //Libera o nó removido
    return no2;
}

int removeArvbin(arvbin *raiz, int ch)
{
    if(raiz == NULL)
        return 0;
    No* ant = NULL;
    No* atual = *raiz;
    printf("end raiz: %p\n", *raiz);
    while(atual != NULL){

        if(atual->ch == ch){ // Chaves iguais
            if(atual == *raiz)
                *raiz = removeAtual(atual); // Se a raiz for o item a ser removido
            else{
                if (ant->dir == atual)
                    ant->dir = removeAtual(atual);
                else
                    ant->esq = removeAtual(atual);
            }
            return 1;
        }
        //Continua procurando a chave
        ant = atual;
        if(ch > atual->ch)
            atual = atual->dir; // Visita o filho da direita
        else
            atual = atual->esq; // Visita o filho da esquerda
    }
    return 0;
}

void removeArvbinRecursiva(arvbin *raiz, int ch)
{
    No* aux;
    if(raiz == NULL || *raiz == NULL) //Árvore não existe ou a chave não foi encontrada
        printf("Erro\n");
    if (ch > (*raiz)->ch)
        removeArvbinRecursiva(&((*raiz)->dir),ch); // Visita o filho da direita
    else if (ch < (*raiz)->ch)
        removeArvbinRecursiva(&((*raiz)->esq),ch); // Visita o filho da esquerda
    else if ((*raiz)->dir == NULL) //A chave foi encontrada, testa qual filho é NULL
    {
        /*Se o nó não tem filho da direita, faz ele receber o filho da esquerda
        e depois libera a memória*/
        aux = (*raiz);
        (*raiz) = (*raiz)->esq;
        free(aux);
    }
    else if ((*raiz)->esq == NULL)
    {
        /*Se o nó não tem filho da esquerda, faz ele receber o filho da direita
        e depois libera a memória*/
        aux = (*raiz);
        (*raiz) = (*raiz)->dir;
        free(aux);
    }
    else
    {
        /* Tenho dois filhos, procura o subtituto do nó que será removido e
        reorganiza a árvore fazendo o ponteiro para o nó que será removido (*raiz)
        apontar para o nó substituto escolhido. */
        No* atual = *raiz; //Guarda o nó a ser removido em uma variável auxiliar
        No* no1 = *raiz; //Nó pai do nó substituto escolhido
        (*raiz) = (*raiz)->esq;
        while ((*raiz)->dir != NULL){
            no1 = (*raiz);
            (*raiz) = (*raiz)->dir;
        }
        if(no1 != (*raiz)){
            no1->dir = (*raiz)->esq;
            (*raiz)->esq = atual->esq;
        }
        (*raiz)->dir = atual->dir;
        free(atual);
    }
}

int consultaArvbin(arvbin *raiz, int ch)
{
    if (raiz == NULL || *raiz == NULL)
        return 0;
    No* atual = *raiz;
    char caminho[20];
    int i = 0;
    while (atual != NULL)
    {
        printf("end no visitado: %p; ch: %d \n", atual, atual->ch);
        if (ch == atual->ch)
        {
            caminho[i] = '\0';
            printf("caminho: %s\n", caminho);
            return 1;
        }
        else if (ch > atual->ch)
        {
            atual = atual->dir;// Visita o filho da direita
            caminho[i++] = 'R';
        }
        else
        {
            atual = atual->esq;// Visita o filho da esquerda
            caminho[i++] = 'L';
        }
    }
    return 0;
}

int consultaArvbinRecursiva(arvbin *raiz, int ch)
{
    if (raiz == NULL || *raiz == NULL)
        return 0;
    printf("Visitando nó %d\n", (*raiz)->ch);
    No* atual = *raiz;
    if (ch == atual->ch)
        return 1;
    else if (ch > atual->ch)
        return consultaArvbinRecursiva(&(atual->dir),ch);// Visita o filho da direita
    else
        return consultaArvbinRecursiva(&(atual->esq),ch);// Visita o filho da esquerda
}

int isArvoreDeBuscaBin(arvbin *raiz, int r)
{
    if (raiz == NULL || *raiz == NULL)
        return r;
    No* atual = *raiz;
    if (atual->dir != NULL && atual->ch > atual->dir->ch)
        r = 0;
    if (atual->esq != NULL && atual->ch < atual->esq->ch)
        r = 0;
    r = isArvoreDeBuscaBin(&(atual->esq), r);
    if (r)
        return isArvoreDeBuscaBin(&(atual->dir), r);
    return 1;
}

int noPaieAvo(No* no, arvbin* raiz)
{
    No* avo = *raiz;
    No* pai = *raiz;
    No* atual = *raiz;
    int i = 0;
    while(no->ch != atual->ch && atual != NULL)
    {
        if (i >= 3)
            avo = pai;
        pai = atual;
        if (no->ch > atual->ch)
        {
            atual = atual->dir;
            i++;
        }
        else
        {
            atual = atual->esq;
            i++;
        }
    }
    if (atual == NULL)
        return 0;
    if (atual == *raiz)
        printf("Não tenho pai, sou a raiz\n");
    else
        printf("Meu pai é %d\n", pai->ch);
    if (atual == *raiz || atual == (*raiz)->esq || atual == (*raiz)->dir)
        printf("Eu não tenho nó avô.\n");
    else
        printf("Meu avo é %d\n", avo->ch);
    return 1;
}

int noIrmao(No* no, arvbin* raiz)
{
    No* pai = *raiz;
    No* atual = *raiz;
    int esq_ou_dir = -1;
    while(no->ch != atual->ch && atual != NULL)
    {
        pai = atual;
        if (no->ch > atual->ch)
        {
            atual = atual->dir;
            esq_ou_dir = 1; //Fui para direita
        }
        else
        {
            atual = atual->esq;
            esq_ou_dir = 0; //Fui para esquerda
        }
    }
    if (atual == NULL)
        return 0;
    if (esq_ou_dir == -1)
    {
        printf("Não tenho irmão. \n");
        return 1;
    }
    if (esq_ou_dir == 0)
        if (pai->dir != NULL)
            printf("Tenho um irmao e sua chave é %d\n", pai->dir->ch);
        else
            printf("Não tenho irmão.\n");
    if (esq_ou_dir == 1)
        if (pai->esq != NULL)
            printf("Tenho um irmao e sua chave é %d\n", pai->esq->ch);
        else
            printf("Não tenho irmão.\n");
    return 1;
}

int questao4d(No* no)
{
    No* atual = no, *aux;
    if (atual->dir == NULL)
        return 0;
    else
    {
        //Vou para o filho da direita
        atual = atual->dir;
        //Começo a procurar pela menor chave andando sempre para esquerda
        while(atual != NULL)
        {
            aux = atual;
            atual = atual->esq;
        }
        printf("A menor chave dos descendentes com chave maior é %d"
         "\n", aux->ch);
    }
}

/*int min(arvbin* raiz)
{
    if (*raiz == NULL)
	return 0;
    No* menor = *raiz;
    min(&((*raiz)->esq));
    return menor->ch;
}*/

int min(arvbin* raiz)
{
    No* p = *raiz;
    while(p->esq != NULL)
    	p = p->esq;
    printf("Menor %d\n",p->ch);
}

int maior(arvbin* raiz)
{
    No* p = *raiz;
    while(p->dir != NULL)
    	p = p->dir;
    printf("Maior %d\n",p->ch);
}


int main(int argc, char* argv[])
{
    if (argc > 1)
    {
        // int SIZE = atoi(argv[1]), K = 10, numAtivacoes = 0, escolha = 1, ch;
        // char letras[10] = {'a','b','c','d','e','f','g','h','i','j'};
        // elemento* vetor = (elemento*)malloc(SIZE*sizeof(elemento));
        // srand(time(NULL));
        // for (int i=0; i < SIZE; i++)
        // {
        //     vetor[i].ch = abs(rand()%(10*SIZE));
        //     vetor[i].f1 = (float)rand()/RAND_MAX;
        //     vetor[i].str = (char*)malloc(K*sizeof(char));
        //     for (int j=0; j < K; j++)
        //     {
        //         vetor[i].str[j] = letras[rand()%K];
        //     }
        // }
        //
        // quick_struct(vetor,0,SIZE-1,&numAtivacoes);
        //
        // printf("Vetor ordenado:\n");
        // for (int i=0; i < SIZE; i++)
        //         printf("%d \n", vetor[i].ch);
        // printf("\n");
        //
        // while(escolha)
        // {
        //     printf("Digite o valor da chave buscada:\n");
        //     scanf("%d", &ch);
        //     int pos = buscaBinaria(vetor,SIZE,ch);
        //     if (pos != -1)
        //         printf("O elemento foi encontrado na posição %d.\n", pos);
        //     else
        //         printf("O elemento não foi encontrado.\n");
        //
        //     printf("Digite 1 para realizar uma nova pesquisa sequencial ou 0 para encerrar essa etapa: ");
        // 	scanf("%d",&escolha);
        // 	printf("\n");
        // }
        // //Libera memória
        // for (int i=0; i < SIZE; i++)
        //     free(vetor[i].str);
        // free(vetor);
    }
    else
        printf("Digite na linha de argumento o tamanho do vetor.\n");

    printf("Iniciando a árvore de busca binária\n");
    arvbin* arvore = criaArvbin();
    insereArvbin(arvore,50);
    insereArvbin(arvore,10);
    insereArvbin(arvore,5);
    insereArvbin(arvore,30);
    insereArvbin(arvore,25);
    insereArvbin(arvore,45);
    insereArvbin(arvore,99);
    insereArvbin(arvore,80);
    insereArvbin(arvore,85);
    insereArvbin(arvore,102);
    printf("Impressao em pre-ordem\n");
    preOrdem(arvore);
    printf("\n");
    printf("Impressao em pos-ordem\n");
    posOrdem(arvore);
    printf("\n");
    if (isArvoreDeBuscaBin(arvore,0))
        printf("É uma árvore de busca binária\n");
    //Pior caso árvore de busca binária
    /*insereArvbin(arvore,1);
    insereArvbin(arvore,2);
    insereArvbin(arvore,3);
    insereArvbin(arvore,10);
    insereArvbin(arvore,4);
    insereArvbin(arvore,5);
    insereArvbin(arvore,9);
    insereArvbin(arvore,7);
    insereArvbin(arvore,6);
    printf("Altura da arvore %d\n", alturaNo(*arvore));
    consultaArvbin(arvore,6);*/

    // No* no50 = insereArvbin(arvore,50);
    // insereArvbin(arvore,99);
    // No* no10 = insereArvbin(arvore,10);
    // insereArvbin(arvore,5);
    // No* no30 = insereArvbin(arvore,30);
    // No* no25 = insereArvbin(arvore,25);
    // // insereArvbin(arvore,24);
    // // insereArvbin(arvore,23);
    // // insereArvbin(arvore,22);
    // // insereArvbin(arvore,21);
    // No* no45 = insereArvbin(arvore,45);
    // No* no40 = insereArvbin(arvore,40);
    // noPaieAvo(no40,arvore);
    // noPaieAvo(no45,arvore);
    // // // insereArvbinRecursiva(arvore,50);
    // // insereArvbinRecursiva(arvore,99);
    // // insereArvbinRecursiva(arvore,10);
    // // insereArvbinRecursiva(arvore,5);
    // // insereArvbinRecursiva(arvore,30);
    // // insereArvbinRecursiva(arvore,25);
    // // insereArvbinRecursiva(arvore,45);
    // // //insereArvbinRecursiva(arvore,40);
    // printf("Imprimindo em pré-ordem.\n");
    // preOrdem(arvore);
    // printf("Imprimindo em em-ordem.\n");
    // emOrdem(arvore);
    // printf("Imprimindo em pós-ordem.\n");
    // posOrdem(arvore);
    // // printf("Altura da arvore %d\n", alturaNo(*arvore));
    // printf("Altura do no %d: %d\n", no25->ch, alturaNo(no25));
    // printf("Altura do no %d: %d\n", no30->ch, alturaNo(no30));
    // noIrmao(no25,arvore);
    // questao4d(no10);
    //removeArvbinRecursiva(arvore,50);
    //removeArvbinRecursiva(arvore,45);
    //removeArvbinRecursiva(arvore,45);
    consultaArvbinRecursiva(arvore,55);
    if (consultaArvbin(arvore,30))
        printf("Valor encontrado\n");
    else
        printf("Valor não encontrado\n");
    if (consultaArvbin(arvore,25))
        printf("Valor encontrado\n");
    else
        printf("Valor não encontrado\n");
    min(arvore);
    maior(arvore);
    liberaArvore(arvore);
    return 0;
}
