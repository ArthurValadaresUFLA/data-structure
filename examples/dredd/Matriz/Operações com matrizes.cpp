/*
# Matrizes - Operações com matrizes


Elabore um programa que preencha uma matriz 10 x 10 com números inteiros, execute cada operação de troca especificada a seguir na matriz original e mostre cada matriz resultante. Você vai precisar de ao menos uma matriz extra para realizar as operações.

Operações de troca a serem realizadas (considerando índices que começam em 1):

1. a linha 2 com a linha 8;
1. a coluna 4 com a coluna 10;
1. a diagonal principal com a diagonal secundária;
1. a linha 5 com a coluna 10.


### Entradas

```
1. Uma matriz 10 x 10 de inteiros.

```

### Saídas

```
1. A matriz 10 x 10 resultante das devidas operações descritas em 1, 2, 3, e 4 (utilizando um índice numérico 
antes de exibir cada matriz).
```

### Exemplo de Entrada

```
1 2 3 4 5 6 7 8 9 0
2 3 4 5 6 7 8 9 0 1
3 4 5 6 7 8 9 0 1 2
4 5 6 7 8 9 0 1 2 3
5 6 7 8 9 0 1 2 3 4
6 7 8 9 0 1 2 3 4 5
7 8 9 0 1 2 3 4 5 6
8 9 0 1 2 3 4 5 6 7
9 0 1 2 3 4 5 6 7 8
0 1 2 3 4 5 6 7 8 9
```

### Exemplo de Saída

```
1.
1 2 3 4 5 6 7 8 9 0
8 9 0 1 2 3 4 5 6 7
3 4 5 6 7 8 9 0 1 2
4 5 6 7 8 9 0 1 2 3
5 6 7 8 9 0 1 2 3 4
6 7 8 9 0 1 2 3 4 5
7 8 9 0 1 2 3 4 5 6
2 3 4 5 6 7 8 9 0 1
9 0 1 2 3 4 5 6 7 8
0 1 2 3 4 5 6 7 8 9
2.
1 2 3 0 5 6 7 8 9 4
2 3 4 1 6 7 8 9 0 5
3 4 5 2 7 8 9 0 1 6
4 5 6 3 8 9 0 1 2 7
5 6 7 4 9 0 1 2 3 8
6 7 8 5 0 1 2 3 4 9
7 8 9 6 1 2 3 4 5 0
8 9 0 7 2 3 4 5 6 1
9 0 1 8 3 4 5 6 7 2
0 1 2 9 4 5 6 7 8 3
3.
0 2 3 4 5 6 7 8 9 1
2 0 4 5 6 7 8 9 3 1
3 4 0 6 7 8 9 5 1 2
4 5 6 0 8 9 7 1 2 3
5 6 7 8 0 9 1 2 3 4
6 7 8 9 1 0 2 3 4 5
7 8 9 3 1 2 0 4 5 6
8 9 5 1 2 3 4 0 6 7
9 7 1 2 3 4 5 6 0 8
9 1 2 3 4 5 6 7 8 0
4.
1 2 3 4 5 6 7 8 9 5
2 3 4 5 6 7 8 9 0 6
3 4 5 6 7 8 9 0 1 7
4 5 6 7 8 9 0 1 2 8
0 1 2 3 4 5 6 7 8 9
6 7 8 9 0 1 2 3 4 0
7 8 9 0 1 2 3 4 5 1
8 9 0 1 2 3 4 5 6 2
9 0 1 2 3 4 5 6 7 3
0 1 2 3 4 5 6 7 8 4
```
*/

#include <iostream>
#include <cstring>

void mostraMatriz(int tamMatriz, int matriz[][10]);

void trocaLinha(int tamMatriz, int matriz[][10], int linhaA, int linhaB);

void trocaColuna(int tamMatriz, int matriz[][10], int colunaA, int colunaB);

void trocaDiagonal(int tamMatriz, int matriz[][10]);

void linhaPorColuna(int tamMatriz, int matriz[][10], int linha, int coluna);

int main(){

    const int tamMatriz{10};

    int matriz[tamMatriz][tamMatriz];

    for(int i{0}; i<(tamMatriz*tamMatriz); i++)
        std::cin >> matriz[int(i/tamMatriz)][(i % tamMatriz)];
    
    std::cout << "1.\n";
    trocaLinha(tamMatriz, matriz, 2, 8);

    std::cout << "2.\n";
    trocaColuna(tamMatriz, matriz, 4, 10);

    std::cout << "3.\n";
    trocaDiagonal(tamMatriz, matriz);

    std::cout << "4.\n";
    linhaPorColuna(tamMatriz, matriz, 5, 10);

    return 0;
}

void mostraMatriz(int tamMatriz, int matriz[][10]){

     for(int i{0}; i<tamMatriz; i++){
        for(int j{0}; j<tamMatriz; j++){
            std::cout << matriz[i][j] << " ";
        }
        std::cout << "\n";
    }

}

void trocaLinha(int tamMatriz, int matriz[][10], int linhaA, int linhaB){

    linhaA--;
    linhaB--;

    int matrizFinal[tamMatriz][10];
    std::memcpy(matrizFinal, matriz, (sizeof(int) * tamMatriz * tamMatriz));

    for(int i{0}; i<tamMatriz; i++){
        matrizFinal[linhaA][i] = matriz[linhaB][i];
        matrizFinal[linhaB][i] = matriz[linhaA][i];
    }
    mostraMatriz(tamMatriz, matrizFinal);
}

void trocaColuna(int tamMatriz, int matriz[][10], int colunaA, int colunaB){

    colunaA--;
    colunaB--;

    int matrizFinal[tamMatriz][10];
    std::memcpy(matrizFinal, matriz, (sizeof(int) * tamMatriz * tamMatriz));

    for(int i{0}; i<tamMatriz; i++){
        matrizFinal[i][colunaA] = matriz[i][colunaB];
        matrizFinal[i][colunaB] = matriz[i][colunaA];
    }
    mostraMatriz(tamMatriz, matrizFinal);
}

void trocaDiagonal(int tamMatriz, int matriz[][10]){

    int matrizFinal[tamMatriz][10];
    std::memcpy(matrizFinal, matriz, (sizeof(int) * tamMatriz * tamMatriz));

    for(int i{0}; i<tamMatriz; i++){
        matrizFinal[i][i] = matriz[i][(tamMatriz - 1 - i)];
        matrizFinal[i][(tamMatriz - 1 - i)] = matriz[i][i];
    }
    mostraMatriz(tamMatriz, matrizFinal);
}

void linhaPorColuna(int tamMatriz, int matriz[][10], int linha, int coluna){

    linha--;
    coluna--;

    int matrizFinal[tamMatriz][10];
    std::memcpy(matrizFinal, matriz, (sizeof(int) * tamMatriz * tamMatriz));

    for(int i{0}; i<tamMatriz; i++){
        matrizFinal[linha][i] = matriz[i][coluna];
        matrizFinal[i][coluna] = matriz[linha][i];
    }
    mostraMatriz(tamMatriz, matrizFinal);
}