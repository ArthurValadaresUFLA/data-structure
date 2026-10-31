# Pilhas

## O que é?

**Pilhas** são estruturas de dados nas quais os elementos pertencentes são ordenados de forma que o
último elemento a ser inserido se posiciona como o primeiro a ser retirado — política *Last-In,
First-Out*, LIFO —, tendo em vista que a definição de pilha restringe que as inserções e remoções —
denominadas, na literatura, "push" e "pop" —, sejam feitas sempre pelo **topo**.

A fim de facilitar o entendimento, podemos fazer uma analogia com uma pilha de livros, por exemplo.
À medida em que você vai estudando, fazendo a leitura das referências bibliográficas referentes à
matéria em questão, você acaba dispondo os livros lidos numa pilha, um em cima do outro. Em certo
momento, o livro que lê referencia um que você já leu e que está na pilha; nesse caso, por não se
lembrar especificamente do trecho, você precisa relê-lo, e, para tal, tem de retirar cada livro que
está acima do requerido. Você não pode retirar os livros por baixo da pilha, pelo lado — corre-se o
risco de derrubar tudo —, retirar pelo *lado* seria uma quebra do encapsulamento da estrutura de
dados.

## Pilhas em Arranjo

Pilhas em arranjo se assemelham muito às [filas em arranjo](./Fila.md#filas-em-arranjo), exceto que
se trata de apenas uma extremidade de entrada e saída, isto é, há duas variáveis principais numa
pilha em arranjo: o vetor alocado dinamicamente e um atributo indicando o **topo**. À medida em que
os elementos são inseridos na pilha, o topo é incrementado; analogamente, quando os elementos são
retirados, o topo é decrementado. Se, na pilha, denotada por *P*, o topo igualar o tamanho, isto é,
*P.topo = P.tamanho*, a pilha está cheia; ao passo que, se *P.topo = 0*, a pilha está vazia
(considerando-se aqui a convenção de que o topo aponta para a **próxima posição livre**, e não para
o último elemento inserido).

```cpp
struct PilhaArranjo {
    int* dados;
    int topo;     // aponta para a próxima posição livre
    int tamanho;  // capacidade máxima do vetor

    PilhaArranjo(int tamanho) : topo(0), tamanho(tamanho) {
        dados = new int[tamanho];
    }
};

bool vazia(const PilhaArranjo& p) {
    return p.topo == 0;
}

bool cheia(const PilhaArranjo& p) {
    return p.topo == p.tamanho;
}

void push(PilhaArranjo& p, int valor) {
    if (cheia(p)) return; // ou realoca o vetor para um tamanho maior

    p.dados[p.topo] = valor;
    p.topo++;
}

int pop(PilhaArranjo& p) {
    p.topo--;
    return p.dados[p.topo];
}
```

## Pilhas Encadeadas

As pilhas encadeadas contêm um ou dois atributos: o ponteiro apontando para o topo do encadeamento
e, opcionalmente, a quantidade de elementos na pilha. Uma pilha pode ser duplamente encadeada ou
unicamente encadeada, isso diz respeito aos atributos de cada um dos nós contidos numa pilha, isto
é, os elos que constituem a corrente — a pilha em si, nessa analogia. Um nó duplamente encadeado é
aquele que tanto armazena um ponteiro indicando o próximo nó quanto o nó predecessor, ao passo que o
nó unicamente encadeado indica somente o nó subsequente.

```cpp
struct No {
    int valor;
    No* proximo; // aponta para o nó imediatamente abaixo na pilha

    No(int valor) : valor(valor), proximo(nullptr) {}
};

struct PilhaEncadeada {
    No* topo = nullptr;
};
```

O atributo que indica o tamanho da pilha tem de ser atualizado a cada inserção ou remoção, a fim de
manter a consistência com os elementos presentes na pilha. Se o ponteiro que aponta para o topo da
pilha é nulo, a pilha está vazia; se não, há dados dentro dela.

No processo de inserção de elementos numa pilha, o valor a ser inserido deve ser encapsulado num nó,
e o seu antecessor deve ser definido como aquele que, até então, estava no topo — e, caso seja uma
pilha duplamente encadeada, deve-se, também, definir o sucessor do antigo topo como sendo o novo nó
criado. Feito isso, é necessário atualizar o ponteiro que aponta para o topo, passando a indicar o
novo nó.

```cpp
void push(PilhaEncadeada& p, int valor) {
    No* novo = new No(valor);
    novo->proximo = p.topo;
    p.topo = novo;
}
```

O processo de remoção é análogo: o ponteiro para o topo passa a apontar para aquele que está abaixo,
o valor é desencapsulado do nó removido, o nó é deletado da memória e, por fim, o valor é retornado.

```cpp
int pop(PilhaEncadeada& p) {
    No* antigoTopo = p.topo;
    int valor = antigoTopo->valor;

    p.topo = antigoTopo->proximo;
    delete antigoTopo;

    return valor;
}

bool vazia(const PilhaEncadeada& p) {
    return p.topo == nullptr;
}
```

## Vantagens e desvantagens

### Arranjo

- Leitura e escrita mais rápidas;
- Tamanho limitado e de aumento computacionalmente custoso, exigindo realocação e cópia de todos os
  elementos;
- Gestão mais fácil;
- O tempo de leitura de um elemento é constante;

### Encadeamento

- Leitura e escrita mais lentas, devido à alocação dinâmica de cada nó;
- Tamanho limitado somente pela quantidade de memória disponível para o programa;
- Mais difícil de ser gerenciada;
- Como o acesso a um elemento que não seja o topo é sempre linear, essa desvantagem, na prática,
  raramente afeta o uso de uma pilha, já que suas operações características (push e pop) só atuam
  sobre o topo;
