// Testes Catch2 (v3) para as árvores binárias de busca:
//   - BinarySearchTree<T>             (nós simplesmente ligados)
//   - DoublyLinkedBinarySearchTree<T> (nós com ponteiro para o pai)
//
// Contrato testado:
//   * Valores iguais são inseridos na subárvore direita.
//   * remove() de valor ausente não faz nada; remove() remove uma ocorrência.
//   * search() devolve o nó que contém o valor, ou nullptr.
//   * Cópia é profunda; a árvore libera todos os nós (sem recursão).

#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>

#include <cstddef>
#include <memory>
#include <random>
#include <set>
#include <string>
#include <utility>
#include <vector>

#include "data-structure/tree/binary_search_tree/BinarySearchTree.h"
#include "data-structure/tree/binary_search_tree/DoublyLinkedBinarySearchTree.h"
#include "data-structure/tree/binary_search_tree/interface/BinarySearchTreeInterface.h"
#include "data-structure/tree/binary_search_tree/interface/DoublyLinkedBinarySearchTreeInterface.h"

TEMPLATE_TEST_CASE("BST<int>: arvore vazia", "[tree][empty]",
                   BinarySearchTree<int>, DoublyLinkedBinarySearchTree<int>) {
  TestType tree;

  REQUIRE(tree.search(1) == nullptr);
  REQUIRE_NOTHROW(tree.remove(1));
}

TEMPLATE_TEST_CASE("BST<int>: insert e search", "[tree][insert]",
                   BinarySearchTree<int>, DoublyLinkedBinarySearchTree<int>) {
  TestType tree;
  for (int v : {50, 30, 70, 20, 40, 60, 80}) {
    tree.insert(v);
  }

  for (int v : {50, 30, 70, 20, 40, 60, 80}) {
    auto *node = tree.search(v);
    REQUIRE(node != nullptr);
    REQUIRE(node->getValue() == v);
  }
  REQUIRE(tree.search(10) == nullptr);
  REQUIRE(tree.search(55) == nullptr);
  REQUIRE(tree.search(100) == nullptr);
}

TEMPLATE_TEST_CASE("BST<int>: estrutura dos nos", "[tree][structure]",
                   BinarySearchTree<int>, DoublyLinkedBinarySearchTree<int>) {
  TestType tree;
  for (int v : {50, 30, 70, 20}) {
    tree.insert(v);
  }

  auto *root = tree.search(50);
  REQUIRE(root->getLeft()->getValue() == 30);
  REQUIRE(root->getRight()->getValue() == 70);
  REQUIRE(root->childCount() == 2);
  REQUIRE(tree.search(30)->getLeft()->getValue() == 20);
  REQUIRE(tree.search(30)->getRight() == nullptr);
  REQUIRE(tree.search(30)->childCount() == 1);
  REQUIRE(tree.search(20)->childCount() == 0);
}

TEMPLATE_TEST_CASE("BST<int>: valores iguais vao para a direita",
                   "[tree][duplicates]", BinarySearchTree<int>,
                   DoublyLinkedBinarySearchTree<int>) {
  TestType tree;
  tree.insert(5);
  tree.insert(5);
  tree.insert(5);

  REQUIRE(tree.search(5)->getRight() != nullptr);
  REQUIRE(tree.search(5)->getLeft() == nullptr);

  tree.remove(5); // remove apenas uma ocorrencia
  REQUIRE(tree.search(5) != nullptr);
  tree.remove(5);
  REQUIRE(tree.search(5) != nullptr);
  tree.remove(5);
  REQUIRE(tree.search(5) == nullptr);
}

