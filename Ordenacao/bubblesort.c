#include <stdio.h>

void swap(int *xp, int *yp) {
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}
// A function to implement bubble sort

void bubbleSort(int arr[], int n) {
    int i, j;
    int cont = 0;
    int troca = 0; 
    for (i = 0; i < n-1; i++) {
    // Last i elements are already in place
        for (j = 0; j < n-i-1; j++) {
            cont++;
            if ( arr[j] > arr[j+1]) {
                swap(&arr[j], &arr[j+1]);
                troca = 1; 
            }
        }
        if (!troca)
            break; 
    }    
}

int main(){

    int V[7] = {7,6,5,4,3,2,1};
    bubbleSort(V,7);
    //for (i = 0; i < 7; i++) 

    
    return 0; 
}