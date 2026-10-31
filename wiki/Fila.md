# Filas

## O que é?

**Filas** são estruturas de dados nas quais os elementos existentes são ordenados conforme o momento
de entrada, mantendo sempre a mesma ordem, seguindo, portanto, uma *política* FIFO, um acrônimo em
inglês para First-In, First-Out, ou seja, o primeiro a entrar é o primeiro a sair.

É importante destacar que existem filas nas quais fatores diferentes dos relacionados ao momento de
entrada são considerados, a exemplo das filas prioritárias. Apesar do que pode parecer, filas
prioritárias não ferem o *encapsulamento*, visto que os dados são somente acessíveis pelos métodos
apropriados.

Filas possuem dois métodos característicos: **Enqueue**, enfileirar, e **Dequeue**, desenfileirar.
Consistem, basicamente, em adicionar um elemento no final e remover um elemento no início,
respectivamente. A fim de auxiliar a compreensão, uma fila não só se assemelha como, conforme a
definição, pode ser exemplificada pela fila experienciada, por exemplo, num banco ou supermercado,
onde uma pessoa, mediante o momento de entrada na fila, adquire uma posição que vai sendo
decrementada conforme os indivíduos de posições inferiores são chamados, isto é, à medida com que as
pessoas são desenfileiradas.

Uma dúvida surge, por exemplo, ao analisar um guichê de hospital: geralmente, você passa por uma
triagem que possui uma fila simples; ao passar por essa triagem, você é encaminhado para um setor no
qual há uma fila, muito provavelmente, prioritária, na qual o atendimento das pessoas considera a
idade, o grupo de risco, o plano de saúde, a urgência e o tempo de espera total — isso constitui uma
fila prioritária. Não se preocupe com isso, no momento; foge ao escopo do curso.

## Tipos de filas

No que tange à implementação de filas, há dois tipos principais abordados ao longo do curso:

- Encadeada;
- Em arranjo;

A seguir, segue a diferença entre elas, aplicações, vantagens e desvantagens.

### Filas Encadeadas

Filas encadeadas constituem uma estrutura de dados cujos elementos são encapsulados em classes que
representam **nós**; o conjunto de nós forma uma fila, desde que siga a *política* **FIFO**.

```cpp
struct No {
    int valor;
    No* proximo;

    No(int valor) : valor(valor), proximo(nullptr) {}
};

struct FilaEncadeada {
    No* inicio = nullptr;
    No* fim = nullptr;
};
```

A fim de auxiliar a compreensão, uma fila e os seus respectivos nós podem ser entendidos como uma
corrente, isto é, cada elemento de uma corrente, cada elo, constitui um nó, ao passo que o conjunto
de nós encadeados, ou seja, a corrente, é entendido como a fila em si. A fim de ter acesso a cada
elo da corrente é necessário tê-la, isto é, segurá-la por algum ponto: pelo início, fim ou ambos.

A fim de acelerar o processo de inserção e remoção — leia-se: enfileiramento e desenfileiramento —,
armazena-se uma referência para ambas as extremidades, a fim de diminuir o tempo necessário para
esses métodos característicos e, muito provavelmente, os mais utilizados.

```cpp
void enqueue(FilaEncadeada& f, int valor) {
    No* novo = new No(valor);

    if (f.inicio == nullptr) { // fila vazia
        f.inicio = f.fim = novo;
        return;
    }

    f.fim->proximo = novo;
    f.fim = novo;
}

int dequeue(FilaEncadeada& f) {
    No* antigoInicio = f.inicio;
    int valor = antigoInicio->valor;

    f.inicio = antigoInicio->proximo;
    if (f.inicio == nullptr) {
        f.fim = nullptr; // a fila ficou vazia
    }

    delete antigoInicio;
    return valor;
}
```

Uma fila encadeada, assim como, por exemplo, uma lista ou pilha, pode ter nós singularmente ou
duplamente encadeados, isto é, armazenar tanto uma referência para o nó subsequente quanto para o nó
precedente.

No processo de inserção de um elemento, logicamente no final da fila, se o ponteiro para o último nó
é nulo, assim como o ponteiro para o primeiro nó, a fila está vazia, e o valor a ser adicionado tem
de ser encapsulado num nó que, quando criado, será tanto o objeto apontado pelo ponteiro de início
quanto o de fim. Se os ponteiros para o fim e para o início não apontam para nulo, o último nó tem
de apontar para o novo nó criado — aquele que encapsula o elemento — como o seu subsequente;
ademais, se o nó for duplamente encadeado, o novo nó deve apontar para o antigo último nó como sendo
o seu predecessor. O ponteiro para o último deve ser atualizado, apontando agora para o novo nó,
devidamente encadeado. Se o ponteiro para o primeiro elemento ou para o último apontar para nulo, e
o outro não, há uma inconsistência na fila.

