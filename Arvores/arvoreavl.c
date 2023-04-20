#include <stdio.h>
#include <stdlib.h>

typedef struct Tno {
    int ch;
    int altura;
    struct Tno* esq;
    struct Tno* dir;
} No;

typedef struct Tno* arvavl;

void preOrdem(arvavl* raiz)
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

void emOrdem(arvavl* raiz)
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

void posOrdem(arvavl* raiz)
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

arvavl* criaAvl()
{
    arvavl* raiz = (arvavl*) malloc(sizeof(arvavl));
    if (raiz != NULL)
        *raiz = NULL;
    return raiz;
}

int	alturaNo(No* no)
{
	if	(no	==	NULL)
		return	0;
	int	alt_esq	= alturaNo(no->esq);
	int	alt_dir	= alturaNo(no->dir);
	if	(alt_esq > alt_dir)
		return alt_esq + 1;
	else
		return alt_dir + 1;
}

int fbNo(No* no) //retorna o fator de balanceamento de um nó
{
    return alturaNo(no->esq) - alturaNo(no->dir);
}

int maior(int x, int y)
{
    if (x > y)
        return x;
    else
        return y;
}

void rotacaoSimplesDireita(arvavl* A) //ou rotacaoLL
{
    printf("Rotação simples à direita de %d\n", (*A)->ch);
    No* B = (*A)->esq;
    (*A)->esq = B->dir;
    B->dir = *A;
    (*A)->altura = alturaNo(*A);
    printf("Altura de %d: %d\n", (*A)->ch, (*A)->altura);
    alturaNo(B);//calcula recursivamente a altura de B
    *A = B; //o nó B é a nova raiz da subárvore
}

void rotacaoSimplesEsquerda(arvavl* A)
{
    printf("Rotação simples à esquerda de %d\n", (*A)->ch);
    No* B = (*A)->dir;
    (*A)->dir = B->esq;
    B->esq = *A;
    (*A)->altura = alturaNo(*A);
    printf("Altura de %d: %d\n", (*A)->ch, (*A)->altura);
    alturaNo(B);
    *A = B; //o nó B é a nova raiz da subárvore
}

void rotacaoDuplaDireita(arvavl* A)
{
    printf("Rotação dupla à direita de %d\n", (*A)->ch);
    rotacaoSimplesEsquerda(&((*A)->esq));
    rotacaoSimplesDireita(A);
}

void rotacaoDuplaEsquerda(arvavl* A)
{
    printf("Rotação dupla à esquerda de %d\n", (*A)->ch);
    rotacaoSimplesDireita(&((*A)->dir));
    rotacaoSimplesEsquerda(A);
}

//valor: valor a ser inserido
int insereAvl(arvavl *raiz, int valor){
    int res;
    if(*raiz == NULL)//árvore vazia ou nó folha
    {
        No *novo = (No*)malloc(sizeof(No));
        if(novo == NULL)
            return 0;
        novo->ch = valor;
        novo->altura = 0;
        novo->esq = NULL;
        novo->dir = NULL;
        *raiz = novo;
        return 1;
    }

    No *atual = *raiz;
    if(valor < atual->ch)
    {
        if((res = insereAvl(&(atual->esq), valor)) == 1)
        {
            if(fbNo(atual) == 2 && fbNo(atual->esq) == 1)
                rotacaoSimplesDireita(raiz);
            else if (fbNo(atual) == 2 && fbNo(atual->esq) == -1)
                rotacaoDuplaDireita(raiz);
        }
    }
    else
    {
        if(valor > atual->ch)
        {
            if((res = insereAvl(&(atual->dir), valor)) == 1)
            {
                if (fbNo(atual) == -2 && fbNo(atual->dir) == -1)
                    rotacaoSimplesEsquerda(raiz);
                else if (fbNo(atual) == -2 && fbNo(atual->dir) == 1)
                    rotacaoDuplaEsquerda(raiz);
            }
        }
        else
        {
            printf("Valor duplicado!!\n");
            return 0;
        }
    }
    atual->altura = maior(alturaNo(atual->esq),alturaNo(atual->dir))+1;
    return res;
}

No* procuraMenor(No* atual)
{
    No *no1 = atual, *no2 = atual->esq;
    while (no2 != NULL)
    {
        no1 = no2;
        no2 = no2->esq;
    }
    return no1;
}

int removeAvl(arvavl* raiz, int ch)
{
    if (*raiz == NULL)
        return 0;
    printf("Ativação de remove para %d\n", (*raiz)->ch);
    int res;
    if (ch < (*raiz)->ch)
    {
        if ((res = removeAvl(&(*raiz)->esq, ch)) == 1)
        {
            if (abs(fbNo(*raiz)) >= 2)
            {
                if(alturaNo((*raiz)->dir->esq) <= alturaNo((*raiz)->dir->dir))
                    rotacaoSimplesEsquerda(raiz);
                else
                    rotacaoDuplaEsquerda(raiz);
            }
        }
    }
    if (ch > (*raiz)->ch)
    {
        if((res = removeAvl(&((*raiz)->dir), ch)) == 1)
        {
            if (abs(fbNo(*raiz)) >= 2)
            {
                if(alturaNo((*raiz)->esq->dir) <= alturaNo((*raiz)->esq->esq))
                    rotacaoSimplesDireita(raiz);
                else
                    rotacaoDuplaDireita(raiz);
            }
        }
    }
    if (ch == (*raiz)->ch)
    {
        //Testa se tem um flho ou nenhum
        if((*raiz)->esq == NULL || (*raiz)->dir == NULL)
        {
            printf("Tenho 0 ou 1 filho\n");
            No* oldno = *raiz;
            if((*raiz)->esq != NULL)
                *raiz = (*raiz)->esq;
            else
                *raiz = (*raiz)->dir;
            free(oldno);
        }
        else // Tenho dois filhos
        {
            printf("Tenho dois filhos\n");
            No* temp = procuraMenor((*raiz)->dir);
            (*raiz)->ch = temp->ch;//Copia a chave e outras informações
            removeAvl(&((*raiz)->dir), (*raiz)->ch);
            /* Decide se é necessário, após a remoção, fazer uma rotação
            simples ou dupla à direita */
            if (abs(fbNo(*raiz)) >= 2)
            {
                if(alturaNo((*raiz)->esq->dir) <= alturaNo((*raiz)->esq->esq))
                    rotacaoSimplesDireita(raiz);
                else
                    rotacaoDuplaDireita(raiz);
            }
        }
        //Atualiza a altura da raiz
        if (*raiz != NULL)
            (*raiz)->altura = alturaNo(*raiz);
        return 1;//remoção realizada com sucesso
    }

    //Atualiza a altura da raiz
    (*raiz)->altura = alturaNo(*raiz);
    return res;
}

int main(){
    arvavl* avl;
    int res,i;
    int N = 9;
    int dados[9] = {1,2,3,10,4,5,9,7,8};
    avl = criaAvl();

    for(i=0; i < N; i++){
        //printf("========================\n");
        printf("Inserindo: %d\n",dados[i]);
        res = insereAvl(avl,dados[i]);
    }

    printf("\nAVL tree preOrdem:\n");
    preOrdem(avl);
    printf("\n\n");

    printf("\nAVL tree posOrdem:\n");
    posOrdem(avl);
    printf("\n\n");

    int NR = 4, dadosR[4] = {9,2,4,5};
    for(i=0;i < NR;i++){
        printf("\nRemovendo: %d\n",dadosR[i]);
        removeAvl(avl,dadosR[i]);
        preOrdem(avl);
        printf("\n\n");
    }
    return 0;
}
