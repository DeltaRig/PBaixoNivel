#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main() {
    int valor, tam;
    int result = -1;
    scanf("%d %d", &valor, &tam);
    
    int nums[tam];
    for(int i = 0; i < tam; i++){
        scanf("%d", &nums[i]);
        if(nums[i] == valor){
            result i;
        }
    }
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */ 
    
    return result;
}

int achaValor(int valor, int tam, int vetor[]){
    for(int i = 0; i < tam; i++){
        if(vetor[i] == valor){
            return i;
        }   
    }
    return -1;
}
