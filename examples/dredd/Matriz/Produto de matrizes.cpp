/*
# Matrizes - Produto de matrizes


Crie um programa que preencha uma primeira matriz de ordem 4 x 5 e uma segunda matriz 5 x 2. O programa deverá, também, calcular e mostrar a matriz resultante do produto matricial das duas matrizes anteriores, armazenando-o em uma terceira matriz de ordem 4 x 2.

### Entradas

```
1. Uma matriz 4 x 5.
2. Uma matriz 5 x 2.

```

### Saídas

```
1. Matriz 4 x 2 resultante do produto entre as duas matrizes anteriores.
```

### Exemplo de Entrada

```
1 2 3 4 5
2 5 9 7 1
3 2 9 4 0
4 6 4 8 8

1 2
2 7
3 6
4 7
5 0
```

### Exemplo de Saída

```
55 62
72 142
50 102
100 130
```
*/

#include <iostream>

int main(){

    int matrizA[4][5], matrizB[5][2], matrizC[4][2];

    for(int i{0}; i<4; i++)
        for(int j{0}; j<5; j++)
            std::cin >> matrizA[i][j];

    for(int i{0}; i<5; i++)
        for(int j{0}; j<2; j++)
            std::cin >> matrizB[i][j];

    int soma;

    for(int i{0}; i<4; i++){
        for(int j{0}; j<2; j++){

            soma = 0;
            for(int k{0}; k<5; k++)
                soma += matrizA[i][k] * matrizB[k][j];
            
            matrizC[i][j] = soma;

        }
    }
    
    for(int i{0}; i<4; i++){
        for(int j{0}; j<2; j++){
            std::cout << matrizC[i][j] << " ";
        }
        std::cout << "\n";
    }

    return 0;
}