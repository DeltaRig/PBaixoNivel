#include "quadtree.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>     /* OpenGL functions */
#endif

unsigned int first = 1;
char desenhaBorda = 1;

QuadNode* newNode(int x, int y, int width, int height)
{
    QuadNode* n = malloc(sizeof(QuadNode));
    n->x = x;
    n->y = y;
    n->width = width;
    n->height = height;
    n->NW = n->NE = n->SW = n->SE = NULL;
    n->color[0] = n->color[1] = n->color[2] = 0;
    n->id = first++;
    return n;
}

void mediaDetalhe(Img* pic, QuadNode* n, float* result){
    RGB (*pixels)[pic->width] = (RGB(*)[pic->width]) pic->img;
    float somaR = 0, somaG = 0, somaB = 0;
    float distR = 0, distG = 0, distB = 0;

    for(int i = n->x; i < n->width; i++){
        for(int j = n->y; j < n->height; j++){
            somaR += pixels[i][j].r;
            somaG += pixels[i][j].g;
            somaB += pixels[i][j].b;
        }
    }
    //calcula as médias
    result[0] = somaR / (n->width * n->height); 
    result[1] = somaG / (n->width * n->height);
    result[2] = somaB / (n->width * n->height);

    for(int i = n->x; i < n->width; i++){
        for(int j = n->y; j < n->height; j++){
            distR += (pixels[i][j].r - result[0]) * (pixels[i][j].r - result[0]);
            distG += (pixels[i][j].g - result[1]) * (pixels[i][j].g - result[1]);
            distB += (pixels[i][j].b - result[2]) * (pixels[i][j].b - result[2]);
        }
    }

    result[3] = sqrt(distR + distG + distB);
    printf("\nO resultado do nivel de detalhamento foi: %f\n", result[3]);

}

void quadTreeRec(QuadNode* n, float minDetail, Img* pic);
void quadTreeRec(QuadNode* n, float minDetail, Img* pic){
    
    if(n->status == PARCIAL){
        float result[4];
        printf("\nMeus quatro quadNodes:");
        QuadNode* nw = newNode(0,0,n->width/2,n->height/2);
        mediaDetalhe(pic, nw, result);
        if(result[3] <= minDetail){
            nw->status = CHEIO;
        } else {
            nw->status = PARCIAL;
        }
        nw->color[0] = result[0]; // R
        nw->color[1] = result[1]; // G
        nw->color[2] = result[2]; // B

        // Aponta do pai para o nodo nw
        n->NW = nw;
        
        QuadNode* se = newNode(n->width/2,n->width/2,n->width/2,n->height/2);
        mediaDetalhe(pic, se, result);
        if(result[3] <= minDetail){
            se->status = CHEIO;
        } else {
            se->status = PARCIAL;
        }
        se->color[0] = result[0]; // R
        se->color[1] = result[1]; // G
        se->color[2] = result[2]; // B

        // Aponta do pai para o nodo nw
        n->SE = se;

        QuadNode* sw = newNode(0,n->width/2,n->width/2,n->height/2);
        mediaDetalhe(pic, sw, result);
        if(result[3] <= minDetail){
            sw->status = CHEIO;
        } else {
            sw->status = PARCIAL;
        }
        sw->color[0] = result[0]; // R
        sw->color[1] = result[1]; // G
        sw->color[2] = result[2]; // B

        // Aponta do pai para o nodo nw
        n->SW = sw;

        QuadNode* ne = newNode(n->width/2,0,n->width/2,n->height/2);
         mediaDetalhe(pic, ne, result);
        if(result[3] <= minDetail){
            ne->status = CHEIO;
        } else {
            ne->status = PARCIAL;
        }
        ne->color[0] = result[0]; // R
        ne->color[1] = result[1]; // G
        ne->color[2] = result[2]; // B

        // Aponta do pai para o nodo nw
        n->NE = ne;

        quadTreeRec(nw, minDetail, pic);
        quadTreeRec(se, minDetail, pic);
        quadTreeRec(sw, minDetail, pic);
        quadTreeRec(ne, minDetail, pic);
    }

}

