#include <stdio.h>

void tempoDia(int segundo, int minuto, int hora); //prototipo

void tempoDia(int segundo, int minuto, int hora){ //declaração
        //3
    int result = (hora * 60 * 60) + (minuto * 60) + (segundo);
    printf("Ja se passaram %d segundos do dia/n", result);
}

void tempoRestante(int segundo, int minuto, int hora);

void tempoRestante(int segundo, int minuto, int hora){
    //4
    int result = (hora * 60 * 60) + (minuto * 60) + (segundo);
    int faltam = (24 * 60 * 60) - result;
    printf("Faltam %d segundos para o dia acabar", faltam);
}

int main(){
    int hora, minuto, segundo;

    printf("Informe que horas sao:\n");
    printf("Horas: ");
    scanf("%d", &hora);
    printf("Minutos: ");
    scanf("%d", &minuto);
    printf("Segundos: ");
    scanf("%d", &segundo);

    tempoDia(segundo, minuto, hora);




    


}