/*
# Matrizes - Minimax


Na teoria de sistemas define-se como elemento minimax de uma matriz o menor elemento da linha onde se encontra o maior elemento da matriz. Escreva um programa que receba uma matriz quadrada de inteiros, 10x10, e retorne seu elemento minimax, seguido de sua posição. Em caso de números iguais considere o que aparece primeiro.

### Entradas

```
1. Um matriz de inteiros de tamanho 10x10.

```

### Saídas

```
1. O menor elemento da linha que tem o maior elemento da matriz.
2. A linha e a coluna onde está o elemento do item anterior.
```

### Exemplo de Entrada

```
 1  2  3  4  5  6  7 8  9  0
11  4 32  5  6  8  9 2  3  1
 2  3  5  6  7  8  1 0  3  1
 1  3 45  2  6  8  9 0  2  0
 4 30  4  2  6 18  5 0  1  0
 2  3 40  2  6  8 19 0 45  9
 3  2  5  7  7  8 10 0  2  2
 1  3 22  2 13  6  9 1  1  0
 4 30  4  2  6 18  5 0  9 10
 2  3 34  2  6  8 19 0  0  0
```

### Exemplo de Saída

```
0
3 7
```
*/

#include <iostream>

int main(){

    const int tamMatriz{10};
    int matriz[tamMatriz][tamMatriz];

    int linhaMaior{0}, colunaMaior{0};

    for(int i{0}; i<tamMatriz; i++){
        for(int j{0}; j<tamMatriz; j++){

            std::cin >> matriz[i][j];
            if(matriz[i][j] > matriz[linhaMaior][colunaMaior]){
                linhaMaior = i;
                colunaMaior = j;
            }

        }
    }

    int colunaMenor{0};

    for(int i{0}; i<tamMatriz; i++){
        if(matriz[linhaMaior][i] < matriz[linhaMaior][colunaMenor])
            colunaMenor = i;
    }
    
    std::cout << matriz[linhaMaior][colunaMenor] << "\n";
    std::cout << linhaMaior << " " << colunaMenor << "\n";


    return 0;
}