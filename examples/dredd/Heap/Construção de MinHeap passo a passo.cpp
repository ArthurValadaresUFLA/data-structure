/*
# Construção de MinHeap passo a passo


Implemente uma classe MinHeap que tem um construtor que recebe um vetor de elementos. Durante a criação do MinHeap, alguns elementos deverão ser reposicionados para que passem a ter as propriedades de um min heap. O construtor (ou método usado no construtor) deverá escrever passo a passo como fica o armazenamento após a correção descendo de cada posição.

Note que não é para escrever os valores do heap após cada troca, os valores do heap devem ser escritos após todas as trocas (zero ou mais) realizadas para a correção de uma posição.

Implemente a função principal que cria um heap a partir do vetor.

### Entradas

```
1. A quantidade de elementos a serem lidos.
2. Os elementos (números inteiros) a serem armazenados no heap.
```

### Saídas

```
Para cada posição a ser corrigida:

1. A posição, seguida de dois pontos;
2. Todos os elementos armazenados após a reorganização iniciada na posição em questão.

Note a ausência de espaço antes do dois pontos e a presença do espaço depois, como em qualquer sinal de pontuação.
```

### Exemplo de Entrada

```
6
9 8 7 5 -1 -3
```

### Exemplo de Saída

```
2: 9 8 -3 5 -1 7 
1: 9 -1 -3 5 8 7 
0: -3 -1 7 5 8 9
```
*/

#include <iostream>
#include <stdexcept>
#include <utility>
#include <cstring>

typedef int Dado;

class MinHeap{

    private:
        Dado* heap;
        const unsigned int capacidade;
        unsigned int tamanho;
        int pai(int i);
        int filhoEsquerdo(int i);
        int filhoDireito(int i);
        void arruma();
        void corrigeSubindo(int i);
        void corrigeDescendo(int i);
        bool vazia();
        bool cheia();
        void mostraArruma(int index);
    public:
        MinHeap(int capacidade = 10); // construtor cria heap vazia
        MinHeap(Dado *arr, int tamanhoArr); // construtor cria heap a partir de array já preenchido
        ~MinHeap();
        Dado espiaRaiz();
        Dado removeRaiz();
        void insere(const Dado &d);
        void imprime(); //fins didáticos (configura quebra de estrutura)
        unsigned int getTamanho();
        unsigned int getCapacidade();
};

MinHeap::MinHeap(int capacidade) : capacidade(capacidade){

    heap = new Dado[capacidade];
    tamanho = 0;
}

MinHeap::MinHeap(Dado *arr, int tamanhoArr) : capacidade(tamanhoArr){

    tamanho = tamanhoArr;
    heap = new Dado[tamanhoArr];
    std::memcpy(heap, arr, sizeof(Dado) * tamanhoArr);
    arruma();
}

MinHeap::~MinHeap(){
    delete[] heap;
}

void MinHeap::arruma(){
    for(int i{int(tamanho/2 - 1)}; i>=0; i--){ // metade para cima (apenas nós não-folhas) até a raiz
        corrigeDescendo(i);
        mostraArruma(i);
    }
}

void MinHeap::mostraArruma(int index){

    std::cout << index << ": ";

    for(int i{0}; i < int(tamanho); i++)
        std::cout << heap[i] << " ";
    std::cout << "\n";

}

int MinHeap::pai(int i){
    return (i - 1)/2;
}

int MinHeap::filhoEsquerdo(int i){
    return i*2 + 1;
}

int MinHeap::filhoDireito(int i){
    return i*2 + 2;
}

void MinHeap::corrigeDescendo(int i){

    int esquerdo{filhoEsquerdo(i)}, direito{filhoDireito(i)};
    int indexMenor = i;

    // verifica se algum dos filhos é menor que o pai e pega o menor em caso positivo
    if(esquerdo < int(tamanho) && heap[esquerdo] < heap[indexMenor])
        indexMenor = esquerdo;
    if(direito < int(tamanho) && heap[direito] < heap[indexMenor])
        indexMenor = direito;
    
    if(indexMenor != i){
        std::swap(heap[i], heap[indexMenor]); // troca pai com menor dos filhos
        corrigeDescendo(indexMenor); // verifica pai com seus novos filhos
    }

}

void MinHeap::corrigeSubindo(int i){
    
    int indexPai{pai(i)};

    // verifica se o filho é menor que o pai
    if(heap[i] < heap[indexPai]){
        std::swap(heap[i], heap[indexPai]);
        corrigeSubindo(indexPai);
    }
}

bool MinHeap::vazia(){
    return !bool(tamanho);
}

bool MinHeap::cheia(){
    return (tamanho == capacidade);
}

Dado MinHeap::espiaRaiz(){
    if(vazia()) 
        throw std::runtime_error("Erro: Heap Vazia.\n");
    
    return heap[0];
}

Dado MinHeap::removeRaiz(){

    if(vazia()) 
        throw std::runtime_error("Erro: Heap Vazia.\n");
    
    Dado temp = heap[0];

    std::swap(heap[0], heap[--tamanho]);
    corrigeDescendo(0);

    return temp;
    

}

void MinHeap::insere(const Dado &d){

    if(cheia()) 
        throw std::runtime_error("Erro: Heap Cheia.\n");
    
    heap[tamanho++] = d;
    corrigeSubindo(tamanho - 1);

}

void MinHeap::imprime(){
    for(int i{0}; i< int(tamanho); i++)
        std::cout << heap[i] << " ";

    std::cout << "\n";
}

unsigned int MinHeap::getTamanho(){
    return tamanho;
}

unsigned int MinHeap::getCapacidade(){
    return capacidade;
}


int main(){

    int n, *arr{nullptr};
    std::cin >> n;
    arr = new int[n];

    for(int i{0}; i<n; i++)
        std::cin >> arr[i];
    
    MinHeap heap(arr, n);

    delete[] arr;

    return 0;
}