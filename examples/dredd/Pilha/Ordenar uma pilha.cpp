/*
# Ordenar uma pilha 


Implemente um estrutura de dados do tipo pilha com as operações de empilhar e desempilhar. Adicione um método que, utilizando uma pilha auxiliar, faça a ordenação crescente da pilha original, com o menor elemento no topo da pilha. Nenhuma outra estrutura pode ser utilizada além da pilha auxiliar.

### Entradas

```
1. Quantidade de elementos a serem armazenados na pilha
2. Elementos da pilha
```

### Saídas

```
1. Elementos da pilha ordenados
```

### Exemplo de Entrada

```
10
3 8 5 10 2 0 4 11 21 7
```

### Exemplo de Saída

```
0 2 3 4 5 7 8 10 11 21
```

### Exemplo de Entrada

```
15
3 8 5 10 -2 0 14 11 21 75 6 34 -1 9 -5
```

### Exemplo de Saída

```
-5 -2 -1 0 3 5 6 8 9 10 11 14 21 34 75
```
*/

#include <iostream>
#include <stdexcept>

typedef int Dado;

class Noh{
    
    //permite o acesso da stack aos atributos privados do noh
    friend class PilhaEncadeada;

    public:
        Noh(const Dado &d) : dado(d), proximo(nullptr) {}
    
    // noh armazena um dado e um ponteiro para o proximo elemento
    private:
        Dado dado;
        Noh* proximo;
};

class PilhaEncadeada{

    public:
        PilhaEncadeada();
        ~PilhaEncadeada();
        Dado desempilhar();
        void empilhar(const Dado &d);
        Dado espiarTopo();
        bool vazia();
        void limparTudo();
        unsigned int getTamanho();
        void ordenarPilha();

    // stack armazena ponteiro para o topo e o tamanho da mesma
    private:
        Noh* topo;
        unsigned int tamanho;
};

PilhaEncadeada::PilhaEncadeada(){
    tamanho = 0;
    topo = nullptr;
}

PilhaEncadeada::~PilhaEncadeada(){
    limparTudo();
}

void PilhaEncadeada::limparTudo(){
    
    // apaga todos nós alocados dinamicamente
    while(!vazia())
        desempilhar();
}

void PilhaEncadeada::empilhar(const Dado &d){

    // cria novo nó, que passa a ser o topo da stack

    Noh* novo = new Noh(d);
    novo->proximo = topo;
    topo = novo;
    
    tamanho++;
}

Dado PilhaEncadeada::desempilhar(){

    if(vazia())
        throw std::runtime_error("Erro: stack vazia!");

    // remove o elemento do topo da stack, e o novo topo passa a ser o proximo

    Noh *aux = topo;
    Dado temp = topo->dado;

    topo = topo->proximo;
    delete aux;

    tamanho--;

    return temp;

}

Dado PilhaEncadeada::espiarTopo(){
    if(vazia())
        throw std::runtime_error("Erro: stack vazia!");

    return topo->dado;
}

bool PilhaEncadeada::vazia(){
    return !bool(topo);
}

unsigned int PilhaEncadeada::getTamanho(){
    return tamanho;
}

void PilhaEncadeada::ordenarPilha(){

    PilhaEncadeada pilhaAux;
    Dado dadoAux;

    while(!this->vazia()){

        dadoAux = this->desempilhar();

        while(!pilhaAux.vazia() && dadoAux > pilhaAux.espiarTopo())
            this->empilhar(pilhaAux.desempilhar());

        pilhaAux.empilhar(dadoAux);

    }

    this->topo = pilhaAux.topo;
    this->tamanho = pilhaAux.tamanho;

    pilhaAux.topo = nullptr;
    pilhaAux.tamanho = 0;

}

int main(){

    PilhaEncadeada pilha;
    
    int n, num;
    std::cin >> n;

    for(int i{0}; i<n; i++){
        std::cin >> num;
        pilha.empilhar(num);
    }

    pilha.ordenarPilha();

    for(int i{0}; i<n; i++)
        std::cout << pilha.desempilhar() << " "; 

    return 0;
}