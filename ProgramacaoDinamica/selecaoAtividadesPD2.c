#include <stdlib.h>
#include <stdio.h>

//max{c[i,k]+ c[k,j] + 1}

typedef struct TAtividade {
    int c;  
    int id; 
    int quant; 
} atividades; 

void imprimeAtividades(atividades **a, int i, int j){
    int k;
    if (a[i][j].c > 0){
        k = a[i][j].id;
        printf(" %d ", k); 
        imprimeAtividades(a,i,k);
        imprimeAtividades(a,k,j);
    }
}

int selecaoAtividadesPD(atividades **a, int s[], int f[], int i, int j){
    if (j - i < 2)
        return 0;
    for(int k=i+1; k < j; k++){
        a[i][k].c = selecaoAtividadesPD(a,s,f,i,k);
        a[k][j].c = selecaoAtividadesPD(a,s,f,k,j);
        if (f[i] <= s[k] && f[k] <= s[j] && a[i][k].c + a[k][j].c + 1 > a[i][j].c) {
            a[i][j].c = a[i][k].c + a[k][j].c + 1;                
            a[i][j].id = k;              
        }
    }
    return a[i][j].c; 
}

int main(){
    int s[] =  {0, 1, 3, 0, 4, 3, 5, 6, 8, 8, 2, 12, 100};
    int f[] =  {0, 4, 5, 6, 6, 8, 9, 10, 11, 12, 13, 14, 200};
    //int s[] =  {0, 1, 3, 0, 4, 3, 100};
    //int f[] =  {0, 5, 5, 6, 7, 8, 200};
    int n = sizeof(s)/sizeof(s[0]);
    printf("%d\n", n);
    atividades **ativ = (atividades**)malloc((n)*sizeof(atividades*));
    for (int i =0; i < n; i++) {
        ativ[i] = (atividades*)malloc((n)*sizeof(atividades));            
    }
    
    for (int i =0; i < n; i++)
        for (int j =0; j < n; j++) {
            ativ[i][j].c = 0;
            ativ[i][j].quant = 0;
        }

    int maxAct = selecaoAtividadesPD(ativ, s, f, 0, n-1);
    printf("Máximo de atividades compatíveis: %d\n", maxAct);
    printf("Atividades selecionadas:\n");    
    imprimeAtividades(ativ,0,n-1);

    printf("\nc:\n");
    for (int i=0; i < n; i++) {
        for (int j=i+2; j < n; j++)
            printf("c[%d,%d] = %d; ", i, j, ativ[i][j].c);
        printf("\n");
    }

    for (int i =0; i < n; i++) {         
        free(ativ[i]);
    }
    free(ativ);    
    return 0;
}
