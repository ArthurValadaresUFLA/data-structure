// Testes Catch2 (v3) para ListInterface<T>:
//   - SinglyLinkedList<T>
//   - DoublyLinkedList<T>
//
// Contrato testado:
//   * insertAt(i) coloca o elemento na posição i; i >= size() insere ao final.
//   * find() retorna a posição da primeira ocorrência, ou size() se ausente.
//   * removeOnBegin/removeAtEnd em lista vazia lançam std::runtime_error;
//     removeAt/operator[] fora do intervalo lançam std::out_of_range.
//   * removeWhere recebe a posição do elemento na lista original.

#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>

#include <cstddef>
#include <list>
#include <memory>
#include <random>
#include <string>
#include <utility>
#include <vector>

#include "data-structure/list/DoublyLinkedList.h"
#include "data-structure/list/SinglyLinkedList.h"
#include "data-structure/list/interface/ListInterface.h"

namespace {

template <class L> std::vector<int> contents(const L &list) {
  std::vector<int> values;
  for (std::size_t i = 0; i < list.size(); ++i) {
    values.push_back(list[i]);
  }
  return values;
}

using Values = std::vector<int>;

} // namespace

TEMPLATE_TEST_CASE("List<int>: lista vazia", "[list][empty]",
                   SinglyLinkedList<int>, DoublyLinkedList<int>) {
  TestType list;

  REQUIRE(list.isEmpty());
  REQUIRE(list.size() == 0);
  REQUIRE_FALSE(list.contains(1));
  REQUIRE(list.find(1) == 0); // size() quando ausente

  REQUIRE_THROWS_AS(list.removeOnBegin(), std::runtime_error);
  REQUIRE_THROWS_AS(list.removeAtEnd(), std::runtime_error);
  REQUIRE_THROWS_AS(list.removeAt(0), std::out_of_range);
  REQUIRE_THROWS_AS(list[0], std::out_of_range);
}

TEMPLATE_TEST_CASE("List<int>: push e pushBack", "[list][add]",
                   SinglyLinkedList<int>, DoublyLinkedList<int>) {
  TestType list;

  SECTION("push insere no início") {
    list.push(1);
    list.push(2);
    list.push(3);
    REQUIRE(contents(list) == Values{3, 2, 1});
  }

  SECTION("pushBack insere no fim") {
    list.pushBack(1);
    list.pushBack(2);
    list.pushBack(3);
    REQUIRE(contents(list) == Values{1, 2, 3});
  }

  SECTION("push e pushBack combinados") {
    list.pushBack(2);
    list.push(1);
    list.pushBack(3);
    REQUIRE(contents(list) == Values{1, 2, 3});
    REQUIRE(list.size() == 3);
    REQUIRE_FALSE(list.isEmpty());
  }
}

TEMPLATE_TEST_CASE("List<int>: insertAt", "[list][insert]",
                   SinglyLinkedList<int>, DoublyLinkedList<int>) {
  TestType list;
  list.pushBack(10);
  list.pushBack(20);
  list.pushBack(30);

  SECTION("no início") {
    list.insertAt(0, 5);
    REQUIRE(contents(list) == Values{5, 10, 20, 30});
  }

  SECTION("no meio") {
    list.insertAt(1, 15);
    list.insertAt(3, 25);
    REQUIRE(contents(list) == Values{10, 15, 20, 25, 30});
  }

  SECTION("na posição size() insere ao final") {
    list.insertAt(3, 40);
    REQUIRE(contents(list) == Values{10, 20, 30, 40});
  }

  SECTION("posição além do tamanho insere ao final") {
    list.insertAt(100, 40);
    REQUIRE(contents(list) == Values{10, 20, 30, 40});
  }

  SECTION("em lista vazia") {
    TestType empty;
    empty.insertAt(5, 1);
    REQUIRE(contents(empty) == Values{1});
  }

  SECTION("o último inserido continua sendo o fim da lista") {
    list.insertAt(3, 40);
    list.pushBack(50);
    REQUIRE(contents(list) == Values{10, 20, 30, 40, 50});
    REQUIRE(list.removeAtEnd() == 50);
    REQUIRE(list.removeAtEnd() == 40);
  }
}

