/**
 * Desenvolvedores: Daniela Rigoli (18110549) (128) e Lucas Salbego (17202261) (138)
 * Programação de Baixo Nível
 * Professor: Marcelo Cohen e Alezandre Agustini
*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>		// Para usar strings

// SOIL é a biblioteca para leitura das imagens
#include "SOIL.h"

// Um pixel RGB
typedef struct {
    unsigned char r, g, b;
} RGB;

// Uma imagem em RGB
typedef struct {
    int width, height;
    RGB* img;
} Img;

//int heightM = 8, widthM = 4; //global

// Protótipos
void load(char* name, Img* pic);

// Carrega uma imagem para a struct Img
void load(char* name, Img* pic)
{
    int chan;
    pic->img = (unsigned char*) SOIL_load_image(name, &pic->width, &pic->height, &chan, SOIL_LOAD_RGB);
    if(!pic->img)
    {
        printf( "SOIL loading error: '%s'\n", SOIL_last_result() );
        exit(1);
    }
    printf("Load: %d x %d x %d\n", pic->width, pic->height, chan);
}

void bloco(Img* pic, char* caracteres);

void bloco(Img* pic, char* caracteres)
{
    int heightM = 8, widthM = 4;
    int soma = 0;
    
    int w = pic->width;
    int h = pic->height;

    int parametro = 255/8;
    //char caracteres[tamanho];
    
    for(int blocosDescidos = 0; blocosDescidos < h/heightM; blocosDescidos++){ //inicia coluna
        for (int blocoDeLinha = 0; blocoDeLinha < w/widthM; blocoDeLinha++) //inicia linha
        {
            
            for (int j = 0; j < heightM; j++) //inicia um bloco
            {
                for (int x = 0; x < widthM; x++)
                {
                    soma += pic->img[(w * (j + (blocosDescidos * heightM))) + x + (widthM * blocoDeLinha)].r;
                }
            } //termina um bloco

            int media = soma / (heightM * widthM);
            soma = 0;
            //printf("%d - ",media);

            //processo de conversão
            if(media < parametro){
                strcat(caracteres, ".");
            } else if(media < parametro * 2){
                strcat(caracteres, ":");
            } else if(media < parametro * 3){
                strcat(caracteres, "c");
            } else if(media < parametro * 4){
                strcat(caracteres, "o");
            } else if(media < parametro * 5){
                strcat(caracteres, "C");
            } else if(media < parametro * 6){
                strcat(caracteres, "O");
            } else if(media < parametro * 7){
                strcat(caracteres, "8");
            } else {
                strcat(caracteres, "@");
            }
        } //termina linha
        // <br>
        strcat(caracteres, "<br>");
        

    } //termina coluna
}

int main(int argc, char** argv)
{
    Img pic;
    if(argc < 1) {
        printf("loader [img]\n");
        exit(1);
    }
    load(argv[1], &pic);
    
    int heightM = 8, widthM = 4;

    //PASSAR P&B
    unsigned char* data [pic.width*pic.height];
    unsigned char tom;
    for(int blocoDeLinha=0; blocoDeLinha<(pic.width)*(pic.height); blocoDeLinha++) {
        tom = (pic.img[blocoDeLinha].r * 0.3 + pic.img[blocoDeLinha].g * 0.59 + pic.img[blocoDeLinha].b * 0.11); //calculo do valor de cinza
        pic.img[blocoDeLinha].r = tom;
        pic.img[blocoDeLinha].g = tom;  //torna a imagem P&B
        pic.img[blocoDeLinha].b = tom;

        data[blocoDeLinha] = &pic.img[blocoDeLinha]; //prepara o vetor de dados para output
        
    }

    //REDUCAO
    
    /*
    
    Img reduzido;
    reduzido.height = pic.height * (porcentagem/100);
    reduzido.width = pic.width * (porcentagem/100);

    long tamanho = reduzido.width * reduzido.height; //floor

    reduzido.img [tamanho];
    //redutor(&pic, porcentagem, &reduzido);
     
    int objetivo = porcentagem;
    long contador = 0;
    for (int i = 0; i < tamanho; i++)
    {
        for(int j = porcentagem; j<100; j += porcentagem)
        {
            //printf("Posicao: %d\n", contador);
            contador++;
        }
        reduzido.img[i] = pic.img[contador];
        contador++;
    }
    /*for (int i = 0; i < (reduzido.width)*(reduzido.height); i++)
    {
        reduzido.img[i] = pic.img[i];
    }*/

    
    /*double porcentagem = atoi(argv[2]);

    int atual = 1;
    int incremento = 2;
    for (int k = 0; k < (pic.width * pic.height)/incremento; k++)
    {
        pic.img[k] = pic.img[atual];
        atual += incremento;

    }*/

    //recebe imagem P&B e converte para ASCII Art
    int tamanhoDeBlocos = ((pic.height)/ heightM)*((pic.width)/widthM) + ((pic.width) * widthM); //*4 por causa da quantidade de caracteres de <br>
    char caracteres[tamanhoDeBlocos];
    bloco(&pic, caracteres);
    //printf("%s", caracteres);
    
    
    for (int i = 0; i < ((pic.height)/5)*((pic.width)/4) ; i++)
    {
        if(caracteres[i] == '<'){
            printf("\n");
           i = i + 3;
        } else {
            printf("%c", caracteres[i]);
        }
    } 


    //Passar para o HTML
    FILE* arq = fopen("saida.html", "w"); //criar o arquivo: w
    if(arq == NULL){
        printf("Erro abrindo arquivo de saída\n");
        exit(1);
    }
    //"Courier New", "Monaco", "monospace";
    fprintf(arq, "<html>\n");
    fprintf(arq, "<head>\n");
    fprintf(arq, "</head>\n");
    fprintf(arq, "<body style='font-size:0.5rem;font-family:monospace, MS Mincho, Lucida Console;background-color:black;color:white'>\n");
    fprintf(arq, "<h1>%s</h1>\n", caracteres);
    fprintf(arq, "</body>\n");
    fprintf(arq, "</html>\n");
    
    fclose(arq);

    SOIL_save_image("british_gray.bmp",SOIL_SAVE_TYPE_BMP,pic.width, pic.height,3,*data);

    //SOIL_save_image("british_reduzida.bmp",SOIL_SAVE_TYPE_BMP, 300, 300,3,*reduzido);
    //printf("Primeiros 10 pixels da imagem:\n");
    free(pic.img);
}



