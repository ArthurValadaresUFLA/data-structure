// Testes Catch2 (v3) para QueueInterface<T>:
//   - ArrayQueue<T>  (buffer circular, capacidade fixa)
//   - LinkedQueue<T> (capacidade ilimitada)

#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>

#include <cstddef>
#include <memory>
#include <queue>
#include <random>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

#include "data-structure/queue/ArrayQueue.h"
#include "data-structure/queue/LinkedQueue.h"
#include "data-structure/queue/interface/QueueInterface.h"

namespace {

constexpr std::size_t kCapacity = 128;

template <class Q> Q makeQueue(std::size_t capacity = kCapacity) {
  if constexpr (std::is_constructible_v<Q, std::size_t>) {
    return Q(capacity);
  } else {
    return Q();
  }
}

} // namespace

TEMPLATE_TEST_CASE("Queue<int>: fila vazia", "[queue][empty]",
                   ArrayQueue<int>, LinkedQueue<int>) {
  TestType queue = makeQueue<TestType>();

  REQUIRE(queue.isEmpty());
  REQUIRE(queue.size() == 0);
  REQUIRE_THROWS_AS(queue.dequeue(), std::runtime_error);
  REQUIRE_THROWS_AS(queue.peek(), std::runtime_error);
}

TEMPLATE_TEST_CASE("Queue<int>: ordem FIFO", "[queue][fifo]", ArrayQueue<int>,
                   LinkedQueue<int>) {
  TestType queue = makeQueue<TestType>();

  queue.queue(1);
  queue.queue(2);
  queue.queue(3);

  REQUIRE_FALSE(queue.isEmpty());
  REQUIRE(queue.size() == 3);
  REQUIRE(queue.peek() == 1); // o proximo a sair e o primeiro a entrar
  REQUIRE(queue.peek() == 1); // peek nao remove

  REQUIRE(queue.dequeue() == 1);
  REQUIRE(queue.dequeue() == 2);
  REQUIRE(queue.size() == 1);
  REQUIRE(queue.peek() == 3);
  REQUIRE(queue.dequeue() == 3);

  REQUIRE(queue.isEmpty());
  REQUIRE_THROWS_AS(queue.dequeue(), std::runtime_error);
}

TEMPLATE_TEST_CASE("Queue<int>: reutilização após esvaziar", "[queue][reuse]",
                   ArrayQueue<int>, LinkedQueue<int>) {
  TestType queue = makeQueue<TestType>(4);

  for (int round = 0; round < 10; ++round) {
    for (int v = 0; v < 4; ++v) {
      queue.queue(round * 10 + v);
    }
    for (int v = 0; v < 4; ++v) {
      REQUIRE(queue.dequeue() == round * 10 + v);
    }
    REQUIRE(queue.isEmpty());
  }
}

TEMPLATE_TEST_CASE("Queue<int>: cópia e movimentação", "[queue][copy]",
                   ArrayQueue<int>, LinkedQueue<int>) {
  TestType queue = makeQueue<TestType>(8);
  queue.queue(1);
  queue.queue(2);
  queue.queue(3);

  SECTION("a cópia é profunda e preserva a ordem") {
    TestType copy(queue);
    queue.dequeue();
    copy.queue(4);

    REQUIRE(queue.size() == 2);
    REQUIRE(copy.size() == 4);
    REQUIRE(copy.dequeue() == 1);
    REQUIRE(copy.dequeue() == 2);
    REQUIRE(copy.dequeue() == 3);
    REQUIRE(copy.dequeue() == 4);
    REQUIRE(queue.peek() == 2);
  }

  SECTION("cópia de fila que deu a volta no buffer") {
    // forca o inicio a andar para o meio do array circular
    TestType wrapped = makeQueue<TestType>(4);
    for (int v : {1, 2, 3, 4}) {
      wrapped.queue(v);
    }
    wrapped.dequeue();
    wrapped.dequeue();
    wrapped.queue(5);
    wrapped.queue(6);

    TestType copy(wrapped);
    for (int v : {3, 4, 5, 6}) {
      REQUIRE(copy.dequeue() == v);
    }
    REQUIRE(wrapped.size() == 4);
  }

  SECTION("atribuição por cópia") {
    TestType other = makeQueue<TestType>(8);
    other.queue(99);
    other = queue;
    REQUIRE(other.size() == 3);
    REQUIRE(other.peek() == 1);
    other.dequeue();
    REQUIRE(queue.size() == 3);
  }

  SECTION("auto-atribuição é segura") {
    auto &alias = queue;
    queue = alias;
    REQUIRE(queue.size() == 3);
    REQUIRE(queue.peek() == 1);
  }

  SECTION("movimentação") {
    TestType moved(std::move(queue));
    REQUIRE(moved.size() == 3);
    REQUIRE(moved.dequeue() == 1);
  }

  SECTION("atribuição por movimentação") {
    TestType other = makeQueue<TestType>(8);
    other = std::move(queue);
    REQUIRE(other.size() == 3);
    REQUIRE(other.peek() == 1);
  }
}

