// Testes Catch2 (v3) para HeapInterface<T>:
//   - MaxHeap<T>    (raiz = maior elemento)
//   - MinHeap<T>    (raiz = menor elemento)
//   - Tournament<T> (árvore de torneio; o campeão é o maior elemento)
//
// Contrato testado:
//   * A capacidade é fixa: insert() em um heap cheio lança std::runtime_error.
//   * removeRoot()/peekRoot() em heap vazio lançam std::out_of_range.
//   * parentOf/leftChildOf/rightChildOf seguem o layout de array
//     (filhos de i em 2i+1 e 2i+2).

#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>

#include <algorithm>
#include <cstddef>
#include <functional>
#include <memory>
#include <random>
#include <set>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

#include "data-structure/heap/MaxHeap.h"
#include "data-structure/heap/MinHeap.h"
#include "data-structure/heap/Tournament.h"
#include "data-structure/heap/interface/HeapInterface.h"

namespace {

// Valores em ordem de saída (a raiz primeiro) para cada tipo de heap.
template <class H> std::vector<int> expectedOrder(std::vector<int> values) {
  if constexpr (std::is_same_v<H, MinHeap<int>>) {
    std::sort(values.begin(), values.end());
  } else {
    std::sort(values.begin(), values.end(), std::greater<int>());
  }
  return values;
}

template <class H> std::vector<int> drain(H &heap) {
  std::vector<int> values;
  while (!heap.isEmpty()) {
    values.push_back(heap.removeRoot());
  }
  return values;
}

using Values = std::vector<int>;

} // namespace

TEMPLATE_TEST_CASE("Heap<int>: heap vazio", "[heap][empty]", MaxHeap<int>,
                   MinHeap<int>, Tournament<int>) {
  TestType heap(8);

  REQUIRE(heap.isEmpty());
  REQUIRE_FALSE(heap.isFull());
  REQUIRE(heap.getSize() == 0);
  REQUIRE(heap.getCapacity() == 8);
  REQUIRE_THROWS_AS(heap.peekRoot(), std::out_of_range);
  REQUIRE_THROWS_AS(heap.removeRoot(), std::out_of_range);
}

TEMPLATE_TEST_CASE("Heap<int>: insercao e remocao em ordem", "[heap][order]",
                   MaxHeap<int>, MinHeap<int>, Tournament<int>) {
  TestType heap(16);
  Values input{5, 3, 9, 1, 7, 3, 8, -2, 0, 9};

  for (int v : input) {
    heap.insert(v);
  }

  REQUIRE(heap.getSize() == input.size());
  REQUIRE(heap.peekRoot() == expectedOrder<TestType>(input).front());
  REQUIRE(drain(heap) == expectedOrder<TestType>(input));
  REQUIRE(heap.isEmpty());
}

TEMPLATE_TEST_CASE("Heap<int>: peekRoot nao remove", "[heap][peek]",
                   MaxHeap<int>, MinHeap<int>, Tournament<int>) {
  TestType heap(4);
  heap.insert(2);
  heap.insert(1);

  const int root = heap.peekRoot();
  REQUIRE(heap.peekRoot() == root);
  REQUIRE(heap.getSize() == 2);
}

TEMPLATE_TEST_CASE("Heap<int>: capacidade fixa", "[heap][capacity]",
                   MaxHeap<int>, MinHeap<int>, Tournament<int>) {
  TestType heap(3);
  heap.insert(1);
  heap.insert(2);
  heap.insert(3);

  REQUIRE(heap.isFull());
  REQUIRE_THROWS_AS(heap.insert(4), std::runtime_error);
  REQUIRE(heap.getSize() == 3);

  SECTION("remover libera espaco") {
    heap.removeRoot();
    REQUIRE_FALSE(heap.isFull());
    REQUIRE_NOTHROW(heap.insert(4));
    REQUIRE(heap.isFull());
  }
}

TEMPLATE_TEST_CASE("Heap<int>: capacidade um", "[heap][capacity]",
                   MaxHeap<int>, MinHeap<int>, Tournament<int>) {
  TestType heap(1);

  heap.insert(7);
  REQUIRE(heap.isFull());
  REQUIRE(heap.peekRoot() == 7);
  REQUIRE(heap.removeRoot() == 7);
  REQUIRE(heap.isEmpty());

  heap.insert(8);
  REQUIRE(heap.removeRoot() == 8);
}

