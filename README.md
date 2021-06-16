# Programação de Baixo Nível

Professores da disciplina: Alexandre Augustine e Marcelo Cohen

Dupla nos trabalhos: Lucas Pereira Salbego <Lucas.Salbego99@edu.pucrs.br>

Foi uma disciplina onde vimos sobre ponteiros em C. Nas pastas Basico, DesafioPont, Ponteiros contém alguns códigos em C para conhecer a linguagem e conhecer sobre ponteiros.

# Trabalho 1 - Gerador de ASCII Art
[Enunciado do Trabalho 1](https://mflash.github.io/progswb2/trab/t1-202-hjb7fyhdc/)

### 1 Introdução
O uso de caracteres da tabela ASCII para produzir desenhos não é uma idéia recente: vem de tempos longínquos, onde os dispositivos de saída eram monitores monocromáticos e impressoras matriciais ou de linha. Mais recentemente, se tornou uma forma de "arte" - daí o termo ASCII Art. Ou seja, imagens criadas exclusivamente com o uso de caracteres da tabela ASCII.
O objetivo deste trabalho é explorar os conceitos de programação C vistos em aula, criando um programa capaz de produzir a representação de uma imagem qualquer em ASCII. A saída do programa será na forma de um arquivo HTML, que poderá ser visualizado no browser. Se você estava em outro planeta nos últimos anos e nunca viu isso, há diversos serviços na rede que fazem esse tipo de conversão:

- http://www.text-image.com/
- http://picascii.com/
- http://lunatic.no/ol/img2aschtml.php

O resultado pode ser visto na figura 1:

![Alt text](https://github.com/DeltaRig/PBaixoNivel/tree/master/imagens/flower.jpg "Title") ![Alt text](https://github.com/DeltaRig/PBaixoNivel/tree/master/imagens/flower_ascii.jpg "Title")

### 2 Funcionamento
Ao ser iniciado, o programa deve solicitar o nome de um arquivo de imagem e carregá-lo (ou obter o nome por parâmetros de linha de comando).
Para ler as imagens utilizaremos uma biblioteca simples (integrada no projeto de exemplo) denominada SOIL. Veja detalhes na seção 2.1. Após a leitura, a imagem deve ser processada e gerado o arquivo de saída em HTML.

Parte do objetivo deste trabalho é a criação de um algoritmo que produza um resultado interessante. Uma possível estratégia é a seguinte:

1. Obter do usuário o nome da imagem a ser carregada, e o fator de redução desejado. Por exemplo, o fator 50% utilizará apenas metade dos pixels originais na saída. Esse fator é usado para calcular o tamanho dos blocos de pixels (ver passo 5).

2. Ler a imagem colorida, onde cada pixel (ponto da imagem) é representado em RGB (ver seção 2.1).

3. Converter a imagem para tons de cinza, isto é, eliminar a cor e considerar que qualquer pixel pode ser representado por um único número inteiro, representando variações de preto (0) a branco (255).

4. Associar cada caractere a um tom de cinza específico. Você pode pesquisar nos sites indicados (ou outros) para ver como isso normalmente é realizado. Mas a idéia básica é que caracteres que ocupam mais espaço visualmente correspondam a cores mais claras (considerando um fundo preto). Por exemplo, "@" é mais "claro" do que "."

5. De acordo com as proporções das letras (que não são quadradas), agrupar os pixels da imagem em blocos retangulares (por exemplo, 4 x 5). Cada bloco irá se transformar em um único caractere na saída. Isso é necessário, pois as imagens normalmente são muito grandes para fazer uma correspondência 1:1.

6. Calcular o tom de cinza médio de cada bloco (por exemplo, fazendo a média de todos os pixels do bloco).

7. Para cada bloco de pixels, escolher e gerar um caractere na saída, cujo tom de cinza é uma boa aproximação para a média do bloco.

As próximas seções dão algumas dicas de como realizar certas etapas.

#### 2.1 Leitura da imagem
Uma imagem é geralmente representada por uma matriz de pontos (pixels) onde cada cor é definida por 3 componentes: vermelho (R), verde (G) e azul (B). Cada uma dessas componentes usualmente é codificada em um byte, o que produz 3 bytes por pixel (24 bits) - ou seja, 16 milhões de possíveis cores. Em outras palavras, as intensidades (R, G, B) variam de 0 a 255, onde 0 é escuro e 255 é claro.
Veja abaixo como diversas cores são representadas nesse formato - cada cor está expressa pelas componentes RGB em hexadecimal.

![Alt text](https://github.com/DeltaRig/PBaixoNivel/tree/master/imagens/hex-colors.jpg "Title") ![Alt text](https://github.com/DeltaRig/PBaixoNivel/tree/master/imagens/rgbcolors.jpg "Title") 

O código fornecido define duas structs: uma para representar um pixel e outra para representar a imagem inteira. Após a leitura da imagem, os pixels estarão disponíveis no vetor pic.img

```
// Um pixel RGB (24 bits)
typedef struct {
    unsigned char r, g, b;
} RGB;

// Uma imagem RGB
typedef struct {
    int width, height;
    RGB* img;            // vetor de pixels
} Img;

// A imagem
Img pic;

// Cada pixel está armazenado em pic.img[i], onde i é o índice do pixel.
// Exemplo: acessando os dois primeiros pixels
RGB aux1 = pic.img[0];
RGB aux2 = pic.img[1];
...
```

#### 2.2 Conversão para tons de cinza
O processo de conversão de uma imagem para tons de cinza pode ser feito com o algoritmo descrito abaixo. A idéia é simplicar a imagem, deixando as três componentes R,G e B de cada ponto iguais entre si - equivale a "tirar a cor" da imagem. O valor a ser colocado nestes 3 componentes deverá ser igual à intensidade da cor, dada pela fórmula:

```
Para cada ponto (x,y) da imagem:
    Obtem a cor do pixel (r,g,b)
    // calcula o equivalente cinza da cor
    i = (0.3 * r + 0.59 * g + 0.11 * b)
    // armazena o cinza no pixel
    EscreveCor(x,y,i,i,i) # x,y,r,g,b
```

#### 2.3 Geração do HTML de saída
Para gerar o código HTML resultante, é preciso escrever determinadas tags no arquivo de saída, de forma que o browser saiba como interpretar os caracteres:

```
<html><head></head>
<body style="background: black;" leftmargin=0 topmargin=0> 
<style> 
   pre  {
          color: white;
    font-family: Courier;
      font-size: 8px;
   }
</style>
```

Esse trecho define que o fundo será preto, enquanto os caracteres serão brancos, para o estilo pré-formatado (tag PRE) e com uma fonte bem pequena (8px). A partir deste ponto, a imagem deve aparecer dentro de um bloco <pre>...</pre>:

```
<pre>
... caracteres da imagem - linha 1 ...
... caracteres da imagem - linha 2 ...
...
</pre>
```

Finalmente, deve-se fechar o corpo da página e o HTML em si:
```
</body>
</html>
```

# Trabalho 2 - Compressão de Imagens por Quadtree

### 1 Introdução
Ha diversas técnicas que podem ser usadas para a compressão de imagens. As mais conhecidas são os algoritmos implementados no padrão JPEG ou PNG, por exemplo. Porém, há outras técnicas menos conhecidas: uma delas é baseada no uso de uma árvore para a representação da imagem. Essa técnica, conhecida como representação através de subdivisão por ocupação espacial, utiliza uma estrutura de dados denominada quadtree, pois é uma árvore onde cada nodo pode ter zero ou quatro "filhos".

O objetivo deste trabalho é explorar os conceitos de programação C, bem como o uso de ponteiros em uma estrutura de árvore, criando um programa capaz de ler uma imagem qualquer e gerar uma quadtree correspondente. Para visualizar o resultado, é fornecido um código que desenha a árvore.

### 2 Funcionamento
Ao ser iniciado, o programa deve carregar um arquivo de imagem. Para tanto, utilizaremos uma biblioteca simples (integrada no projeto) denominada SOIL.

Ler a imagem colorida, onde cada pixel (ponto da imagem) é representado em RGB (componente vermelho, verde e azul: cada um é um unsigned char).

Obter do usuário o menor nível de detalhe desejado. Esse valor varia de imagem para a imagem, e representa, em linhas, gerais, a menor diferença média entre os pixels de uma determinada região e a cor média da região (veja detalhes a seguir).

Gerar a quadtree e chamar a função para desenhá-la na tela (já fornecido).

O código fornecido (ver seção 3) contém um projeto com as bibliotecas necessárias para compilá-lo, mais algumas imagens de teste.

O programa de exemplo recebe o nome da imagem a ser carregada pela linha de comando, como o primeiro parâmetro.

A imagem original é então exibida, e pode-se usar as seguintes teclas:

ESC: libera memória e termina o programa

- =: aumenta em uma unidade o nível de detalhe atual, regenerando a árvore
- -: reduz em uma unidade o nível de detalhe atual, regenerando a árvore
- b: liga/desliga o desenho das bordas de cada região
- r: regenera e desenha a árvore, sem alterar o nível de detalhe
- w: grava a árvore no disco, no formato de entrada do Graphviz (.dot)

As próximas seções explicam como realizar as etapas.

#### 2.1 Geração da Quadtree

O processo de geração da quadtree é um algoritmo recursivo: a raiz da árvore representa toda a região da imagem. Se essa região não tem muitos detalhes, o processo se encerra. Caso contrário, são gerados nodos filhos para cada subregião: superior direita (NW), superior esquerda (NE), inferior direita (SW) e inferior esquerda (SE). E o algoritmo é novamente aplicado para cada uma delas. Para entender o processo, veja a sequência de figuras abaixo, que mostra o resultado ao algoritmo para 1, 2, 3, 4 e 5 níveis na árvore:

![Alt text](https://github.com/DeltaRig/PBaixoNivel/tree/master/imagens/geraQ.png "Title") 

A última imagem mostra o resultado final, ou seja, ao chegar no nível de detalhe desejado. Esse nível é especificado através de um valor, que deve ser comparado com o nível de detalhe da região (ver seção 2.2): se este último for inferior ou igual ao valor informado, significa que o nível desejado foi atingido e o processo se encerra. Note que regiões com apenas uma cor têm nível de detalhe igual a zero.

![Alt text](https://github.com/DeltaRig/PBaixoNivel/tree/master/imagens/qt6.png "Title") 

Finalmente, a figura abaixo apresenta um exemplo de árvore gerada, para uma imagem simples:

![Alt text](https://github.com/DeltaRig/PBaixoNivel/tree/master/imagens/qe.png "Title") 

#### 2.2 Acessando os pixels da imagem

A biblioteca SOIL é responsável pela correta leitura da imagem. O programa principal armazena a imagem em uma struct Img:
```
typedef struct {
    int width, height;
    RGB *img;
} Img;
```

Ou seja, há a informação de largura e altura, bem como um ponteiro para o vetor com os pixels da imagem. Lembre-se que será necessário acessar regiões específicas da imagem, então será preciso converter coordenadas na forma (linha,coluna) para uma posição nesse vetor.

O módulo quadtree.c, na função geraQuadtree, demonstra como acessar as componentes de cor de cada pixel:

```
// pixels é um ponteiro que permite o acesso do vetor img como matriz - veja no código

for(int i=0; i<10; i++)
    printf("%02X %02X %02X\n",pixels[0][i].r,pixels[0][i].g,pixels[0][i].b);
```

Ou seja, estamos exibindo, em hexadecimal, as componentes de cor R, G e B dos primeiros 10 pixels (a partir do canto superior esquerdo).

#### 2.3 Cálculo do nível de detalhe
Para calcular o nível de detalhe de uma região, deve ser usado o seguinte algoritmo:

Descobrir a cor média da região (média de todas as cores dos pixels da região, isto é, a média das componentes R, G e B de todos os pixels). A cor média é, portanto, também expressa em R, G e B.

Calcular a diferença entre cada pixel da região e essa cor média. Isso pode ser feito através da distância euclideana entre cada cor (Rp,Gp,Bp) e a cor média (Rm,Gm,Bm) , imaginando que as componentes R, G e B são coordenadas espaciais:

![Alt text](https://github.com/DeltaRig/PBaixoNivel/tree/master/imagens/qc.png "Title") 

Acumular essa diferença ao longo de toda a região e calcular a diferença média no final. Para tanto, essa soma de diferenças precisa ser dividida pela área em pixels da região.

A diferença média resultante corresponde ao nível de detalhe da região.

#### 2.4 A struct QuadNode
A estrutura de dados a ser utilizada é a struct QuadNode, já fornecida. O algoritmo de geração da árvore deve estar presente no módulo quadtree.c (também já fornecido), dentro da função geraQuadTree (ou ser chamado por ela).

A struct Quad representa um nodo da quadtree, com a seguinte estrutura:

```
enum { CHEIO, PARCIAL };

struct Quad {
    unsigned int id;
    float x, y;              // canto superior esquerdo da região
    float width, height;     // largura e altura da região
    int status;              // CHEIO ou PARCIAL
    unsigned char color[3];  // cor média da região
    struct Quad* NW;            // ponteiros para os filhos, se houver
    struct Quad* NE;
    struct Quad* SW;
    struct Quad* SE;
};

typedef struct Quad QuadNode;
```

A struct Quad não deve ser alterada, pois é usada dessa forma para desenhar a quadtree. Declaramos também um typedef para a struct Quad com o nome QuadNode, para facilitar seu uso. As alterações devem ser feitas apenas no módulo quadtree, criando funções adicionais, etc. A função geraQuadtree deve ser complementada, incluindo o código que gera os nodos da árvore. Preferencialmente, não altere o restante do programa.

Você pode utilizar a função newNode para gerar um novo nodo na árvore: ela recebe as coordenadas x e y, bem como largura e altura do nodo, alocando memória e devolvendo um ponteiro para QuadNode. Observe que você é responsável pelo encadeamento, isto é, a ligação desse nodo com os demais.
```
QuadNode* newNode(int x, int y, int width, int height);
```

## 3 Compilação (para ambos trabalhos)

Quando recebemos os trabalhos, foi disponibilizado um zip com um algoritmo que já realiza a leitura de uma imagem qualquer de 24 bits. O projeto pode ser compilado no Windows, Linux ou macOS, seguindo as instruções abaixo.

Para a compilação no Linux, é necessário ter instalado os pacotes de desenvolvimento da biblioteca OpenGL. Para Ubuntu, Mint, Debian e derivados, instale com:

```
sudo apt-get install freeglut3-dev
```

Para a compilação no Windows ou no macOS, não é necessário instalar mais nada - o compilador já vem com as bibliotecas necessárias.

#### 3.1 Visual Studio Code
Se você estiver utilizando o Visual Studio Code, basta descompactar o zip e abrir a pasta.

Para compilar: use Ctrl+Shift+B (⌘+Shift+B no macOS).

Para executar, use F5 para usar o debugger ou Ctrl+F5 para executar sem o debugger.

#### 3.2 Outros ambientes ou terminal
Caso esteja usando outro ambiente de desenvolvimento, fornecemos um Makefile para Linux e macOS, e outro para Windows (Makefile.mk).

Dessa forma, para compilar no Linux ou macOS, basta digitar:

```make```

Se estiver utilizando o Windows, o comando é similar:
```mingw32-make -f Makefile.mk ```

Alternativamente, você também pode utilizar o CMake (Cross Platform Make) para compilar pelo terminal. Para tanto, crie um diretório build embaixo do diretório do projeto e faça:
cd build
cmake ..
make -j  # ou mingw32-make -j no Windows

