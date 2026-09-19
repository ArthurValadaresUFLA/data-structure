# Heaps

## Tópicos

* [MaxHeaps](../src/heap/maxHeap)
* [MinHeaps](../src/heap/minHeap)
* [Torneio](../src/heap/tournament)

## Definição e Visão Geral

### O que é?

Estrutura de dados usada para implementar **filas de prioridade**.

Geralmente, é construída em **arrays**, mas manipulada como uma **árvore binária**. Na verdade, um heap é uma **árvore
binária balanceada** (nós folhas com no máximo um nível de diferença) e **completa** (nós não folhas com mesmo grau da
árvore). É aceitável que o último nó não folha (à direita ou à esquerda) possua grau inferior. **Isso garante que não há
espaços vazios no meio do _array**.

Em um **heap**, **todo pai é sempre maior**, no caso caso de um **max heap**, **ou menor**, no caso de um **min heap**,
**que seus filhos**.

Já o **torneio**, é uma estrutura bastante semelhante ao heap, diferenciando-se, essencialmente, pelo fato de **todo pai
possuir uma cópia do maior entre seus dois filhos**.

A importância dessas estruturas para implementação de filas de prioridade se deve ao fato da **raiz sempre representar o
elemento de maior prioridade**. Assim, a cada remoção da raiz a estrutura é reorganizada e o novo elemento com maior
prioridade passa a ocupar a raiz.

### Aplicações

* HeapSort