TEMPLATE_TEST_CASE("Heap<int>: reutilizacao e duplicados", "[heap][reuse]",
                   MaxHeap<int>, MinHeap<int>, Tournament<int>) {
  TestType heap(10);

  for (int round = 0; round < 5; ++round) {
    for (int i = 0; i < 6; ++i) {
      heap.insert(i % 3); // muitos duplicados
    }
    REQUIRE(drain(heap) == expectedOrder<TestType>({0, 1, 2, 0, 1, 2}));
  }
}

TEMPLATE_TEST_CASE("Heap<int>: from(array, n)", "[heap][from]", MaxHeap<int>,
                   MinHeap<int>, Tournament<int>) {
  const int array[] = {4, 8, 1, 9, 3};

  TestType heap = TestType::from(array, 5);

  REQUIRE(heap.getSize() == 5);
  REQUIRE(heap.getCapacity() == 5);
  REQUIRE(heap.isFull());
  REQUIRE(drain(heap) == expectedOrder<TestType>({4, 8, 1, 9, 3}));

  SECTION("array vazio") {
    TestType empty = TestType::from(array, 0);
    REQUIRE(empty.isEmpty());
  }
}

TEMPLATE_TEST_CASE("Heap<int>: indices de pai e filhos", "[heap][index]",
                   MaxHeap<int>, MinHeap<int>, Tournament<int>) {
  TestType heap(8);

  REQUIRE(heap.leftChildOf(0) == 1);
  REQUIRE(heap.rightChildOf(0) == 2);
  REQUIRE(heap.leftChildOf(3) == 7);
  REQUIRE(heap.rightChildOf(3) == 8);
  REQUIRE(heap.parentOf(1) == 0);
  REQUIRE(heap.parentOf(2) == 0);
  REQUIRE(heap.parentOf(7) == 3);
  REQUIRE(heap.parentOf(8) == 3);
  REQUIRE(heap.parentOf(0) == 0); // a raiz e pai de si mesma
}

TEMPLATE_TEST_CASE("Heap<int>: copia e movimentacao", "[heap][copy]",
                   MaxHeap<int>, MinHeap<int>, Tournament<int>) {
  TestType heap(8);
  for (int v : {3, 1, 4, 1, 5}) {
    heap.insert(v);
  }
  const Values expected = expectedOrder<TestType>({3, 1, 4, 1, 5});

  SECTION("a copia e independente do original") {
    TestType copy(heap);
    heap.removeRoot();
    copy.insert(100);

    REQUIRE(heap.getSize() == 4);
    REQUIRE(copy.getSize() == 6);
    REQUIRE(drain(copy).size() == 6);
  }

  SECTION("atribuicao por copia") {
    TestType other(2);
    other.insert(99);
    other = heap;

    REQUIRE(other.getCapacity() == 8);
    REQUIRE(drain(other) == expected);
    REQUIRE(heap.getSize() == 5);
  }

  SECTION("auto-atribuicao e segura") {
    auto &alias = heap;
    heap = alias;
    REQUIRE(drain(heap) == expected);
  }

  SECTION("construtor de movimentacao") {
    TestType moved(std::move(heap));
    REQUIRE(drain(moved) == expected);
  }

  SECTION("atribuicao por movimentacao") {
    TestType other(2);
    other.insert(99);
    other = std::move(heap);
    REQUIRE(drain(other) == expected);
  }
}

TEMPLATE_TEST_CASE("Heap<std::string>: operacoes basicas", "[heap][string]",
                   MaxHeap<std::string>, MinHeap<std::string>) {
  TestType heap(4);
  heap.insert("banana");
  heap.insert("abacaxi");
  heap.insert("cereja");

  const bool isMin = std::is_same_v<TestType, MinHeap<std::string>>;
  REQUIRE(heap.removeRoot() == (isMin ? "abacaxi" : "cereja"));
  REQUIRE(heap.removeRoot() == "banana");
  REQUIRE(heap.removeRoot() == (isMin ? "cereja" : "abacaxi"));
}

