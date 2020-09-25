#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main() {

    /* Enter your code here. Read input from STDIN. Print output to STDOUT */  
    int tam;
    scanf("%d", &tam);
    
    int nums[tam];
    for(int i = 0; i < tam; i++){
        scanf("%d", &nums[i]);
    }
    
    int copia[tam];
    int temp;
    for(int i = 0; i < tam; i++){
        temp = nums[i];
        copia[i] = temp;
        printf("%d ", &copia[i]);
    }
}
