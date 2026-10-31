# Estrutura de Dados (C++)

Repositório com as implementações das Estruturas de Dados desenvolvidas na disciplina de **GAC108 —
DCC/UFLA**. Os códigos foram baseados nas aulas e materiais disponibilizados pelos docentes e são de
autoria de **Arthur Valadares Campideli** e **Gabriel Coelho**.

> As estruturas deste repositório são implementadas seguindo a abstração em TADs (Tipos Abstratos de
> Dados), usando o padrão `Interface → Abstract → Implementação`. Se este for o seu primeiro contato
> com o paradigma, comece por [Introdução a TAD](wiki/tad.md).

## Conteúdo

Cada linha abaixo aponta tanto para a explicação conceitual (wiki) quanto para o código-fonte
(header + implementação).

| Estrutura de Dados                       | Conceito                                                                   | Header (`include/`)                                                                                             | Implementação (`src/`)                                                                                          |
| :--------------------------------------- | :------------------------------------------------------------------------- | :-------------------------------------------------------------------------------------------------------------- | :-------------------------------------------------------------------------------------------------------------- |
| Pilha (Array)                            | [Pilha](wiki/pilha.md)                                                     | [ArrayStack.h](include/data-structure/stack/ArrayStack.h)                                                       | [ArrayStack.cpp](src/data-structure/stack/ArrayStack.cpp)                                                       |
| Pilha (Encadeada)                        | [Pilha](wiki/pilha.md)                                                     | [LinkedStack.h](include/data-structure/stack/LinkedStack.h)                                                     | [LinkedStack.cpp](src/data-structure/stack/LinkedStack.cpp)                                                     |
| Fila (Array circular)                    | [Fila](wiki/fila.md)                                                       | [ArrayQueue.h](include/data-structure/queue/ArrayQueue.h)                                                       | [ArrayQueue.cpp](src/data-structure/queue/ArrayQueue.cpp)                                                       |
| Fila (Encadeada)                         | [Fila](wiki/fila.md)                                                       | [LinkedQueue.h](include/data-structure/queue/LinkedQueue.h)                                                     | [LinkedQueue.cpp](src/data-structure/queue/LinkedQueue.cpp)                                                     |
| MaxHeap                                  | [Heap](wiki/heap.md) · [MaxHeap](wiki/max-heap.md)                         | [MaxHeap.h](include/data-structure/heap/MaxHeap.h)                                                              | [MaxHeap.cpp](src/data-structure/heap/MaxHeap.cpp)                                                              |
| MinHeap                                  | [Heap](wiki/heap.md) · [MinHeap](wiki/min-heap.md)                         | [MinHeap.h](include/data-structure/heap/MinHeap.h)                                                              | [MinHeap.cpp](src/data-structure/heap/MinHeap.cpp)                                                              |
| Torneio                                  | [Torneio](wiki/torneio.md)                                                 | [Tournament.h](include/data-structure/heap/Tournament.h)                                                        | [Tournament.cpp](src/data-structure/heap/Tournament.cpp)                                                        |
| Lista Simplesmente Encadeada             | [Lista](wiki/lista.md) · [Lista Encadeada](wiki/lista-encadeada.md)        | [SinglyLinkedList.h](include/data-structure/list/SinglyLinkedList.h)                                            | [SinglyLinkedList.cpp](src/data-structure/list/SinglyLinkedList.cpp)                                            |
| Lista Duplamente Encadeada               | [Lista](wiki/lista.md) · [Lista Encadeada](wiki/lista-encadeada.md)        | [DoublyLinkedList.h](include/data-structure/list/DoublyLinkedList.h)                                            | [DoublyLinkedList.cpp](src/data-structure/list/DoublyLinkedList.cpp)                                            |
| Tabela Hash (encadeamento)               | [Hash](wiki/hash.md) · [Encadeada](wiki/hash-encadeado.md)                 | [LinkedHashTable.h](include/data-structure/hash/LinkedHashTable.h)                                              | [LinkedHashTable.cpp](src/data-structure/hash/LinkedHashTable.cpp)                                              |
| Tabela Hash (endereçamento aberto)       | [Hash](wiki/hash.md) · [Endereço Aberto](wiki/hash-com-endereco-aberto.md) | [OpenAddressHashTable.h](include/data-structure/hash/OpenAddressHashTable.h)                                    | [OpenAddressHashTable.cpp](src/data-structure/hash/OpenAddressHashTable.cpp)                                    |
| Árvore Binária de Busca                  | [Árvore Binária de Busca](wiki/arvore-binaria-de-busca.md)                 | [BinarySearchTree.h](include/data-structure/tree/binary_search_tree/BinarySearchTree.h)                         | [BinarySearchTree.cpp](src/data-structure/tree/binary_search_tree/BinarySearchTree.cpp)                         |
| Árvore Binária de Busca (dup. encadeada) | [Árvore Binária de Busca](wiki/arvore-binaria-de-busca.md)                 | [DoublyLinkedBinarySearchTree.h](include/data-structure/tree/binary_search_tree/DoublyLinkedBinarySearchTree.h) | [DoublyLinkedBinarySearchTree.cpp](src/data-structure/tree/binary_search_tree/DoublyLinkedBinarySearchTree.cpp) |

