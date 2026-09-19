/*
# Corretude de parênteses (v2)


Faça um programa que lê uma linha de texto e verifica se todo parênteses tem um correspondente. Assuma que cada sinal de "fecha parênteses" fecha o último "abre parênteses".

Caso não existam parênteses correspondentes em todos os casos, o programa deve escrever a posição do erro. A posição do primeiro caractere é zero. Se todos os parênteses têm correspondentes, o programa deverá escrever "correto" (letras minúsculas). A posição do erro no caso de um "fecha parênteses" sem correspondente é a dele mesmo, pois não é preciso olhar o resto do texto para saber que há erro. A posição do erro no caso de um "abre parênteses" sem correspondente é a do último "abre parênteses" visto, pois só é possível saber que ele não tem correspondente ao final do texto.

Este é um exercício de solução de problema usando pilha. A pilha deve ser parte importante da solução. Faça um programa utilizando somente a estrutura de dado pilha, respeitando todas as suas propriedades e não utilizando a STL.

### Entradas

```
1. Uma linha de texto (não mais do que 254 caracteres).
```

### Saídas

```
1. A palavra "correto" se todos tiverem correspondentes ou então a posição do erro.
```

### Exemplo de Entrada

```
func(x, (y+3)*4)
```

### Exemplo de Saída

```
correto
```

### Exemplo de Entrada

```
(idw ( dpq() sho
```

### Exemplo de Saída

```
5
```

### Exemplo de Entrada

```
(12 + 3) * 4 - 2)
```

### Exemplo de Saída

```
16
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

int main(){

    PilhaEncadeada pilha;
    
    std::string txt;
    std::getline(std::cin, txt);

    bool txtValido{true};
    int i{0};

    while(txtValido && i < int(txt.length()) ){

         if(txt[i] == '(')
            pilha.empilhar(i);
        else if(txt[i] == ')'){

            if(pilha.vazia())
                txtValido = false;
            else
                pilha.desempilhar();

        }

        i++;
    }

    if(txtValido){

        if(pilha.vazia())
            std::cout << "correto\n";
        else
            std::cout << pilha.espiarTopo() << "\n";

    }else{

        std::cout << (i - 1) << "\n";;

    }

    return 0;
}