# Árvores Binárias de Busca

## Tópicos

* [Árvores Binárias de Busca](../arvores/abb/abb)
* [Tries](tries)

## Definição e Visão Geral

### O que é?

Árvores Binárias são **grafos conexos, acíclicos e que cada nó possui zero, um ou dois filhos**.

Assim, árvores binárias podem ser definidas recursivamente como um **nó raiz contendo duas subárvores**, **à esquerda (SE) e à direita (SD)**.

#### Níveis e Altura

**Nível** determina a distância (número de arestas) que determinado nó se encontra da raiz. Sendo assim a raíz possui nível 0, seus filhos nível 1 e assim por diante...

Já a **altura** é determinada pelo nó de maior nível presente na árvore.

#### Percorrimento

Para realizar o percorrimento em árvores binárias 3 métodos podem ser adotados, que se diferenciam pela **prioridade no tratamento dos nós**:

* **Pré-ordem:** Raiz $\rightarrow$ SE $\rightarrow$ SD

* **Em-ordem:** SE $\rightarrow$ Raiz $\rightarrow$ SD

* **Pós-ordem:** SE $\rightarrow$ SD $\rightarrow$ Raiz

Observe que a SE sempre possui preferência em relação à SD, porém essa é apenas uma forma de implementação, sendo que, em determinadas situações, essa ordem deve ser invertida.

#### ABB

Pontuados os aspectos importantes para se definir uma árvore binária, podemos, agora, nos concentrar nas árvores binárias de busca.

Árvores binárias de busca são, basicamente, árvores binárias em que seus nós se encontram ordenados. Assim, para cada nó, os elementos menores estarão à sua esquerda e os maiores à sua direita.


### Aplicações