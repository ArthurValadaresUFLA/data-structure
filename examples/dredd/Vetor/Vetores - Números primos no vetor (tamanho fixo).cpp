/*
# Vetores - Números primos no vetor (tamanho fixo)


Faça um programa para receber nove números inteiros positivos, armazená-los em um vetor, calcular e exibir no dispositivo de saída padrão aqueles números que são primos e suas respectivas posições no vetor. Se nenhum número primo for fornecido, nenhuma mensagem precisará ser exibida.

### Entradas

```
1. Nove números inteiros positivos a serem armazenados em um vetor.
```

### Saídas

```
1. Sequência de números primos e suas respectivas posições (índices no vetor). 

Obs.: Aqueles números que forem primos e suas respectivas posições deverão ser exibidos aos pares.
```

### Exemplo de Entrada

```
7 13 49 23 6 21 78 98 3
```

### Exemplo de Saída

```
7 0
13 1
23 3
3 8
```
*/

#include <iostream>

bool ehPrimo(int x);

int main(){

    const int numElementos{9};
    int arr[numElementos];

    for(int i{0}; i<numElementos; i++)
        std::cin >> arr[i];

    for(int i{0}; i<numElementos; i++)
        if(ehPrimo(arr[i]))
            std::cout << arr[i] << "  " << i << "\n";

}

bool ehPrimo(int x){
    int i{2};

    while(i < x){
        if(!(x % i))
            return false;
        i++;
    }

    return true; 

}