No processo de remoção de um elemento de uma fila, o primeiro elemento é acessado por meio do
ponteiro de início. Se os nós forem duplamente encadeados, o nó subsequente ao primeiro, se existir,
deverá ter definido como o seu precedente o valor nulo. O ponteiro de início deve passar a apontar
para o subsequente daquele que, até então, era o primeiro; o valor deve ser desencapsulado, ou seja,
retirado do nó, o nó deve ser deletado e o valor, retornado. Se o primeiro for também o último, ao
ser removido, ambos os ponteiros, de início e fim, devem apontar para nulo.

### Filas em Arranjo

#### Arranjo Linear

Uma fila pode ser disposta ao longo de um vetor dinamicamente alocado; a fila então passa a ter, no
mínimo, três atributos: o ponteiro do vetor dinamicamente alocado, o início e o fim da fila.

```cpp
struct FilaArranjo {
    int* dados;
    int inicio;
    int fim;
    int tamanho; // capacidade máxima do vetor

    FilaArranjo(int tamanho) : inicio(0), fim(0), tamanho(tamanho) {
        dados = new int[tamanho];
    }
};

void enqueue(FilaArranjo& q, int valor) {
    q.dados[q.fim] = valor;
    q.fim++;
}

int dequeue(FilaArranjo& q) {
    int valor = q.dados[q.inicio];
    q.inicio++;
    return valor;
}
```

À medida que os elementos são enfileirados, o fim se desloca para a direita e, analogamente, à
medida que os elementos são desenfileirados, o início se desloca também para a direita. Como a fila
não é circular — veremos a definição mais adiante —, quando o atributo *fim* da fila, denotada por
*Q*, se iguala ao tamanho, isto é, *Q.fim = Q.tamanho*, a fila está cheia; nenhum elemento pode ser
adicionado a ela sem que seja necessário fazer um processo de realocação de memória para um vetor de
tamanho igual, menor — removendo aqueles que precedem o início —, ou maior. Se o início iguala o
fim, a fila está vazia; se não, a fila tem pelo menos um elemento. É importante destacar que, no
contexto de arranjo, os atributos de início e de fim podem ser tanto inteiros indicando os índices
quanto ponteiros apontando para os endereços de memória correspondentes.

Uma fila em arranjo pode ter um atributo opcional: **tamanho** (aqui, no sentido de quantidade de
elementos, e não de capacidade), usado para armazenar a quantidade de elementos presentes na fila;
deve ser mantido, isto é, o seu valor deve ser alterado conforme se fazem inserções e remoções na
fila, incrementando e decrementando, respectivamente.

#### Arranjo Circular

Um arranjo circular se assemelha muito ao linear, exceto que, quando o fim se iguala ao tamanho, ao
ser incrementado, ele volta para o início — usa-se o *(mod n)* para tal —, o que resolve o problema
do arranjo linear de desperdiçar as posições já desenfileiradas no começo do vetor.

```cpp
struct FilaCircular {
    int* dados;
    int inicio;
    int fim;
    int quantidade; // número de elementos atualmente na fila
    int tamanho;    // capacidade máxima do vetor

    FilaCircular(int tamanho) : inicio(0), fim(0), quantidade(0), tamanho(tamanho) {
        dados = new int[tamanho];
    }
};

bool cheia(const FilaCircular& q) {
    return q.quantidade == q.tamanho;
}

bool vazia(const FilaCircular& q) {
    return q.quantidade == 0;
}

void enqueue(FilaCircular& q, int valor) {
    if (cheia(q)) return;

    q.dados[q.fim] = valor;
    q.fim = (q.fim + 1) % q.tamanho;
    q.quantidade++;
}

int dequeue(FilaCircular& q) {
    int valor = q.dados[q.inicio];
    q.inicio = (q.inicio + 1) % q.tamanho;
    q.quantidade--;
    return valor;
}
```

Essa circularidade traz mais algumas restrições, tais quais: a fila *não completou uma volta*, logo,
se *Q.fim = Q.inicio* e a fila não está vazia, ela está cheia. É justamente por conta dessa
ambiguidade entre "fila cheia" e "fila vazia" quando *início = fim* que, na prática, costuma-se
manter um contador explícito de elementos — como o atributo *quantidade* do exemplo acima —, em vez
de depender apenas da comparação entre início e fim.

## Vantagens e desvantagens

### Arranjo

- Leitura e escrita mais rápidas;
- Tamanho limitado e de aumento computacionalmente custoso;
- Gestão mais fácil;
- O tempo de leitura de um elemento é constante;

### Encadeamento

- Leitura e escrita mais lentas;
- Tamanho limitado somente pela quantidade de memória alocada ao programa;
- Mais difícil de ser gerenciada;
- Tempo de leitura de um elemento é linear, isto é, para ler o 3º elemento é necessário ler todos os
  que o precedem, mediante o ponto de escolha para o início da iteração: início ou fim da fila;
