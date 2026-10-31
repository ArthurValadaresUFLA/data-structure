# Heaps

## O que é?

Estrutura de dados usada para implementar **filas de prioridade**.

Geralmente, é construída em **arrays**, mas manipulada como uma **árvore binária**. Na verdade, um
heap é uma **árvore binária balanceada** (nós folhas com, no máximo, um nível de diferença entre si)
e **completa** (nós não folhas com o mesmo grau da árvore, isto é, sempre dois filhos). É aceitável
que o último nó não folha (à direita ou à esquerda) possua grau inferior. **Isso garante que não há
espaços vazios no meio do array**.

Justamente por ser completa, a representação de um heap em array é bastante direta: dado um nó no
índice $i$ (considerando indexação a partir de 0), seu filho à esquerda se encontra no índice $2i +
1$, seu filho à direita no índice $2i + 2$, e seu pai no índice $\\lfloor (i - 1) / 2 \\rfloor$. Não
há necessidade, portanto, de armazenar ponteiros entre os nós.

Em um **heap**, **todo pai é sempre maior**, no caso de um **max heap**, **ou menor**, no caso de um
**min heap**, **que seus filhos**.

Já o **torneio** é uma estrutura bastante semelhante ao heap, diferenciando-se, essencialmente, pelo
fato de **todo pai possuir uma cópia do maior (ou menor) entre seus dois filhos**, em vez de apenas
ser maior (ou menor) do que eles.

A importância dessas estruturas para a implementação de filas de prioridade se deve ao fato de a
**raiz sempre representar o elemento de maior prioridade**. Assim, a cada remoção da raiz, a
estrutura é reorganizada e o novo elemento com maior prioridade passa a ocupar a raiz.

## Max Heap

Como dito anteriormente, **max heaps** são estruturas geralmente implementadas em **arrays** nas
quais **todo pai é maior que os seus dois filhos**. Dessa forma, podemos garantir que **o maior
elemento sempre se encontra na raiz**.

### Inserção

Um novo elemento é sempre inserido na primeira posição livre do array (mantendo a propriedade de
completude) e, então, "sobe" pela árvore — operação chamada de ***sift-up*** ou *heapify-up* —,
trocando de lugar com o seu pai enquanto for maior do que ele, até restaurar a propriedade de heap.

```cpp
#include <vector>

void siftUp(std::vector<int>& heap, int i) {
    while (i > 0) {
        int pai = (i - 1) / 2;

        if (heap[i] <= heap[pai]) break; // propriedade de heap restaurada

        std::swap(heap[i], heap[pai]);
        i = pai;
    }
}

void inserir(std::vector<int>& heap, int valor) {
    heap.push_back(valor);       // insere na última posição livre
    siftUp(heap, heap.size() - 1);
}
```

### Remoção da raiz

A remoção do elemento de maior prioridade (a raiz) é feita substituindo-a pelo **último elemento**
do array, que é então removido de sua posição original, e "descendo-o" pela árvore — operação
chamada de ***sift-down*** ou *heapify-down* —, trocando-o de lugar com o maior dos seus filhos
enquanto ele for menor do que algum deles.

```cpp
void siftDown(std::vector<int>& heap, int i) {
    int tamanho = heap.size();

    while (true) {
        int esquerda = 2 * i + 1;
        int direita = 2 * i + 2;
        int maior = i;

        if (esquerda < tamanho && heap[esquerda] > heap[maior]) maior = esquerda;
        if (direita < tamanho && heap[direita] > heap[maior]) maior = direita;

        if (maior == i) break; // propriedade de heap restaurada

        std::swap(heap[i], heap[maior]);
        i = maior;
    }
}

int removerMáximo(std::vector<int>& heap) {
    int raiz = heap[0];
    heap[0] = heap.back(); // último elemento assume a posição da raiz
    heap.pop_back();

    siftDown(heap, 0);
    return raiz;
}
```

Ambas as operações, inserção e remoção, custam $O(\\log n)$, já que, no pior caso, o elemento
precisa percorrer toda a altura da árvore, que, por esta ser completa e balanceada, é sempre
$O(\\log n)$.

## Min Heap

Como dito anteriormente, **min heaps** são estruturas geralmente implementadas em **arrays** nas
quais **todo pai é menor que os seus dois filhos**. Dessa forma, podemos garantir que **o menor
elemento sempre se encontra na raiz**.

A implementação de um min heap é idêntica à de um max heap, bastando inverter o sentido das
comparações — trocando `>` por `<` nas funções `siftUp` e `siftDown` apresentadas acima.

## Torneio

A implementação de um **torneio** se assemelha muito à implementação de um heap, com a diferença já
citada anteriormente: **cada pai contém uma cópia do maior (ou menor, a depender do critério
adotado) entre seus dois filhos**. Dessa forma, **o conteúdo dos nós folhas determina todos os
valores restantes da árvore**.

Geralmente, torneios são implementados para a **obtenção de um vencedor**, comparando os elementos
dois a dois, nível a nível, de forma semelhante a um torneio esportivo eliminatório — daí o nome.
Dessa forma, para a maioria das implementações, não faz sentido a operação de **remoção**. O mais
sensato a se fazer, caso haja essa necessidade, seria **refazer o torneio inteiro com os elementos
restantes**.

No caso de **torneios incompletos**, em que o **número de elementos não é uma potência de 2**,
algumas **posições intermediárias** são preenchidas como **inválidas**, servindo apenas para
preservar a estrutura completa e balanceada da árvore.

Dessa forma, o **número de nós intermediários** é dado pela **primeira potência de 2 que seja maior
ou igual ao número de dados**, decrescida de uma unidade.

## Vantagens e desvantagens

- Inserção e remoção da raiz custam $O(\\log n)$, sensivelmente mais rápido que manter um array
  ordenado (que exigiria $O(n)$ para inserção) e comparável a uma árvore binária de busca
  balanceada.
- Consultar o elemento de maior (ou menor) prioridade custa $O(1)$, já que ele sempre está na raiz.
- Diferentemente de uma árvore binária de busca, um heap **não** permite busca eficiente por um
  elemento qualquer que não seja a raiz — para isso, seria necessário percorrer toda a estrutura, em
  $O(n)$.
- Por ser representado num array contíguo, tende a ter melhor desempenho de cache do que estruturas
  baseadas em ponteiros, como árvores encadeadas tradicionais.
