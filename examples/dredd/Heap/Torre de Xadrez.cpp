/*
# Matrizes - Xadrez - Torre


Faça um programa que receba como entrada um tabuleiro de xadrez (matriz de 8x8 posições) e informe quais são as peças ameaçadas pela torre do jogador.

O tabuleiro será dado como uma matriz de 0s, 1s e 2s. Zeros representam posições sem peça. O número 1 representa uma torre (haverá somente uma torre no tabuleiro) e os números 2 representam outras peças (haverá zero ou mais peças representadas pelo número 2 no tabuleiro).

A torre pode ser movida na vertical ou na horizontal quantas casas quiser, mas não pode passar por cima de outra peça. As posições com outras peças que a torre pode tomar são posições ditas "ameaçadas" pela torre. A imagem abaixo mostra uma torre que ameça outras 3 peças (marcadas com um X).

<img src="./xadrez.png" width=300 height=300>

Seu programa deve escrever as coordenadas (linha e coluna, nesta ordem) de cada peça (valor 2 na matriz) ameaçada pela torre (valor 1 na matriz).

### Entradas

```
1. 64 valores inteiros, dispostos na forma de uma matriz 8x8 de peças representadas conforme explicado acima.

```

### Saídas

```
1. As coordenadas (linha e depois coluna) de cada peça ameaçada, seguindo a ordem de leitura da matriz, ou seja, 
da menor para a maior linha e da menor para maior coluna (de cima para baixo e da esquerda para direita). As 
linhas e colunas começam em zero. Cada par de coordenadas deve estar numa linha. Caso nenhuma peça seja ameaçada 
pela torre, o programa não deve escrever coisa alguma.
```

### Exemplo de Entrada

```
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 2 0 0 0
2 2 0 0 1 0 2 2
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
```

### Exemplo de Saída

```
2 4
3 1
3 6
```
*/

#include <iostream>

void procuraPecas(int tamMatriz, int matriz[][8], int linhaTorre, int colunaTorre, int direcaoX = 0, int direcaoY = -1);
bool posValida(int tamMatriz, int x, int y);

int main(){

    const int tamMatriz{8};
    int tabuleiro[tamMatriz][tamMatriz], linhaTorre, colunaTorre;

    for(int i{0}; i<tamMatriz; i++){
        for(int j{0}; j<tamMatriz; j++){
            std::cin >> tabuleiro[i][j];
            if(tabuleiro[i][j] == 1){
                linhaTorre = i;
                colunaTorre = j;
            }
        }
    }

    procuraPecas(tamMatriz, tabuleiro, linhaTorre, colunaTorre);
    procuraPecas(tamMatriz, tabuleiro, linhaTorre, colunaTorre, -1, 0);
    procuraPecas(tamMatriz, tabuleiro, linhaTorre, colunaTorre, 1, 0);
    procuraPecas(tamMatriz, tabuleiro, linhaTorre, colunaTorre, 0, 1);

    return 0;
}

bool posValida(int tamMatriz, int x, int y){
    return (x>=0 && x<tamMatriz && y>=0 && y<tamMatriz);
}

void procuraPecas(int tamMatriz, int matriz[][8], int linhaTorre, int colunaTorre, int direcaoX, int direcaoY){

    int i{linhaTorre + direcaoY}, j{colunaTorre + direcaoX};
    while(posValida(tamMatriz, i, j) && !(matriz[i][j])){
        i+= direcaoY;
        j+= direcaoX;
    }

    if(posValida(tamMatriz, i , j))
        std::cout << i << " " << j << "\n";

}