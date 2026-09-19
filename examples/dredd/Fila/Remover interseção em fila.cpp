/*
# Remover interseção em fila


Dadas duas filas F1 e F2, implemente o método que remove os elementos de F2, presentes em F1. F1 deve estar disponível após a remoção dos elementos de F2 para outras operações. As propriedades de fila devem ser estritamente respeitadas, ou seja: não é permitido o acesso aleatório aos elementos da fila.A fila deve ser implementada utilizando encadeamento.

### Entradas

```
1. Número de elementos a serem inseridos em F1.
2. Elementos de F1 em ordem de inserção (inserção no fim da fila).
3. Número de elementos a serem inseridos em F2.
4. Elementos de F2 em ordem de inserção (inserção no fim da fila).
```

### Saídas

```
1. Elementos restantes em F1 após a remoção.
```

### Exemplo de Entrada

```
11
4 6 9 10 1 9 2 13 7 3 5
4
9 2 7 3
```

### Exemplo de Saída

```
4 6 10 1 13 5
```
*/

#include <iostream>
#include <stdexcept>

typedef int Dado;

class Noh{

    //permitir acesso da queue aos atributos privados do Noh
    friend class FilaEncadeada;

    // noh armazena dado e ponteiro para o próximo
    private:
        Noh* proximo;
        Dado dado;
    public:
        Noh(const Dado &d) : dado(d), proximo(nullptr) {}
};

class FilaEncadeada{
    private:
        Noh *inicio, *fim;
        unsigned int tamanho;
    public:
        FilaEncadeada();
        ~FilaEncadeada();
        void enfileira(const Dado &d);
        Dado desenfileira();
        void limparTudo();
        unsigned int getTamanho();
        bool vazia();
        Dado espiarInicio();
        void removeIntersecao(FilaEncadeada &filaB);
};

FilaEncadeada::FilaEncadeada(){
    inicio = fim = nullptr;
    tamanho = 0;
}

FilaEncadeada::~FilaEncadeada(){
    limparTudo();
}

void FilaEncadeada::limparTudo(){
    while(!vazia())
        desenfileira();
}

void FilaEncadeada::enfileira(const Dado &d){

    Noh *novo = new Noh(d);

    if(vazia())
        inicio = novo;
    else
        fim->proximo = novo; // proximo do antigo fim é novo
    
    fim = novo; // fim passa a ser o novo elemento

    tamanho++;

}

Dado FilaEncadeada::desenfileira(){

    if(vazia())
        throw std::runtime_error("Erro: Fila Vazia!");

    Noh *aux = inicio;
    Dado temp = inicio->dado;

    inicio = inicio->proximo;
    delete aux;
    tamanho--;

    if(vazia())
        fim = nullptr;

    return temp;

}

unsigned int FilaEncadeada::getTamanho(){
    return tamanho;
}

bool FilaEncadeada::vazia(){
    return !bool(inicio);
}

Dado FilaEncadeada::espiarInicio(){

    if(vazia())
        throw std::runtime_error("Erro: Fila Vazia!");

    return inicio->dado;
}

void FilaEncadeada::removeIntersecao(FilaEncadeada &filaB){

    int tamA{getTamanho()}, tamB{filaB.getTamanho()};
    int j;
    Dado auxA, auxB;
    bool naoEncontrou;

    for(int i{0}; i<tamA; i++){

        j = 0;
        auxA = desenfileira();
        naoEncontrou = true;

        while(j < tamB && naoEncontrou){

            auxB = filaB.desenfileira();

            if(auxB == auxA)
                naoEncontrou = false;

            filaB.enfileira(auxB);
            j++;
        }

        if(naoEncontrou)
            enfileira(auxA);

    }

}

void leituraFila(int tam, FilaEncadeada &fila){

    int num;

    for(int i{0}; i<tam; i++){
        std::cin >> num;
        fila.enfileira(num);
    }

}

int main(){

    FilaEncadeada filaA, filaB;

    int n;

    std::cin >> n;
    leituraFila(n, filaA);

    std::cin >> n;
    leituraFila(n, filaB);

    filaA.removeIntersecao(filaB);
    int novoTam{filaA.getTamanho()};

    for(int i{0}; i<novoTam; i++)
        std::cout << filaA.desenfileira() << " ";

    return 0;
}
