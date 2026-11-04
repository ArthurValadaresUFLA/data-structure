// Testes Catch2 (v3) para StackInterface<T>:
//   - ArrayStack<T>  (capacidade fixa)
//   - LinkedStack<T> (capacidade ilimitada)

#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>

#include <cstddef>
#include <memory>
#include <random>
#include <stack>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

#include "data-structure/stack/ArrayStack.h"
#include "data-structure/stack/LinkedStack.h"
#include "data-structure/stack/interface/StackInterface.h"

namespace {

constexpr std::size_t kCapacity = 128;

// ArrayStack precisa de capacidade; LinkedStack nao.
template <class S> S makeStack(std::size_t capacity = kCapacity) {
  if constexpr (std::is_constructible_v<S, std::size_t>) {
    return S(capacity);
  } else {
    return S();
  }
}

} // namespace

TEMPLATE_TEST_CASE("Stack<int>: pilha vazia", "[stack][empty]",
                   ArrayStack<int>, LinkedStack<int>) {
  TestType stack = makeStack<TestType>();

  REQUIRE(stack.empty());
  REQUIRE(stack.size() == 0);
  REQUIRE_THROWS_AS(stack.unstack(), std::runtime_error);
  REQUIRE_THROWS_AS(stack.peek(), std::runtime_error);
}

TEMPLATE_TEST_CASE("Stack<int>: ordem LIFO", "[stack][lifo]", ArrayStack<int>,
                   LinkedStack<int>) {
  TestType stack = makeStack<TestType>();

  stack.stackUp(1);
  stack.stackUp(2);
  stack.stackUp(3);

  REQUIRE_FALSE(stack.empty());
  REQUIRE(stack.size() == 3);
  REQUIRE(stack.peek() == 3);
  REQUIRE(stack.peek() == 3); // peek nao remove

  REQUIRE(stack.unstack() == 3);
  REQUIRE(stack.unstack() == 2);
  REQUIRE(stack.size() == 1);
  REQUIRE(stack.unstack() == 1);

  REQUIRE(stack.empty());
  REQUIRE_THROWS_AS(stack.unstack(), std::runtime_error);
}

TEMPLATE_TEST_CASE("Stack<int>: reutilização após esvaziar", "[stack][reuse]",
                   ArrayStack<int>, LinkedStack<int>) {
  TestType stack = makeStack<TestType>();

  for (int round = 0; round < 3; ++round) {
    for (int v = 0; v < 10; ++v) {
      stack.stackUp(v);
    }
    for (int v = 9; v >= 0; --v) {
      REQUIRE(stack.unstack() == v);
    }
    REQUIRE(stack.empty());
  }
}

TEMPLATE_TEST_CASE("Stack<int>: cópia e movimentação", "[stack][copy]",
                   ArrayStack<int>, LinkedStack<int>) {
  TestType stack = makeStack<TestType>();
  stack.stackUp(1);
  stack.stackUp(2);
  stack.stackUp(3);

  SECTION("a cópia é profunda e preserva a ordem") {
    TestType copy(stack);
    stack.unstack();
    copy.stackUp(4);

    REQUIRE(stack.size() == 2);
    REQUIRE(copy.size() == 4);
    REQUIRE(copy.unstack() == 4);
    REQUIRE(copy.unstack() == 3);
    REQUIRE(copy.unstack() == 2);
    REQUIRE(copy.unstack() == 1);
    REQUIRE(stack.peek() == 2);
  }

  SECTION("cópia de pilha vazia") {
    TestType empty = makeStack<TestType>();
    TestType copy(empty);
    REQUIRE(copy.empty());
  }

  SECTION("atribuição por cópia") {
    TestType other = makeStack<TestType>();
    other.stackUp(99);
    other = stack;
    REQUIRE(other.size() == 3);
    REQUIRE(other.peek() == 3);
    other.unstack();
    REQUIRE(stack.size() == 3);
  }

  SECTION("auto-atribuição é segura") {
    auto &alias = stack;
    stack = alias;
    REQUIRE(stack.size() == 3);
    REQUIRE(stack.peek() == 3);
  }

  SECTION("movimentação") {
    TestType moved(std::move(stack));
    REQUIRE(moved.size() == 3);
    REQUIRE(moved.unstack() == 3);
  }

  SECTION("atribuição por movimentação") {
    TestType other = makeStack<TestType>();
    other = std::move(stack);
    REQUIRE(other.size() == 3);
    REQUIRE(other.peek() == 3);
  }
}