TEMPLATE_TEST_CASE("List<int>: remoções", "[list][remove]",
                   SinglyLinkedList<int>, DoublyLinkedList<int>) {
  TestType list;
  for (int v : {1, 2, 3, 4, 5}) {
    list.pushBack(v);
  }

  SECTION("removeOnBegin") {
    REQUIRE(list.removeOnBegin() == 1);
    REQUIRE(contents(list) == Values{2, 3, 4, 5});
  }

  SECTION("removeAtEnd") {
    REQUIRE(list.removeAtEnd() == 5);
    REQUIRE(contents(list) == Values{1, 2, 3, 4});
    list.pushBack(6); // o fim precisa ter sido atualizado
    REQUIRE(contents(list) == Values{1, 2, 3, 4, 6});
  }

  SECTION("removeAt no meio, início e fim") {
    REQUIRE(list.removeAt(2) == 3);
    REQUIRE(list.removeAt(0) == 1);
    REQUIRE(list.removeAt(2) == 5);
    REQUIRE(contents(list) == Values{2, 4});
  }

  SECTION("removeAt fora do intervalo") {
    REQUIRE_THROWS_AS(list.removeAt(5), std::out_of_range);
    REQUIRE(list.size() == 5);
  }

  SECTION("remover todos os elementos deixa a lista reutilizável") {
    while (!list.isEmpty()) {
      list.removeOnBegin();
    }
    REQUIRE(list.size() == 0);
    REQUIRE_THROWS_AS(list.removeAtEnd(), std::runtime_error);
    list.push(7);
    list.pushBack(8);
    REQUIRE(contents(list) == Values{7, 8});
  }

  SECTION("remover o único elemento pelo fim") {
    TestType single;
    single.push(1);
    REQUIRE(single.removeAtEnd() == 1);
    REQUIRE(single.isEmpty());
    single.pushBack(2);
    REQUIRE(contents(single) == Values{2});
  }
}

TEMPLATE_TEST_CASE("List<int>: busca e acesso", "[list][find]",
                   SinglyLinkedList<int>, DoublyLinkedList<int>) {
  TestType list;
  for (int v : {10, 20, 30, 20}) {
    list.pushBack(v);
  }

  SECTION("find retorna a primeira ocorrência") {
    REQUIRE(list.find(10) == 0);
    REQUIRE(list.find(20) == 1);
    REQUIRE(list.find(30) == 2);
  }

  SECTION("find de valor ausente retorna size()") {
    REQUIRE(list.find(99) == list.size());
  }

  SECTION("contains inclui o primeiro e o último elemento") {
    REQUIRE(list.contains(10));
    REQUIRE(list.contains(20));
    REQUIRE_FALSE(list.contains(99));
  }

  SECTION("operator[] lê e escreve") {
    REQUIRE(list[2] == 30);
    list[2] = 99;
    REQUIRE(list[2] == 99);
    REQUIRE(list.contains(99));
    REQUIRE_FALSE(list.contains(30));
  }

  SECTION("operator[] fora do intervalo") {
    REQUIRE_THROWS_AS(list[4], std::out_of_range);
  }

  SECTION("funciona em objeto const") {
    const TestType &ref = list;
    REQUIRE(ref.size() == 4);
    REQUIRE(ref[0] == 10);
    REQUIRE(ref.contains(30));
  }
}

TEMPLATE_TEST_CASE("List<int>: removeWhere", "[list][removeWhere]",
                   SinglyLinkedList<int>, DoublyLinkedList<int>) {
  TestType list;
  for (int v : {1, 2, 3, 4, 5, 6}) {
    list.pushBack(v);
  }

  SECTION("remove por valor") {
    list.removeWhere([](std::size_t, int v) { return v % 2 == 0; });
    REQUIRE(contents(list) == Values{1, 3, 5});
  }

  SECTION("a posição é a da lista original") {
    std::vector<std::size_t> seen;
    list.removeWhere([&seen](std::size_t index, int) {
      seen.push_back(index);
      return index < 3;
    });
    REQUIRE(seen == std::vector<std::size_t>{0, 1, 2, 3, 4, 5});
    REQUIRE(contents(list) == Values{4, 5, 6});
  }

  SECTION("remover o primeiro e o último") {
    list.removeWhere([](std::size_t, int v) { return v == 1 || v == 6; });
    REQUIRE(contents(list) == Values{2, 3, 4, 5});
    list.pushBack(7); // o fim precisa ter sido atualizado
    REQUIRE(contents(list) == Values{2, 3, 4, 5, 7});
    REQUIRE(list.removeAtEnd() == 7);
  }

  SECTION("remover tudo") {
    list.removeWhere([](std::size_t, int) { return true; });
    REQUIRE(list.isEmpty());
    list.push(1);
    REQUIRE(contents(list) == Values{1});
  }

  SECTION("nenhuma correspondência") {
    list.removeWhere([](std::size_t, int) { return false; });
    REQUIRE(list.size() == 6);
  }
}

