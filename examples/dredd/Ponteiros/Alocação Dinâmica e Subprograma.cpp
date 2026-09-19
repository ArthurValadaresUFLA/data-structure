/*
# Ponteiros – Alocação Dinâmica e Subprograma


Faça um subprograma (do tipo procedimento) para preencher automaticamente um vetor de números em ponto flutuante, nomeie o subprograma como obterVetor. Para preencher o vetor seu subprograma deverá satisfazer as seguintes restrições:

1. O valor a ser armazenado em uma posição i qualquer do vetor deverá ser obtido a partir da expressão: (2 * i! + i) / (i*i + 1.75). Note que i representa os índices dos subscritos (posições) do vetor.
1. O subprograma de preenchimento do vetor deverá possuir apenas dois parâmetros de entrada. O primeiro deles deverá ser um tipo de dado ponteiro para números em ponto flutuante e o outro deverá ser um inteiro indicando o tamanho do vetor.
1. O vetor que armazenará os dados deverá ser alocado dinamicamente.
1. A alocação dinâmica deverá ser realizada fora do subprograma obterVetor.

Faça um subprograma principal para testar o procedimento obterVetor, para isso seu programa deverá ler um inteiro N, alocar dinamicamente o vetor, chamar o subprograma obterVetor e preencher o vetor. Em seguida, seu programa deverá ler um segundo número inteiro M e exibir no dispositivo de saída padrão todos os valores armazenados no vetor a partir da posição M (inclusive). Note que todas as operações de entrada e saída de dados devem ser realizadas no subprograma principal. Assuma que M sempre será menor do que N.

### Entradas

```
1. Inteiro N.
2. Inteiro M.
```

### Saídas

```
1. Sequência de (N-M) valores em ponto flutuante. Indicando os valores armazenados no vetor.
```

### Exemplo de Entrada

```
5
0
```

### Exemplo de Saída

```
1.14286
1.09091
1.04348
1.39535
2.92958
```

### Exemplo de Entrada

```
5
3
```

### Exemplo de Saída

```
1.39535
2.92958
```
*/

#include <iostream>

void obterVetor(float *arr, int tamArr){

    int fatorial{1};

    arr[0] = (2)/(1.75);

    for(int i{1}; i<tamArr; i++){
        fatorial *= i;
        arr[i] = (2 * fatorial + i) / (i*i + 1.75);
    }

}

int main(){

    int N;
    std::cin >> N;

    float *arr = new float[N];
    obterVetor(arr, N);

    int M;
    std::cin >> M;

    for(int i{M}; i<N; i++)
        std::cout << arr[i] << "\n";

    delete[] arr;

    return 0;
}