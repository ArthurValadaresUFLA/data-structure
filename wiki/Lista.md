# Listas

## O que é?

Listas são estruturas de dados nas quais as informações são armazenadas de forma linear, em objetos
constituintes denominados, frequentemente, de **nós**.

Há dois tipos de listas, no que tange à estrutura de cada um dos nós constituintes:

- Simplesmente encadeada;
- Duplamente encadeada;

Um nó simplesmente encadeado é aquele que, além do dado e de informações *satélites*, possui um
ponteiro apontando para o próximo elemento; ao passo que nós duplamente encadeados são aqueles que
têm tanto um ponteiro para o próximo elemento quanto para o antecessor. Se o ponteiro para o
anterior é nulo, o elemento é o primeiro da lista. Se o ponteiro para o próximo é nulo, ele é o
último da lista.

O processo de inserção, busca e remoção depende da abordagem adotada: a inserção no início e, se
houver um ponteiro para o fim da mesma forma que há para o início, tem tempo de execução constante,
isto é, $O(1)$. Para a inserção numa posição *k* qualquer, a complexidade é linear no pior dos
cenários, $O(n)$, isto é, no pior dos casos é necessário percorrer cada um dos elementos da lista
antes de fazer a inserção.

Tendo em vista que, da mesma forma que a inserção, na remoção é necessário percorrer, no pior dos
casos, toda a lista a fim de achar o nó cujo valor armazenado corresponde àquele que deve ser
removido, a complexidade também é $O(n)$.

É importante destacar que, apesar da remoção e da inserção terem complexidade $O(n)$, o que, de
fato, *atrasa* a inserção e a remoção é achar o elemento — visto que o processo de inserir ou
remover, excluída a busca do elemento na posição, ou pela chave específica, é constante, isto é,
$O(1)$, bastando alterar os ponteiros para o próximo e, se for o caso, para o anterior, seguido da
(des)alocação do nó correspondente.

## Lista Simplesmente Encadeada

Cada elemento da lista é representado por um **"nó"**, que possui dados e também um ponteiro para o
próximo elemento.

```cpp
struct No {
    int valor;
    No* proximo;

    No(int valor) : valor(valor), proximo(nullptr) {}
};
```

A lista possui um ponteiro para o **início** (primeiro elemento) e, opcionalmente, para o **fim**
(último elemento). O ponteiro para o último elemento tem em vista a maior facilidade para a inserção
de um novo elemento e também para remoções no fim da estrutura.

Opcionalmente, pode ser incluído na lista um **atributo tamanho**, que informa o número de nós
presentes na estrutura. Sem essa informação, a estrutura deve ser percorrida por completo para que
seu tamanho seja determinado.

Implementações de listas encadeadas costumam disponibilizar os seguintes métodos:

- **Percorrimento:** percorre todos os nós da lista, realizando uma determinada operação sobre eles.
- **Busca por valor:** percorre a lista buscando um nó que contenha um determinado valor.
- **Busca por posição:** percorre a lista até determinada posição informada.
- **Inserção:** insere determinado valor na lista.
  - Inserção no começo
  - Inserção no fim
  - Inserção em posição específica
- **Remoção:** remove determinado elemento presente na lista.
  - Remoção no começo
  - Remoção no fim
  - Remoção em posição específica
  - Remoção por valor específico
- **Trocar dois elementos de posição**
- **Concatenar duas listas**

### Inserção no início

Basta criar o novo nó apontando para o antigo início da lista e, então, atualizar o ponteiro de
início para o nó recém-criado. Operação de custo constante, $O(1)$.

```cpp
void inserirInicio(No*& inicio, int valor) {
    No* novo = new No(valor);
    novo->proximo = inicio;
    inicio = novo;
}
```

### Inserção no fim

Caso haja um ponteiro para o fim da lista, a inserção também é feita em tempo constante; caso
contrário, é necessário percorrer a lista inteira até encontrar o último nó, tornando a operação
$O(n)$.

```cpp
void inserirFim(No*& inicio, No*& fim, int valor) {
    No* novo = new No(valor);

    if (inicio == nullptr) { // lista vazia
        inicio = fim = novo;
        return;
    }

    fim->proximo = novo;
    fim = novo;
}
```

### Busca por valor

```cpp
No* buscar(No* inicio, int valor) {
    No* atual = inicio;

    while (atual != nullptr && atual->valor != valor) {
        atual = atual->proximo;
    }

    return atual; // nullptr caso o valor não seja encontrado
}
```

### Remoção por valor específico

Para remover um nó é necessário manter uma referência ao seu **antecessor**, já que é o ponteiro do
antecessor que precisa ser redirecionado para "pular" o nó removido.

```cpp
void removerPorValor(No*& inicio, int valor) {
    No* atual = inicio;
    No* anterior = nullptr;

    while (atual != nullptr && atual->valor != valor) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == nullptr) return; // valor não encontrado

    if (anterior == nullptr) {
        inicio = atual->proximo; // removendo o próprio início
    } else {
        anterior->proximo = atual->proximo;
    }

    delete atual;
}
```

## Lista Duplamente Encadeada

Na lista duplamente encadeada, cada nó armazena, além do ponteiro para o próximo elemento, um
ponteiro para o elemento **anterior**. Essa característica permite que a lista seja percorrida em
ambos os sentidos e torna algumas operações — como a remoção de um nó já conhecido ou a inserção
antes de um nó específico — mais simples e eficientes, já que não é necessário percorrer a lista
para descobrir o antecessor de um nó.

```cpp
struct NoDuplo {
    int valor;
    NoDuplo* proximo;
    NoDuplo* anterior;

    NoDuplo(int valor) : valor(valor), proximo(nullptr), anterior(nullptr) {}
};
```

Como contrapartida, cada nó passa a exigir mais memória, devido ao ponteiro adicional, e as
operações de inserção e remoção precisam manter **dois ponteiros consistentes** em vez de apenas um.

### Inserção no fim

```cpp
void inserirFim(NoDuplo*& inicio, NoDuplo*& fim, int valor) {
    NoDuplo* novo = new NoDuplo(valor);

    if (inicio == nullptr) { // lista vazia
        inicio = fim = novo;
        return;
    }

    novo->anterior = fim;
    fim->proximo = novo;
    fim = novo;
}
```

### Remoção de um nó conhecido

Diferentemente da lista simplesmente encadeada, se já se possui um ponteiro para o nó a ser
removido, não é necessário percorrer a lista para encontrar o seu antecessor — basta consultar o
ponteiro `anterior` do próprio nó.

```cpp
void remover(NoDuplo*& inicio, NoDuplo*& fim, NoDuplo* no) {
    if (no->anterior != nullptr) {
        no->anterior->proximo = no->proximo;
    } else {
        inicio = no->proximo; // 'no' era o início da lista
    }

    if (no->proximo != nullptr) {
        no->proximo->anterior = no->anterior;
    } else {
        fim = no->anterior; // 'no' era o fim da lista
    }

    delete no;
}
```

## Vantagens e desvantagens

### Lista Simplesmente Encadeada

- Cada nó ocupa menos memória, por armazenar apenas um ponteiro.
- Não é possível percorrer a lista de trás para frente.
- Remover um nó exige, em geral, encontrar seu antecessor, o que demanda percorrer a lista a partir
  do início.

### Lista Duplamente Encadeada

- Permite percorrimento nos dois sentidos (início ao fim e fim ao início).
- Remoções e inserções junto a um nó já conhecido são mais simples, pois o antecessor é acessado
  diretamente.
- Cada nó ocupa mais memória, devido ao ponteiro adicional para o antecessor.