TEMPLATE_TEST_CASE("List<int>: cópia e movimentação", "[list][copy]",
                   SinglyLinkedList<int>, DoublyLinkedList<int>) {
  TestType list;
  for (int v : {1, 2, 3}) {
    list.pushBack(v);
  }

  SECTION("a cópia é profunda e preserva a ordem") {
    TestType copy(list);
    list.removeOnBegin();
    copy.pushBack(4);
    REQUIRE(contents(list) == Values{2, 3});
    REQUIRE(contents(copy) == Values{1, 2, 3, 4});
  }

  SECTION("cópia de lista vazia") {
    TestType empty;
    TestType copy(empty);
    REQUIRE(copy.isEmpty());
    copy.pushBack(1);
    REQUIRE(contents(copy) == Values{1});
  }

  SECTION("atribuição por cópia") {
    TestType other;
    other.push(99);
    other = list;
    REQUIRE(contents(other) == Values{1, 2, 3});
    other.removeAtEnd();
    REQUIRE(contents(list) == Values{1, 2, 3});
  }

  SECTION("auto-atribuição é segura") {
    auto &alias = list;
    list = alias;
    REQUIRE(contents(list) == Values{1, 2, 3});
  }

  SECTION("movimentação esvazia a origem") {
    TestType moved(std::move(list));
    REQUIRE(contents(moved) == Values{1, 2, 3});
    REQUIRE(list.isEmpty()); // NOLINT: estado apos mover e especificado
    list.push(5);
    REQUIRE(contents(list) == Values{5});
  }

  SECTION("atribuição por movimentação") {
    TestType other;
    other.push(99);
    other = std::move(list);
    REQUIRE(contents(other) == Values{1, 2, 3});
  }
}

TEMPLATE_TEST_CASE("List<std::string>: operações básicas", "[list][string]",
                   SinglyLinkedList<std::string>,
                   DoublyLinkedList<std::string>) {
  TestType list;
  list.pushBack("b");
  list.push("a");
  list.pushBack("c");

  REQUIRE(list[0] == "a");
  REQUIRE(list[2] == "c");
  REQUIRE(list.find("b") == 1);
  list[1] = "bb";
  REQUIRE(list.contains("bb"));
  REQUIRE(list.removeAt(1) == "bb");
  REQUIRE(list.size() == 2);
}

TEMPLATE_TEST_CASE("List<int>: comparação com std::list (aleatório)",
                   "[list][random]", SinglyLinkedList<int>,
                   DoublyLinkedList<int>) {
  std::mt19937 rng(12345);
  TestType list;
  std::list<int> reference;

  for (int step = 0; step < 5000; ++step) {
    int value = static_cast<int>(rng() % 20);

    switch (rng() % 6) {
    case 0:
      list.push(value);
      reference.push_front(value);
      break;
    case 1:
      list.pushBack(value);
      reference.push_back(value);
      break;
    case 2: {
      std::size_t index = rng() % (reference.size() + 2);
      list.insertAt(index, value);
      reference.insert(
          std::next(reference.begin(), std::min(index, reference.size())),
          value);
      break;
    }
    case 3:
      if (!reference.empty()) {
        REQUIRE(list.removeOnBegin() == reference.front());
        reference.pop_front();
      }
      break;
    case 4:
      if (!reference.empty()) {
        REQUIRE(list.removeAtEnd() == reference.back());
        reference.pop_back();
      }
      break;
    default:
      list.removeWhere([value](std::size_t, int v) { return v == value; });
      reference.remove(value);
      break;
    }

    REQUIRE(list.size() == reference.size());
  }

  REQUIRE(contents(list) == Values(reference.begin(), reference.end()));
}

TEST_CASE("ListInterface: uso polimórfico", "[list][interface]") {
  std::vector<std::unique_ptr<ListInterface<int>>> lists;
  lists.push_back(std::make_unique<SinglyLinkedList<int>>());
  lists.push_back(std::make_unique<DoublyLinkedList<int>>());

  for (auto &list : lists) {
    REQUIRE(list->isEmpty());
    list->pushBack(2);
    list->push(1);
    list->insertAt(2, 3);
    REQUIRE(list->size() == 3);
    REQUIRE((*list)[1] == 2);
    REQUIRE(list->removeAt(1) == 2);
    REQUIRE(list->removeOnBegin() == 1);
    REQUIRE(list->removeAtEnd() == 3);
    REQUIRE(list->isEmpty());
  }
}