TEMPLATE_TEST_CASE("Heap<int>: comparacao com std::multiset (aleatorio)",
                   "[heap][random]", MaxHeap<int>, MinHeap<int>,
                   Tournament<int>) {
  std::mt19937 rng(99);
  constexpr std::size_t capacity = 13;
  TestType heap(capacity);
  std::multiset<int> reference;

  for (int step = 0; step < 5000; ++step) {
    if (rng() % 2 == 0 && reference.size() < capacity) {
      int value = static_cast<int>(rng() % 50);
      heap.insert(value);
      reference.insert(value);
    } else if (!reference.empty()) {
      int expected = std::is_same_v<TestType, MinHeap<int>>
                         ? *reference.begin()
                         : *reference.rbegin();
      REQUIRE(heap.peekRoot() == expected);
      REQUIRE(heap.removeRoot() == expected);
      if constexpr (std::is_same_v<TestType, MinHeap<int>>) {
        reference.erase(reference.begin());
      } else {
        reference.erase(std::prev(reference.end()));
      }
    }
    REQUIRE(heap.getSize() == reference.size());
  }
}

TEST_CASE("MaxHeap/MinHeap: operator[] expoe o array do heap",
          "[heap][index]") {
  MaxHeap<int> max(8);
  for (int v : {3, 9, 5, 1}) {
    max.insert(v);
  }

  REQUIRE(max[0] == 9); // raiz
  REQUIRE(max[0] == max.peekRoot());
  for (std::size_t i = 1; i < max.getSize(); ++i) {
    REQUIRE(max[max.parentOf(i)] >= max[i]); // propriedade do heap maximo
  }
  REQUIRE_THROWS_AS(max[max.getSize()], std::out_of_range);

  MinHeap<int> min(8);
  for (int v : {3, 9, 5, 1}) {
    min.insert(v);
  }
  for (std::size_t i = 1; i < min.getSize(); ++i) {
    REQUIRE(min[min.parentOf(i)] <= min[i]); // propriedade do heap minimo
  }
}

TEST_CASE("AbstractHeap: igualdade entre heaps", "[heap][equality]") {
  MaxHeap<int> a(4);
  MaxHeap<int> b(4);
  a.insert(1);
  a.insert(2);
  b.insert(1);
  b.insert(2);

  REQUIRE(a == b);
  b.insert(3);
  REQUIRE_FALSE(a == b);
}

TEST_CASE("Tournament: operator[] acessa nos da arvore", "[heap][tournament]") {
  Tournament<int> tournament(4);

  REQUIRE_THROWS_AS(tournament[0], std::out_of_range); // raiz vazia

  tournament.insert(3);
  tournament.insert(8);
  tournament.insert(5);

  REQUIRE(tournament[0] == 8); // campeao na raiz
  REQUIRE(tournament[0] == tournament.peekRoot());
  REQUIRE_THROWS_AS(tournament[100], std::out_of_range);
}

TEST_CASE("Tournament: capacidade que nao e potencia de dois",
          "[heap][tournament]") {
  Tournament<int> tournament(5);

  for (int v : {4, 7, 2, 9, 1}) {
    tournament.insert(v);
  }
  REQUIRE(tournament.isFull());
  REQUIRE_THROWS_AS(tournament.insert(0), std::runtime_error);

  REQUIRE(tournament.removeRoot() == 9);
  REQUIRE(tournament.removeRoot() == 7);
  tournament.insert(10); // reaproveita a folha liberada
  REQUIRE(tournament.peekRoot() == 10);
  REQUIRE(tournament.removeRoot() == 10);
  REQUIRE(tournament.removeRoot() == 4);
  REQUIRE(tournament.removeRoot() == 2);
  REQUIRE(tournament.removeRoot() == 1);
  REQUIRE(tournament.isEmpty());
}

TEST_CASE("HeapInterface: uso polimorfico", "[heap][interface]") {
  std::vector<std::unique_ptr<HeapInterface<int>>> heaps;
  heaps.push_back(std::make_unique<MaxHeap<int>>(8));
  heaps.push_back(std::make_unique<MinHeap<int>>(8));
  heaps.push_back(std::make_unique<Tournament<int>>(8));

  for (auto &heap : heaps) {
    REQUIRE(heap->isEmpty());
    heap->insert(2);
    heap->insert(1);
    heap->insert(3);
    REQUIRE(heap->getSize() == 3);
    heap->removeRoot();
    REQUIRE(heap->getSize() == 2);
  }
}
