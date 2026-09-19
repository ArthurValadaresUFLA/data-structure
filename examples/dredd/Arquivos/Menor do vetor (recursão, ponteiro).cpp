/*
# Arquivos Tipados - Menor do vetor (recursão, ponteiro)


Faça um programa que leia de um arquivo tipado cujo nome é "menor.bin" um vetor, alocado dinamicamente, de 10 números reais e determina, de forma recursiva, o menor elemento. O arquivo não tem cabeçalho.

Podemos usar a seguinte ideia:

* O menor elemento de um vetor de uma única posição é o seu único elemento.
* O menor elemento de um vetor de mais de uma posição é o menor entre o primeiro elemento e o menor do restante do vetor.

### Entradas

```
1. 10 números reais (float) a serem lidos do arquivo "menor.bin".
```

### Saídas

```
1. Menor valor lido.
```

### [Exemplo de Entrada (menor.bin)](menor.bin)

### Exemplo de Saída

```
1.5
```
*/

#include <iostream>
#include <fstream>

float procuraMenor(float *arr, int numElementos){

    if(numElementos == 1)
        return (*arr);

    float menorRestante = procuraMenor(arr + 1, numElementos - 1);
    return (arr[0] < menorRestante) ? arr[0] : menorRestante;

}

int main(){

    const int numElementos{10};
    std::ifstream arqDat("menor.bin");

    float *arr = new float[numElementos];
    arqDat.read((char *) arr, sizeof(float) * numElementos);

    std::cout << procuraMenor(arr, numElementos) << "\n";

    return 0;

}