QuadNode* geraQuadtree(Img* pic, float minDetail)
{
    // Converte o vetor RGB para uma MATRIZ que pode acessada por pixels[linha][coluna]
    RGB (*pixels)[pic->width] = (RGB(*)[pic->width]) pic->img;

    // Veja como acessar os primeiros 10 pixels da imagem, por exemplo:
    int i;
    for(i=0; i<10; i++)
        printf("%02X %02X %02X\n",pixels[0][i].r,pixels[1][i].g,pixels[2][i].b);

    int width = pic->width;
    int height = pic->height;

    //////////////////////////////////////////////////////////////////////////
    // Implemente aqui o algoritmo que gera a quadtree, retornando o nodo raiz
    //////////////////////////////////////////////////////////////////////////

    float result[4];

    QuadNode* raiz = newNode(0, 0, width, height);
    mediaDetalhe(pic, raiz, result);
    if(result[3] <= minDetail){
        raiz->status = CHEIO;
    } else {
        raiz->status = PARCIAL;
    }
    raiz->color[0] = result[0]; // R
    raiz->color[1] = result[1]; // G
    raiz->color[2] = result[2]; // B

    quadTreeRec(raiz, minDetail, pic);

// COMENTE a linha abaixo quando seu algoritmo ja estiver funcionando
// Caso contrario, ele ira gerar uma arvore de teste

//#define DEMO
#ifdef DEMO

    /************************************************************/
    /* Teste: criando uma raiz e dois nodos a mais              */
    /************************************************************/

    QuadNode* raiz = newNode(0,0,width,height);
    raiz->status = PARCIAL;
    raiz->color[0] = 0;
    raiz->color[1] = 0;
    raiz->color[2] = 255;

    QuadNode* nw = newNode(0,0,width/2,height/2);
    nw->status = CHEIO;
    nw->color[0] = 0;
    nw->color[1] = 0;
    nw->color[2] = 255;

    // Aponta da raiz para o nodo nw
    raiz->NW = nw;
    
    QuadNode* se = newNode(width/2,width/2,width/2,height/2);
    
    se->status = CHEIO;
    se->color[0] = 0;
    se->color[1] = 255;
    se->color[2] = 0;

    // Aponta da raiz para o nodo nw
    raiz->SE = se;

    QuadNode* sw = newNode(0,width/2,width/2,height/2);
    sw->status = CHEIO;
    sw->color[0] = 255;
    sw->color[1] = 0;
    sw->color[2] = 0;

    // Aponta da raiz para o nodo nw
    raiz->SW = sw;

    QuadNode* ne = newNode(width/2,0,width/2,height/2);
    ne->status = CHEIO;
    ne->color[0] = 100;
    ne->color[1] = 100;
    ne->color[2] = 100;

    // Aponta da raiz para o nodo nw
    raiz->NE = ne;

#endif
    // Finalmente, retorna a raiz da árvore
    return raiz;
}

// Limpa a memória ocupada pela árvore
void clearTree(QuadNode* n)
{
    if(n == NULL) return;
    if(n->status == PARCIAL)
    {
        clearTree(n->NE);
        clearTree(n->NW);
        clearTree(n->SE);
        clearTree(n->SW);
    }
    //printf("Liberando... %d - %.2f %.2f %.2f %.2f\n", n->status, n->x, n->y, n->width, n->height);
    free(n);
}

// Ativa/desativa o desenho das bordas de cada região
void toggleBorder() {
    desenhaBorda = !desenhaBorda;
    printf("Desenhando borda: %s\n", desenhaBorda ? "SIM" : "NÃO");
}

// Desenha toda a quadtree
void drawTree(QuadNode* raiz) {
    if(raiz != NULL)
        drawNode(raiz);
}

// Grava a árvore no formato do Graphviz
void writeTree(QuadNode* raiz) {
    FILE* fp = fopen("quad.dot", "w");
    fprintf(fp, "digraph quadtree {\n");
    if (raiz != NULL)
        writeNode(fp, raiz);
    fprintf(fp, "}\n");
    fclose(fp);
    printf("\nFim!\n");
}

void writeNode(FILE* fp, QuadNode* n)
{
    if(n == NULL) return;

    if(n->NE != NULL) fprintf(fp, "%d -> %d;\n", n->id, n->NE->id);
    if(n->NW != NULL) fprintf(fp, "%d -> %d;\n", n->id, n->NW->id);
    if(n->SE != NULL) fprintf(fp, "%d -> %d;\n", n->id, n->SE->id);
    if(n->SW != NULL) fprintf(fp, "%d -> %d;\n", n->id, n->SW->id);
    writeNode(fp, n->NE);
    writeNode(fp, n->NW);
    writeNode(fp, n->SE);
    writeNode(fp, n->SW);
}

// Desenha todos os nodos da quadtree, recursivamente
void drawNode(QuadNode* n)
{
    if(n == NULL) return;

    glLineWidth(0.1);

    if(n->status == CHEIO) {
        glBegin(GL_QUADS);
        glColor3ubv(n->color);
        glVertex2f(n->x, n->y);
        glVertex2f(n->x+n->width-1, n->y);
        glVertex2f(n->x+n->width-1, n->y+n->height-1);
        glVertex2f(n->x, n->y+n->height-1);
        glEnd();
    }

    else if(n->status == PARCIAL)
    {
        if(desenhaBorda) {
            glBegin(GL_LINE_LOOP);
            glColor3ubv(n->color);
            glVertex2f(n->x, n->y);
            glVertex2f(n->x+n->width-1, n->y);
            glVertex2f(n->x+n->width-1, n->y+n->height-1);
            glVertex2f(n->x, n->y+n->height-1);
            glEnd();
        }
        drawNode(n->NE);
        drawNode(n->NW);
        drawNode(n->SE);
        drawNode(n->SW);
    }
    // Nodos vazios não precisam ser desenhados... nem armazenados!
}