TEMPLATE_TEST_CASE("BST<int>: remove", "[tree][remove]", BinarySearchTree<int>,
                   DoublyLinkedBinarySearchTree<int>) {
  TestType tree;
  for (int v : {50, 30, 70, 20, 40, 60, 80, 65}) {
    tree.insert(v);
  }

  auto requireOnly = [&tree](std::set<int> present) {
    for (int v : {50, 30, 70, 20, 40, 60, 80, 65}) {
      REQUIRE((tree.search(v) != nullptr) == (present.count(v) > 0));
    }
  };

  SECTION("folha") {
    tree.remove(20);
    requireOnly({50, 30, 70, 40, 60, 80, 65});
    REQUIRE(tree.search(30)->getLeft() == nullptr);
  }

  SECTION("no com um filho") {
    tree.remove(60); // tem apenas o filho direito (65)
    requireOnly({50, 30, 70, 20, 40, 80, 65});
    REQUIRE(tree.search(70)->getLeft()->getValue() == 65);
  }

  SECTION("no com dois filhos (sucessor e o filho direito)") {
    tree.remove(30); // sucessor: 40, filho direito direto
    requireOnly({50, 70, 20, 40, 60, 80, 65});
    REQUIRE(tree.search(50)->getLeft()->getValue() == 40);
    REQUIRE(tree.search(40)->getLeft()->getValue() == 20);
  }

  SECTION("no com dois filhos (sucessor mais fundo)") {
    tree.remove(70); // sucessor: 80? nao: minimo da direita (80) e ele mesmo
    requireOnly({50, 30, 20, 40, 60, 80, 65});
    REQUIRE(tree.search(50)->getRight()->getValue() == 80);
    REQUIRE(tree.search(80)->getLeft()->getValue() == 60);
  }

  SECTION("raiz com dois filhos") {
    tree.remove(50); // sucessor: 60, que possui filho direito (65)
    requireOnly({30, 70, 20, 40, 60, 80, 65});
    REQUIRE(tree.search(60)->getLeft()->getValue() == 30);
    REQUIRE(tree.search(60)->getRight()->getValue() == 70);
    REQUIRE(tree.search(70)->getLeft()->getValue() == 65);
  }

  SECTION("valor ausente nao altera a arvore") {
    REQUIRE_NOTHROW(tree.remove(999));
    requireOnly({50, 30, 70, 20, 40, 60, 80, 65});
  }

  SECTION("remover tudo e reutilizar") {
    for (int v : {50, 30, 70, 20, 40, 60, 80, 65}) {
      tree.remove(v);
    }
    requireOnly({});
    tree.insert(1);
    REQUIRE(tree.search(1) != nullptr);
  }
}

TEMPLATE_TEST_CASE("BST<int>: raiz com um unico filho", "[tree][remove]",
                   BinarySearchTree<int>, DoublyLinkedBinarySearchTree<int>) {
  TestType tree;
  tree.insert(1);
  tree.insert(2);

  tree.remove(1);
  REQUIRE(tree.search(1) == nullptr);
  REQUIRE(tree.search(2) != nullptr);

  tree.insert(0); // 2 passou a ser a raiz
  REQUIRE(tree.search(2)->getLeft()->getValue() == 0);
}

TEMPLATE_TEST_CASE("BST<int>: copia e movimentacao", "[tree][copy]",
                   BinarySearchTree<int>, DoublyLinkedBinarySearchTree<int>) {
  TestType tree;
  for (int v : {5, 3, 8, 1, 4}) {
    tree.insert(v);
  }

  SECTION("a copia e profunda") {
    TestType copy(tree);
    tree.remove(3);
    copy.insert(100);

    REQUIRE(tree.search(3) == nullptr);
    REQUIRE(copy.search(3) != nullptr);
    REQUIRE(copy.search(100) != nullptr);
    REQUIRE(tree.search(100) == nullptr);
    REQUIRE(copy.search(3) != tree.search(5)); // nos distintos
  }

  SECTION("copia de arvore vazia") {
    TestType empty;
    TestType copy(empty);
    REQUIRE(copy.search(1) == nullptr);
  }

  SECTION("atribuicao por copia") {
    TestType other;
    other.insert(99);
    other = tree;
    REQUIRE(other.search(99) == nullptr);
    for (int v : {5, 3, 8, 1, 4}) {
      REQUIRE(other.search(v) != nullptr);
    }
  }

  SECTION("auto-atribuicao e segura") {
    auto &alias = tree;
    tree = alias;
    for (int v : {5, 3, 8, 1, 4}) {
      REQUIRE(tree.search(v) != nullptr);
    }
  }

  SECTION("movimentacao") {
    TestType moved(std::move(tree));
    for (int v : {5, 3, 8, 1, 4}) {
      REQUIRE(moved.search(v) != nullptr);
    }
  }

  SECTION("atribuicao por movimentacao") {
    TestType other;
    other.insert(99);
    other = std::move(tree);
    REQUIRE(other.search(99) == nullptr);
    REQUIRE(other.search(4) != nullptr);
  }
}

