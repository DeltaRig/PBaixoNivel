//2. conversão de temperaturas de Fahrenheit para Celsius, segundo a fórmula conhecida:
// C = 5/9 ∗ (F − 32)

#include <stdio.h>

void tempFC(int valor);

void tempFC(int valor){
    double result = (valor - 32) * 5/9;
    printf("Em Celsius eh %.2f", result);
}

int main(){
    float valor1;

    printf("Informe um valor em Fahrenheit para  se convertido em Celsius\n");
    scanf("%f", &valor1);
    printf("Valor lido: %.2f\n", valor1);

    tempFC(valor1);
    

}