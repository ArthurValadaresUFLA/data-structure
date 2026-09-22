# Árvores Binárias de Busca

## O que é?

Árvores binárias são **grafos conexos e acíclicos nos quais cada nó possui zero, um ou dois filhos**.

Assim, árvores binárias podem ser definidas recursivamente como um **nó raiz contendo duas subárvores**, **à esquerda
(SE) e à direita (SD)**, sendo que cada uma dessas subárvores é, ela mesma, uma árvore binária (podendo, inclusive,
estar vazia).

```cpp
struct No {
    int valor;
    No* esquerda;
    No* direita;

    No(int valor) : valor(valor), esquerda(nullptr), direita(nullptr) {}
};
```

Alguns termos são recorrentes ao se tratar de árvores:

- **Raiz:** o único nó que não possui pai, ponto de partida da árvore.
- **Folha:** nó que não possui filhos.
- **Grau de um nó:** quantidade de filhos que esse nó possui (0, 1 ou 2, no caso de árvores binárias).
- **Subárvore:** qualquer nó, juntamente com todos os seus descendentes, pode ser entendido como a raiz de uma nova
  árvore, menor, contida na árvore original.

### Níveis e Altura

**Nível** determina a distância (número de arestas) que determinado nó se encontra da raiz. Sendo assim, a raiz possui
nível 0, seus filhos nível 1 e assim por diante.

Já a **altura** de uma árvore é determinada pelo nível do nó de maior nível presente nela. Uma árvore composta somente
pela raiz possui altura 0; uma árvore vazia, por convenção, costuma ter altura -1.

### Percorrimento

Para realizar o percorrimento em árvores binárias, três métodos podem ser adotados, que se diferenciam pela
**prioridade no tratamento dos nós**:

- **Pré-ordem:** Raiz $\rightarrow$ SE $\rightarrow$ SD
- **Em-ordem:** SE $\rightarrow$ Raiz $\rightarrow$ SD
- **Pós-ordem:** SE $\rightarrow$ SD $\rightarrow$ Raiz

Observe que a SE sempre possui preferência em relação à SD nas definições acima, porém essa é apenas uma convenção de
implementação; em determinadas situações, essa ordem pode ser invertida.

Os três métodos podem ser implementados recursivamente, bastando alterar a posição em que o nó atual é processado em
relação às chamadas recursivas para as subárvores:

```cpp
void preOrdem(No* raiz) {
    if (raiz == nullptr) return;

    // processa o nó antes de visitar as subárvores
    std::cout << raiz->valor << " ";
    preOrdem(raiz->esquerda);
    preOrdem(raiz->direita);
}

void emOrdem(No* raiz) {
    if (raiz == nullptr) return;

    emOrdem(raiz->esquerda);
    // processa o nó entre as duas subárvores
    std::cout << raiz->valor << " ";
    emOrdem(raiz->direita);
}

void posOrdem(No* raiz) {
    if (raiz == nullptr) return;

    posOrdem(raiz->esquerda);
    posOrdem(raiz->direita);
    // processa o nó depois de visitar as subárvores
    std::cout << raiz->valor << " ";
}
```

## Árvore Binária de Busca (ABB)

Pontuados os aspectos importantes para se definir uma árvore binária, podemos, agora, nos concentrar nas árvores
binárias de busca.

Árvores binárias de busca são, basicamente, árvores binárias em que seus nós se encontram ordenados. Assim, para cada
nó, todos os elementos da sua subárvore esquerda são menores do que ele e todos os elementos da sua subárvore direita
são maiores. Essa propriedade deve valer recursivamente para todos os nós da árvore, não apenas para a raiz.

É justamente essa propriedade de ordenação que permite que as operações de busca, inserção e remoção sejam realizadas,
no melhor caso, em tempo $O(\log n)$: a cada comparação, é possível descartar uma das duas subárvores, exatamente como
ocorre numa busca binária em um vetor ordenado.

### Busca

Para buscar um valor, compara-se o valor procurado com o valor do nó atual: se forem iguais, o elemento foi
encontrado; se o valor procurado for menor, a busca prossegue na subárvore esquerda; se for maior, na subárvore
direita.

```cpp
No* buscar(No* raiz, int valor) {
    if (raiz == nullptr || raiz->valor == valor) {
        return raiz; // encontrou o valor ou chegou a uma subárvore vazia
    }

    if (valor < raiz->valor) {
        return buscar(raiz->esquerda, valor);
    }

    return buscar(raiz->direita, valor);
}
```

### Inserção

A inserção segue a mesma lógica da busca: percorre-se a árvore comparando o valor a ser inserido com o valor de cada
nó, até que se encontre uma subárvore vazia, posição na qual o novo nó deve ser inserido.

```cpp
No* inserir(No* raiz, int valor) {
    if (raiz == nullptr) {
        return new No(valor); // posição encontrada
    }

    if (valor < raiz->valor) {
        raiz->esquerda = inserir(raiz->esquerda, valor);
    } else if (valor > raiz->valor) {
        raiz->direita = inserir(raiz->direita, valor);
    }
    // se valor == raiz->valor, o elemento já existe e nada é feito

    return raiz;
}
```

### Remoção

A remoção é a operação mais delicada, pois é necessário manter a propriedade de ordenação da árvore após a retirada do
nó. Há três casos a considerar:

1. **Nó folha:** basta remover o nó, sem necessidade de nenhum ajuste adicional.
2. **Nó com um único filho:** o filho assume o lugar do nó removido.
3. **Nó com dois filhos:** o nó é substituído pelo seu **sucessor em-ordem** (o menor valor da sua subárvore direita)
   ou pelo seu **antecessor em-ordem** (o maior valor da sua subárvore esquerda), e esse sucessor/antecessor é então
   removido de sua posição original.

```cpp
No* encontrarMinimo(No* raiz) {
    while (raiz->esquerda != nullptr) {
        raiz = raiz->esquerda;
    }
    return raiz;
}

No* remover(No* raiz, int valor) {
    if (raiz == nullptr) return raiz;

    if (valor < raiz->valor) {
        raiz->esquerda = remover(raiz->esquerda, valor);
    } else if (valor > raiz->valor) {
        raiz->direita = remover(raiz->direita, valor);
    } else {
        // encontrou o nó a ser removido
        if (raiz->esquerda == nullptr) {
            No* filho = raiz->direita;
            delete raiz;
            return filho;
        } else if (raiz->direita == nullptr) {
            No* filho = raiz->esquerda;
            delete raiz;
            return filho;
        }

        // nó com dois filhos: substitui pelo sucessor em-ordem
        No* sucessor = encontrarMinimo(raiz->direita);
        raiz->valor = sucessor->valor;
        raiz->direita = remover(raiz->direita, sucessor->valor);
    }

    return raiz;
}
```

## Vantagens e desvantagens

- Buscas, inserções e remoções podem ser feitas em $O(\log n)$, caso a árvore esteja **balanceada**.
- No pior caso — quando os elementos são inseridos em ordem crescente ou decrescente, por exemplo —, a árvore
  **degenera** em uma estrutura semelhante a uma lista encadeada, e as operações passam a custar $O(n)$.
- Diferentemente de um vetor ordenado, permite inserções e remoções sem a necessidade de deslocar elementos.
- Estruturas como as **árvores AVL** e as **árvores rubro-negras** resolvem o problema da degeneração ao
  reequilibrarem a árvore automaticamente a cada inserção ou remoção, garantindo altura $O(\log n)$ mesmo no pior
  caso; esse é um tópico que foge ao escopo introdutório aqui apresentado.