TEMPLATE_TEST_CASE("BST<std::string>: operacoes basicas", "[tree][string]",
                   BinarySearchTree<std::string>,
                   DoublyLinkedBinarySearchTree<std::string>) {
  TestType tree;
  tree.insert("maca");
  tree.insert("banana");
  tree.insert("uva");

  REQUIRE(tree.search("banana") != nullptr);
  REQUIRE(tree.search("pera") == nullptr);
  tree.remove("maca");
  REQUIRE(tree.search("maca") == nullptr);
  REQUIRE(tree.search("uva") != nullptr);
}

TEMPLATE_TEST_CASE("BST<int>: arvore degenerada (profunda)",
                   "[tree][stress]", BinarySearchTree<int>,
                   DoublyLinkedBinarySearchTree<int>) {
  // Insercao ordenada gera uma lista: copia e destruicao precisam ser
  // iterativas para nao estourar a pilha de chamadas.
  TestType tree;
  constexpr int N = 20000;
  for (int i = 0; i < N; ++i) {
    tree.insert(i);
  }

  TestType copy(tree);
  REQUIRE(copy.search(N - 1) != nullptr);
  REQUIRE(tree.search(N) == nullptr);
}

TEMPLATE_TEST_CASE("BST<int>: comparacao com std::multiset (aleatorio)",
                   "[tree][random]", BinarySearchTree<int>,
                   DoublyLinkedBinarySearchTree<int>) {
  std::mt19937 rng(31337);
  TestType tree;
  std::multiset<int> reference;

  for (int step = 0; step < 4000; ++step) {
    int value = static_cast<int>(rng() % 100);

    if (rng() % 3 != 0) {
      tree.insert(value);
      reference.insert(value);
    } else {
      tree.remove(value);
      auto found = reference.find(value);
      if (found != reference.end()) {
        reference.erase(found);
      }
    }

    REQUIRE((tree.search(value) != nullptr) == (reference.count(value) > 0));
  }

  for (int v = 0; v < 100; ++v) {
    REQUIRE((tree.search(v) != nullptr) == (reference.count(v) > 0));
  }
}

TEST_CASE("DoublyLinkedBinarySearchTree: ponteiros para o pai",
          "[tree][doubly][parent]") {
  DoublyLinkedBinarySearchTree<int> tree;
  std::set<int> present;

  std::mt19937 rng(7);
  auto verifyParents = [&]() {
    for (int v : present) {
      auto *node = tree.search(v);
      REQUIRE(node != nullptr);

      auto *parent = node->getParent();
      if (parent != nullptr) {
        // o pai precisa apontar de volta para o filho
        REQUIRE((parent->getLeft() == node || parent->getRight() == node));
      }
      if (node->getLeft() != nullptr) {
        REQUIRE(node->getLeft()->getParent() == node);
      }
      if (node->getRight() != nullptr) {
        REQUIRE(node->getRight()->getParent() == node);
      }
    }
  };

  for (int step = 0; step < 600; ++step) {
    int value = static_cast<int>(rng() % 200);
    if (rng() % 3 != 0) {
      if (present.insert(value).second) { // evita duplicados no conjunto
        tree.insert(value);
      }
    } else if (present.erase(value) > 0) {
      tree.remove(value);
    }
    if (step % 20 == 0) {
      verifyParents();
    }
  }
  verifyParents();

  SECTION("a raiz nao possui pai") {
    DoublyLinkedBinarySearchTree<int> small;
    small.insert(2);
    small.insert(1);
    REQUIRE(small.search(2)->getParent() == nullptr);
    REQUIRE(small.search(1)->getParent() == small.search(2));
    small.remove(2);
    REQUIRE(small.search(1)->getParent() == nullptr);
  }
}

TEST_CASE("BinarySearchTreeInterface: uso polimorfico", "[tree][interface]") {
  std::unique_ptr<BinarySearchTreeInterface<int>> tree =
      std::make_unique<BinarySearchTree<int>>();
  tree->insert(2);
  tree->insert(1);
  REQUIRE(tree->search(1) != nullptr);
  tree->remove(1);
  REQUIRE(tree->search(1) == nullptr);

  std::unique_ptr<DoublyLinkedBinarySearchTreeInterface<int>> doubly =
      std::make_unique<DoublyLinkedBinarySearchTree<int>>();
  doubly->insert(2);
  REQUIRE(doubly->search(2) != nullptr);
}
