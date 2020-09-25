#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main() {
    int tam;
    scanf("%d", &tam);
    
    int nums[tam];
    for(int i = 0; i < tam; i++){
        scanf("%d", &nums[i]);
    }
    
    int inver[tam]; 
    for(int i = 0; i < tam; i++){
        inver[tam] = nums[i];
        tam--;
    }
    
    
    return 0;
}
