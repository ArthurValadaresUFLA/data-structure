# Lista Encadeada

Confira a implementação de uma [lista encadeada](../src/list/LinkedList.cpp) em C++.

## Detalhes da implementação

Cada elemento da lista é representado por um **"nó"** , que possui dados e também um ponteiro para o próximo elemento.

A lista possui um ponteiro para o **inicio** (primeiro elemento) e, opcionalmente, para o **fim** (último elemento). O
ponteiro para o último elemento tem em vista a maior facilidade para a inserção de um novo elemento e também para
remoções no fim da estrutura.

Opcionalmente, pode ser incluído na fila um **atributo tamanho**, que informa o número de nós presentes na estrutura.
Sem essa informação, a estrutura deve ser percorrida por completo para que seu tamanho seja determinado.

Implementações de listas encadeadas costumam disponibilizar os seguintes métodos:

* **Percorrimento:** percorre todos os nós da lista, realizando uma determinada operação sobre eles.

* **Busca por valor:** percorre a lista buscando um nó que contenha um determinado valor.

* **Busca por posição:** percorre a lista até determinada posição informada.

* **Inserção:** inserir determinado valor na lista.
    * Inserção no começo
    * Inserção no fim
    * Inserção em posição específica

* **Remoção:** remover determinado elemento presente na lista.
    * Remoção no começo
    * Remoção no fim
    * Remoção em posição específica
    * Remoção por valor específico

* **Trocar dois elementos de posição**

* **Concatenar duas listas**