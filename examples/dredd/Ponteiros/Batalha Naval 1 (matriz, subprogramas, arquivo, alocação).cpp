/*
# Ponteiros - Batalha Naval 1 (matriz, subprogramas, arquivo, alocação)


Leia de um arquivo de nome "BatalhaNaval.txt", duas matrizes de tamanho NxN a serem alocadas dinamicamente, sendo que primeira matriz representa a localização dos navios no tabuleiro e a segunda matriz representa a posição de onde os tiros atingiram na primeira matriz.

Na primeira matriz, k representa uma parte do k-ésimo navio, 0 partes no mar.

Na segunda matriz, 1 representa a posição do tiro (correspondente a posição na primeira matriz), 0 posição sem tiro.

Os navios sempre terão tamanho maior que uma posição da matriz, e estarão sempre totalmente na vertical ou horizontal.

O programa deverá retornar o número total de navios completamente afundados pelos tiros. 

**OBS:** Sub-rotinas devem ser utilizadas.

### Entradas

```
1. Tamanho da matriz N (inteiro).
2. Valores da primeira matriz NxN (inteiros).
3. Valores da segunda matriz NxN (inteiros).
```

### Saídas

```
1. Número total de navios completamente afundados (inteiro).
```

### Exemplo de Entrada

```
5
0 1 1 1 0
2 0 0 0 0
2 0 0 0 0
2 0 0 0 0
2 3 3 0 0
0 1 1 1 1
1 0 0 0 0
1 0 0 0 0
1 0 0 0 0
1 1 0 0 0
```

### Exemplo de Saída

```
2
```
*/

#include <iostream>
#include <fstream>
#include <cstring>

void alocadorMatriz(int **&matriz, int tamMatriz){

    matriz = new int*[tamMatriz];
    for(int i{0}; i<tamMatriz; i++)
        matriz[i] = new int[tamMatriz];
    
}

void destrutorMatriz(int **matriz, int tamMatriz){

    for(int i{0}; i<tamMatriz; i++)
        delete[] matriz[i];
    delete[] matriz;

}

void lerMatriz(int **matriz, int tamMatriz, std::ifstream &arq){

    for(int i{0}; i<tamMatriz; i++){
        for(int j{0}; j<tamMatriz; j++){
            arq >> matriz[i][j];
        }
    }

}

int contabilizaNavios(int **matriz, int tamMatriz){

    int capacidade{10}, numNavios{0};
    int *idNavios{new int[capacidade]};

    int k;

    for(int i{0}; i<tamMatriz; i++){
        for(int j{0}; j<tamMatriz; j++){

            if(matriz[i][j]){

                k = 0;
                while(k<numNavios && idNavios[k] != matriz[i][j]){
                    k++;
                }

                if(k == numNavios){

                    if(numNavios == capacidade){
                        capacidade += 10;
                        int *aux = new int[capacidade];
                        std::memcpy(aux, idNavios, sizeof(int) * numNavios);
                        delete[] idNavios;
                        idNavios = aux;
                    }

                    idNavios[numNavios++] = matriz[i][j];

                }

            }

        }
    }

    return numNavios;

}

void realizaDisparos(int **matrizNavios, int **matrizDisparos, int tamMatriz){

    for(int i{0}; i<tamMatriz; i++){
        for(int j{0}; j<tamMatriz; j++){

            if(matrizDisparos[i][j]){
                matrizNavios[i][j] = 0;
            }

        }
    }

}

int main(){

    std::ifstream arq("BatalhaNaval.txt");
    int tamMatriz;
    int **matrizNavios, **matrizDisparos;

    arq >> tamMatriz;

    alocadorMatriz(matrizNavios, tamMatriz);
    lerMatriz(matrizNavios, tamMatriz, arq);

    alocadorMatriz(matrizDisparos, tamMatriz);
    lerMatriz(matrizDisparos, tamMatriz, arq);

    int naviosInicias{contabilizaNavios(matrizNavios, tamMatriz)};
    realizaDisparos(matrizNavios, matrizDisparos, tamMatriz);
    int naviosFinais{contabilizaNavios(matrizNavios, tamMatriz)};

    std::cout << (naviosInicias - naviosFinais) << "\n";

    destrutorMatriz(matrizNavios, tamMatriz);
    destrutorMatriz(matrizDisparos, tamMatriz);

    return 0;
}