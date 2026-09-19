/*
# Gerar números binários utilizando uma fila


Implemente uma estrutura do tipo fila com as operações básicas de inserção e remoção. Com a estrutura implementada, faça um programa que utilize a fila para gerar números binários de 1 a N. O trecho a seguir dá uma dica de como resolver o problema:

```
inicio = "1"
enfileira (inicio) // fila = (1)
laço
	enfileira(inicio + “0”) // fila = (1, 10)
	enfileira(inicio + “1”) // fila(1, 10, 11)
	elemento = desenfileira() 
fim  do laço
```

Note que como cada passo do laço enfileira por padrão dois elementos, você precisará inserir um controle adicional no laço ou na impressão para evitar enfileirar um elemento a mais, dependendo da entrada.

### Entradas

```
1. Número inteiro positivo representando N
```

### Saídas

```
1. Números binários gerados de 1 a N
```

### Exemplo de Entrada

```
6
```

### Exemplo de Saída

```
1 10 11 100 101 110
```
*/

#include <iostream>
#include <stdexcept>

typedef std::string Dado;

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

int main(){

    FilaEncadeada fila;
    int n;
    Dado base{"1"};
    Dado numA, numB;

    std::cin >> n;

    std::cout << base << " ";

    for(int i{0}; i<(n/2 - 1); i++){

        numA = base + "0";
        numB = base + "1";

        std::cout << numA << " ";
        std::cout << numB << " ";

        fila.enfileira(numA);
        fila.enfileira(numB);

        base = fila.desenfileira();

    }

    if(n % 2){ // impar
        std::cout << base + "0" << " ";
        std::cout << base + "1" << "\n";
    }else // par
        std::cout << base + "0" << "\n";

    return 0;
}