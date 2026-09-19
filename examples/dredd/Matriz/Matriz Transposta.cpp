/*
# Matrizes - Matriz Transposta


Faça um programa que transpõe uma matriz. Transpor uma matriz significa trocar as linhas pelas colunas da matriz. Escrever a matriz transposta é suficiente, não sendo necessário criar antes uma matriz transposta.

### Entradas

```
1. o número de linhas da matriz e o número de colunas da matriz, na mesma linha
2. os elementos da matriz (números inteiros).

```

### Saídas

```
1. O programa deverá escrever a matriz transposta.
```

### Exemplo de Entrada

```
3 5
1 2 3 4 5
6 7 8 9 0
4 5 6 7 8
```

### Exemplo de Saída

```
1 6 4 
2 7 5 
3 8 6 
4 9 7 
5 0 8
```
*/

#include <iostream>

int main(){

    int numLinhas, numColunas;
    std::cin >> numLinhas >> numColunas;

    int matriz[numLinhas][numColunas];

    for(int i{0}; i<numLinhas; i++)
        for(int j{0}; j<numColunas; j++)
            std::cin >> matriz[i][j];
    

    for(int j{0}; j<numColunas; j++){
        for(int i{0}; i<numLinhas; i++)
            std::cout << matriz[i][j] << " ";
        std::cout << "\n";
    }

    return 0;
}