> Os nós (`node/`) que dão suporte às listas e árvores (`SinglyLinkedNode`, `DoublyLinkedNode`,
> `SinglyLinkedBinaryTreeNode`, `DoublyLinkedBinaryTreeNode`, entre outros) ficam em
> [`include/data-structure/node`](include/data-structure/node) e
> [`src/data-structure/node`](src/data-structure/node), e normalmente não precisam ser usados
> diretamente — servem como peça interna das estruturas acima.

Todas as estruturas seguem o mesmo padrão de organização interna: uma **interface**
(`interface/XInterface.h`) define o contrato público, uma classe **abstrata** (`AbstractX.h`)
implementa o que é comum a todas as variações, e as classes **concretas** (ex.: `MaxHeap`,
`ArrayStack`) implementam os detalhes específicos.

## Documentação

Além deste README, o projeto conta com duas fontes de documentação complementares:

- `wiki/` — explicações conceituais de cada estrutura de dados (o "porquê" e a teoria por trás
  delas), escritas em Markdown.

- **Doxygen** — documentação gerada automaticamente a partir dos comentários no código-fonte
  (`include/` e `src/`), cobrindo classes, métodos e a hierarquia
  `Interface → Abstract → Implementação`. A configuração fica em
  [`doc/Doxyfile.in`](doc/Doxyfile.in) e pode ser gerada com CMake.

  ```fish
  cmake .

  doxygen # Na raiz do projeto
  doxygen Doxyfile # ou referenciando o arquivo gerado pelo CMake na raiz do projeto
  ```

  > Existe também um `Doxyfile.in` na raiz do repositório; ele é um resquício do `doxygen -g`
  > inicial e **não** é o arquivo de configuração oficial — use sempre o de `doc/Doxyfile.in`.

## Exemplos (Dredd)

O diretório [`examples/dredd`](examples/dredd) reúne soluções de exercícios aplicados durante a
disciplina na plataforma [Dredd](https://dredd.dac.ufla.br/), organizados por assunto:

| Categoria                                     | Diretório                               |
| :-------------------------------------------- | :-------------------------------------- |
| Exercícios diversos (arquivos, recursão etc.) | [`Arquivos`](examples/dredd/Arquivos)   |
| Filas                                         | [`Fila`](examples/dredd/Fila)           |
| Heaps                                         | [`Heap`](examples/dredd/Heap)           |
| Matrizes                                      | [`Matriz`](examples/dredd/Matriz)       |
| Pilhas                                        | [`Pilha`](examples/dredd/Pilha)         |
| Ponteiros e alocação dinâmica                 | [`Ponteiros`](examples/dredd/Ponteiros) |
| Vetores                                       | [`Vetor`](examples/dredd/Vetor)         |

> Esses exemplos são soluções pontuais de exercícios (não fazem parte da API pública da biblioteca)
> e por isso ficam fora da documentação gerada pelo Doxygen.

## Estrutura do Repositório

```txt
.
├── CMakeLists.txt        # Configuração de build do projeto (biblioteca)
├── conanfile.py           # Receita do Conan 2 (empacotamento/dependências)
├── doc/
│   └── Doxyfile.in        # Configuração oficial do Doxygen
├── examples/
│   ├── CMakeLists.txt     # Build dos exemplos
│   └── dredd/             # Soluções de exercícios da plataforma Dredd
├── include/
│   └── data-structure/    # Headers (.h) das estruturas de dados, por módulo
├── src/
│   └── data-structure/    # Implementações (.cpp) correspondentes aos headers
├── test_package/          # Pacote de teste padrão do Conan (valida a instalação/consumo da lib)
└── wiki/                  # Documentação conceitual de cada estrutura, em Markdown
```

Cada módulo dentro de `include/data-structure` e `src/data-structure` (`hash`, `heap`, `list`,
`node`, `queue`, `stack`, `tree`) segue o mesmo padrão: uma pasta `interface/` com os contratos
(`.h`), classes abstratas na raiz do módulo, e as implementações concretas.

## Ambiente de Desenvolvimento

O projeto usa **CMake** para build e **Conan 2** para gerenciamento de dependências e empacotamento.

1. Instale o [Conan 2](https://docs.conan.io/2/installation.html) e o CMake.

1. Na raiz do repositório, crie/instale o pacote localmente:

   ```bash
   conan create . --build=missing
   ```

   Esse comando compila a biblioteca e roda o `test_package/`, validando que ela pode ser consumida
   por outro projeto via Conan.

1. Para desenvolvimento local com CMake diretamente (sem empacotar via Conan), configure e compile
   normalmente:

   ```bash
   cmake -S . -B build
   cmake --build build
   ```

## Ferramentas Utilizadas

- **Git** — controle de versão.
- **CMake** — geração e build do projeto, de forma independente de plataforma.
- **Conan 2** — gerenciamento de dependências e empacotamento em C++.
- **Doxygen** — geração da documentação de API a partir do código-fonte.