TEMPLATE_TEST_CASE("Stack<std::string>: operações básicas", "[stack][string]",
                   ArrayStack<std::string>, LinkedStack<std::string>) {
  TestType stack = makeStack<TestType>();

  stack.stackUp("a");
  stack.stackUp("");
  stack.stackUp("c");

  REQUIRE(stack.unstack() == "c");
  REQUIRE(stack.unstack() == "");
  REQUIRE(stack.peek() == "a");
}

TEMPLATE_TEST_CASE("Stack<int>: comparação com std::stack (aleatório)",
                   "[stack][random]", ArrayStack<int>, LinkedStack<int>) {
  std::mt19937 rng(777);
  TestType stack = makeStack<TestType>(50);
  std::stack<int> reference;

  for (int step = 0; step < 5000; ++step) {
    if (rng() % 2 == 0 && reference.size() < 50) {
      int value = static_cast<int>(rng() % 1000);
      stack.stackUp(value);
      reference.push(value);
    } else if (!reference.empty()) {
      REQUIRE(stack.peek() == reference.top());
      REQUIRE(stack.unstack() == reference.top());
      reference.pop();
    }

    REQUIRE(stack.size() == reference.size());
    REQUIRE(stack.empty() == reference.empty());
  }
}

TEST_CASE("ArrayStack: capacidade fixa", "[stack][array][capacity]") {
  ArrayStack<int> stack(3);

  REQUIRE(stack.getCapacity() == 3);
  REQUIRE_FALSE(stack.isFull());

  stack.stackUp(1);
  stack.stackUp(2);
  stack.stackUp(3);

  REQUIRE(stack.isFull());
  REQUIRE_THROWS_AS(stack.stackUp(4), std::runtime_error);
  REQUIRE(stack.size() == 3);
  REQUIRE(stack.peek() == 3);

  stack.unstack();
  REQUIRE_FALSE(stack.isFull());
  REQUIRE_NOTHROW(stack.stackUp(5));
}

TEST_CASE("ArrayStack: capacidade zero", "[stack][array][capacity]") {
  ArrayStack<int> stack(0);

  REQUIRE(stack.empty());
  REQUIRE(stack.isFull());
  REQUIRE_THROWS_AS(stack.stackUp(1), std::runtime_error);
  REQUIRE_THROWS_AS(stack.unstack(), std::runtime_error);
}

TEST_CASE("LinkedStack: muitos elementos", "[stack][linked][stress]") {
  LinkedStack<int> stack;
  constexpr int N = 100000;

  for (int i = 0; i < N; ++i) {
    stack.stackUp(i);
  }
  REQUIRE(stack.size() == static_cast<std::size_t>(N));

  // O destrutor libera os nós restantes sem recursão (não estoura a pilha).
  for (int i = N - 1; i >= N / 2; --i) {
    REQUIRE(stack.unstack() == i);
  }
}

TEST_CASE("StackInterface: uso polimórfico", "[stack][interface]") {
  std::vector<std::unique_ptr<StackInterface<int>>> stacks;
  stacks.push_back(std::make_unique<ArrayStack<int>>(10));
  stacks.push_back(std::make_unique<LinkedStack<int>>());

  for (auto &stack : stacks) {
    REQUIRE(stack->empty());
    stack->stackUp(1);
    stack->stackUp(2);
    REQUIRE(stack->size() == 2);
    REQUIRE(stack->peek() == 2);
    REQUIRE(stack->unstack() == 2);
    REQUIRE(stack->unstack() == 1);
    REQUIRE(stack->empty());
  }
}
