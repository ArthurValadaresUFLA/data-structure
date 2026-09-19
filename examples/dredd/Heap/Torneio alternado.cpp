/*
# Torneio alternado


Um torneio é uma árvore estritamente binária na qual cada nó não folha contém uma cópia do maior elemento entre seus dois filhos. O conteúdo das folhas de um torneio determina o conteúdo de todos os seus nós. Um torneio com n folhas representa um conjunto de n elementos.

Implemente um torneio utilizando uma estratégia semelhante a um Heap. Entretanto, a cada etapa, a condição de vitória (maior elemento ou menor elemento) é alternada. A primeira etapa sempre começa com a condição de vitória sendo o maior elemento, a segunda é o menor valor, a terceira volta a ser o maior, e continua sucessivamente.

Note que normalmente um torneio é uma árvore estritamente binária, cheia. Como, neste problema, temos que o tamanho da entrada pode não ser uma potência de 2, será necessário fazer ajustes para trabalhar com o que costumamos chamar de torneio incompleto. Uma das abordagens possíveis é apresentada nos slides e vídeo do assunto, verifique.

Faça um programa que funcione como um torneio alternado, onde a cada etapa, alterna a condição de vitória (maior ou menor). A primeira etapa sempre começa com a condição de vitória sendo o maior valor, a segunda é o menor valor, a terceira volta a ser o maior, e continua nessa ordem.

A entrada deve conter o número de participantes seguido dos participantes. A saída apresenta o participante campeão do torneio.

### Entradas

```
1. Quantidade de participantes
2. Identificação dos participantes
```

### Saídas

```
1. Campeão do torneio
```

### Exemplo de Entrada

```
8
2 7 4 1 3 9 6 8
```

### Exemplo de Saída

```
8
```

### Exemplo de Entrada

```
13
11 5 3 4 2 15 7 9 10 8 12 6 16
```

### Exemplo de Saída

```
9
```

*/

#include <iostream>
#include <stdexcept>
#include <cstring>

typedef int Dado;
const int INVALIDO{-1};

class Torneio{
    private:
        Dado *heap;
        int tamanho, capacidade, indexDados;
        int pai(int i);
        int filhoEsquerdo(int i);
        int filhoDireito(int i);
        void arruma();
        void copiaMaior(int i);
        void copiaSubindo(int i);
        bool cheio();
        bool vazio();
        int fatorComparacao{1};
        int potenciaDois;
    public:
        Torneio(int numFolhas = 9);
        Torneio(Dado *arrDados, int tamanhoArr);
        ~Torneio();
        void insere(const Dado &d);
        void imprime();
        Dado campeao();
};

Torneio::Torneio(Dado *arrDados, int tamanhoArr){

    capacidade = 1;

    while(capacidade < tamanhoArr) // numero de possíveis pais é a primeira potência de 2 maior q o numero de dados - 1
        capacidade *= 2;
    potenciaDois = capacidade;

    capacidade = capacidade - 1 + tamanhoArr; // numero de possiveis pais + numero de dados (folhas da heap)

    heap = new Dado[capacidade];
    indexDados = capacidade - tamanhoArr; // index de inicio dos nós folhas

    std::memcpy(heap + indexDados, arrDados, tamanhoArr * sizeof(Dado));

    tamanho = tamanhoArr;
    arruma(); // criar o tournament
}

Torneio::Torneio(int numFolhas){

    capacidade = 1;

    while(capacidade < numFolhas) // numero de possíveis pais é a primeira potência de 2 maior q o numero de folhas - 1
        capacidade *= 2;

    capacidade = capacidade - 1 + numFolhas; // numero de possiveis pais + numero de folhas

    heap = new Dado[capacidade];
    indexDados = capacidade - numFolhas; // index de inicio dos nós folhas

    tamanho = 0;

    for(int i{0}; i<capacidade; i++)
        heap[i] = INVALIDO;
}

Torneio::~Torneio(){
    delete[] heap;
}

int Torneio::pai(int i){
    return (i-1)/2;
}

int Torneio::filhoEsquerdo(int i){
    return 2*i + 1;
}

int Torneio::filhoDireito(int i){
    return 2*i + 2;
}

void Torneio::arruma(){

    int numPais{potenciaDois/2}, contador{0};

    // realiza o duelo entre os elementos
    for(int i{indexDados - 1}; i>= 0; i--){

        copiaMaior(i);

        contador++;
        if(contador == numPais){
            contador = 0;
            numPais /= 2;
            fatorComparacao = -1 * fatorComparacao;
        }
    }
}

void Torneio::copiaMaior(int i){

    int esq{filhoEsquerdo(i)}, dir{filhoDireito(i)};
    int indexMaior;

    if(esq < capacidade){

        if(dir < capacidade && heap[dir] != INVALIDO && (heap[dir] * fatorComparacao) > (heap[esq] * fatorComparacao))
            indexMaior = dir;
        else
            indexMaior = esq;
        
        heap[i] = heap[indexMaior];
        

    }else{
        heap[i] = INVALIDO; // pai não possui filhos
    }
}

void Torneio::copiaSubindo(int i){
    int indexPai{pai(i)};

    // verifica se elemento é maior que pai, em caso positivo substitui a cópia
    if(heap[i] > heap[indexPai]){
        heap[indexPai] = heap[i];
        copiaSubindo(indexPai);
    }
}

void Torneio::insere(const Dado &d){

    if(cheio())
        throw std::runtime_error("Erro: Heap cheia.\n");
    
    heap[indexDados + tamanho] = d;
    copiaSubindo(indexDados + tamanho);
    tamanho++;

}

bool Torneio::cheio(){
    return (indexDados + tamanho == capacidade);
}

bool Torneio::vazio(){
    return !bool(tamanho);
}

Dado Torneio::campeao(){
    
    if(vazio())
        throw std::runtime_error("Erro: Heap vazia.\n");
    
    return heap[0];
}

void Torneio::imprime(){

    for(int i{0}; i<capacidade; i++)
        std::cout << heap[i] << " ";
    
    std::cout << "\n";
}

int main(){

    int n;
    std::cin >> n;

    int *arr = new int[n];
    for(int i{0}; i<n; i++)
        std::cin >> arr[i];

    Torneio torneio(arr, n);

    std::cout << torneio.campeao() << "\n";

    delete[] arr;

    return 0;
}