TEMPLATE_TEST_CASE("Queue<std::string>: operações básicas", "[queue][string]",
                   ArrayQueue<std::string>, LinkedQueue<std::string>) {
  TestType queue = makeQueue<TestType>();

  queue.queue("a");
  queue.queue("");
  queue.queue("c");

  REQUIRE(queue.dequeue() == "a");
  REQUIRE(queue.dequeue() == "");
  REQUIRE(queue.peek() == "c");
}

TEMPLATE_TEST_CASE("Queue<int>: comparação com std::queue (aleatório)",
                   "[queue][random]", ArrayQueue<int>, LinkedQueue<int>) {
  std::mt19937 rng(2024);
  constexpr std::size_t capacity = 37;
  TestType queue = makeQueue<TestType>(capacity);
  std::queue<int> reference;

  for (int step = 0; step < 5000; ++step) {
    if (rng() % 2 == 0 && reference.size() < capacity) {
      int value = static_cast<int>(rng() % 1000);
      queue.queue(value);
      reference.push(value);
    } else if (!reference.empty()) {
      REQUIRE(queue.peek() == reference.front());
      REQUIRE(queue.dequeue() == reference.front());
      reference.pop();
    }

    REQUIRE(queue.size() == reference.size());
    REQUIRE(queue.isEmpty() == reference.empty());
  }
}

TEST_CASE("ArrayQueue: capacidade fixa", "[queue][array][capacity]") {
  ArrayQueue<int> queue(3);

  REQUIRE(queue.getCapacity() == 3);
  REQUIRE_FALSE(queue.isFull());

  queue.queue(1);
  queue.queue(2);
  queue.queue(3);

  REQUIRE(queue.isFull());
  REQUIRE_THROWS_AS(queue.queue(4), std::runtime_error);
  REQUIRE(queue.size() == 3);

  SECTION("desenfileirar libera espaço e o buffer dá a volta") {
    REQUIRE(queue.dequeue() == 1);
    REQUIRE_FALSE(queue.isFull());
    REQUIRE_NOTHROW(queue.queue(4));
    REQUIRE(queue.isFull());
    REQUIRE(queue.dequeue() == 2);
    REQUIRE(queue.dequeue() == 3);
    REQUIRE(queue.dequeue() == 4);
    REQUIRE(queue.isEmpty());
  }
}

TEST_CASE("ArrayQueue: capacidade zero", "[queue][array][capacity]") {
  ArrayQueue<int> queue(0);

  REQUIRE(queue.isEmpty());
  REQUIRE(queue.isFull());
  REQUIRE_THROWS_AS(queue.queue(1), std::runtime_error);
  REQUIRE_THROWS_AS(queue.dequeue(), std::runtime_error);
}

TEST_CASE("LinkedQueue: muitos elementos", "[queue][linked][stress]") {
  LinkedQueue<int> queue;
  constexpr int N = 100000;

  for (int i = 0; i < N; ++i) {
    queue.queue(i);
  }
  REQUIRE(queue.size() == static_cast<std::size_t>(N));

  // O destrutor libera os nós restantes sem recursão.
  for (int i = 0; i < N / 2; ++i) {
    REQUIRE(queue.dequeue() == i);
  }
}

TEST_CASE("QueueInterface: uso polimórfico", "[queue][interface]") {
  std::vector<std::unique_ptr<QueueInterface<int>>> queues;
  queues.push_back(std::make_unique<ArrayQueue<int>>(10));
  queues.push_back(std::make_unique<LinkedQueue<int>>());

  for (auto &queue : queues) {
    REQUIRE(queue->isEmpty());
    queue->queue(1);
    queue->queue(2);
    REQUIRE(queue->size() == 2);
    REQUIRE(queue->peek() == 1);
    REQUIRE(queue->dequeue() == 1);
    REQUIRE(queue->dequeue() == 2);
    REQUIRE(queue->isEmpty());
  }
}
