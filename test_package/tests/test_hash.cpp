// Testes Catch2 (v3) para as implementações de HashTableInterface<T>:
//   - LinkedHashTable<T>      (encadeamento externo)
//   - OpenAddressHashTable<T> (endereçamento aberto, sondagem linear)
//
// Contrato testado:
//   * As tabelas são construídas com (capacidade, função hash). O resultado da
//     função hash é reduzido módulo a capacidade.
//   * Semântica de conjunto: adicionar um valor já presente não cria uma
//     segunda cópia (um único remove() basta para eliminá-lo).
//   * remove() de valor inexistente é silencioso (não lança exceção).
//   * A capacidade é fixa: a tabela de endereçamento aberto lança
//     std::runtime_error ao receber um valor novo quando está cheia. A tabela
//     encadeada nunca fica "cheia".
//   * Uma tabela construída por padrão não tem capacidade e lança
//     std::logic_error ao ser usada.

#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>

#include <cstddef>
#include <functional>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "data-structure/hash/LinkedHashTable.h"
#include "data-structure/hash/OpenAddressHashTable.h"
#include "data-structure/hash/interface/HashTableInterface.h"

namespace {

std::size_t intHash(int value, std::size_t) {
  return static_cast<std::size_t>(value);
}

std::size_t stringHash(std::string value, std::size_t) {
  return std::hash<std::string>{}(value);
}

constexpr std::size_t kSmallCapacity = 64;
constexpr std::size_t kLargeCapacity = 20011;

} // namespace

// ---------------------------------------------------------------------------
// Testes compartilhados para tipos inteiros
// ---------------------------------------------------------------------------

TEMPLATE_TEST_CASE("HashTable<int>: tabela vazia", "[hash][empty]",
                   LinkedHashTable<int>, OpenAddressHashTable<int>) {
  TestType table(kSmallCapacity, intHash);

  SECTION("nao contem nenhum valor") {
    REQUIRE_FALSE(table.contains(0));
    REQUIRE_FALSE(table.contains(1));
    REQUIRE_FALSE(table.contains(-1));
  }

  SECTION("remover de tabela vazia nao lanca excecao") {
    REQUIRE_NOTHROW(table.remove(42));
    REQUIRE_FALSE(table.contains(42));
  }
}

TEMPLATE_TEST_CASE("HashTable<int>: sem capacidade", "[hash][capacity]",
                   LinkedHashTable<int>, OpenAddressHashTable<int>) {
  TestType table;

  REQUIRE_THROWS_AS(table.add(1), std::logic_error);
  REQUIRE_THROWS_AS(table.contains(1), std::logic_error);
}

TEMPLATE_TEST_CASE("HashTable<int>: funcao hash invalida", "[hash][capacity]",
                   LinkedHashTable<int>, OpenAddressHashTable<int>) {
  REQUIRE_THROWS_AS(TestType(8, std::function<std::size_t(int, std::size_t)>()),
                    std::invalid_argument);
}

TEMPLATE_TEST_CASE("HashTable<int>: add e contains", "[hash][add]",
                   LinkedHashTable<int>, OpenAddressHashTable<int>) {
  TestType table(kSmallCapacity, intHash);

  SECTION("valor adicionado passa a ser encontrado") {
    table.add(10);
    REQUIRE(table.contains(10));
  }

  SECTION("valores nao adicionados continuam ausentes") {
    table.add(10);
    REQUIRE_FALSE(table.contains(11));
    REQUIRE_FALSE(table.contains(9));
  }

  SECTION("varios valores distintos") {
    constexpr std::array values{1, 2, 3, 4, 5};

    for (int v : values) {
      table.add(v);
    }
    for (int v : values) {
      CAPTURE(v);
      REQUIRE(table.contains(v));
    }

    REQUIRE_FALSE(table.contains(6));
  }

  SECTION("zero e negativos") {
    table.add(0);
    table.add(-1);
    table.add(-100);
    REQUIRE(table.contains(0));
    REQUIRE(table.contains(-1));
    REQUIRE(table.contains(-100));
    REQUIRE_FALSE(table.contains(1));
  }

  SECTION("contains funciona em objeto const") {
    table.add(7);
    const TestType &ref = table;
    REQUIRE(ref.contains(7));
    REQUIRE_FALSE(ref.contains(8));
  }

  SECTION("adicionar duplicado nao quebra a tabela") {
    table.add(5);
    REQUIRE_NOTHROW(table.add(5));
    REQUIRE(table.contains(5));
  }
}

TEMPLATE_TEST_CASE("HashTable<int>: remove", "[hash][remove]",
                   LinkedHashTable<int>, OpenAddressHashTable<int>) {
  TestType table(kSmallCapacity, intHash);

  SECTION("remove valor existente") {
    table.add(1);
    table.remove(1);
    REQUIRE_FALSE(table.contains(1));
  }

  SECTION("remove nao afeta os demais valores") {
    table.add(1);
    table.add(2);
    table.add(3);
    table.remove(2);
    REQUIRE(table.contains(1));
    REQUIRE_FALSE(table.contains(2));
    REQUIRE(table.contains(3));
  }

  SECTION("remover valor inexistente nao altera a tabela") {
    table.add(1);
    REQUIRE_NOTHROW(table.remove(999));
    REQUIRE(table.contains(1));
    REQUIRE_FALSE(table.contains(999));
  }

  SECTION("remover duas vezes o mesmo valor e seguro") {
    table.add(1);
    table.remove(1);
    REQUIRE_NOTHROW(table.remove(1));
    REQUIRE_FALSE(table.contains(1));
  }

  SECTION("adicionar duplicado e remover uma vez elimina o valor") {
    table.add(5);
    table.add(5);
    table.remove(5);
    REQUIRE_FALSE(table.contains(5));
  }

  SECTION("re-adicionar apos remover") {
    table.add(1);
    table.remove(1);
    table.add(1);
    REQUIRE(table.contains(1));
  }
}

// ---------------------------------------------------------------------------
// Colisões
// ---------------------------------------------------------------------------

TEMPLATE_TEST_CASE("HashTable<int>: colisoes", "[hash][collision]",
                   LinkedHashTable<int>, OpenAddressHashTable<int>) {
  // Todos os multiplos de 1024 caem no indice 0 de uma tabela de 64 posicoes.
  TestType table(kSmallCapacity, intHash);

  std::vector<int> colliding;
  for (int i = 0; i < 50; ++i) {
    colliding.push_back(i * 1024);
  }

  for (int v : colliding) {
    table.add(v);
  }

  SECTION("todos os valores colidentes sao encontrados") {
    for (int v : colliding) {
      REQUIRE(table.contains(v));
    }
    REQUIRE_FALSE(table.contains(1));
    REQUIRE_FALSE(table.contains(1025));
  }

  SECTION("remover um valor no meio da cadeia/sondagem preserva os demais") {
    // Em enderecamento aberto, remover sem marcar como "deletado"
    // (lapide) quebraria a busca pelos elementos seguintes.
    table.remove(colliding[10]);
    REQUIRE_FALSE(table.contains(colliding[10]));
    for (std::size_t i = 0; i < colliding.size(); ++i) {
      if (i != 10) {
        REQUIRE(table.contains(colliding[i]));
      }
    }
  }

  SECTION("remover o primeiro e o ultimo valor inseridos") {
    table.remove(colliding.front());
    table.remove(colliding.back());
    REQUIRE_FALSE(table.contains(colliding.front()));
    REQUIRE_FALSE(table.contains(colliding.back()));
    REQUIRE(table.contains(colliding[1]));
    REQUIRE(table.contains(colliding[colliding.size() - 2]));
  }
}

TEMPLATE_TEST_CASE("HashTable<int>: funcao hash maior que a capacidade",
                   "[hash][collision]", LinkedHashTable<int>,
                   OpenAddressHashTable<int>) {
  // A funcao devolve um indice muito acima da capacidade: a tabela precisa
  // reduzi-lo, e nao acessar memoria fora do vetor.
  TestType table(8, [](int, std::size_t) { return std::size_t{1000000007}; });

  table.add(1);
  table.add(2);

  REQUIRE(table.contains(1));
  REQUIRE(table.contains(2));
  REQUIRE_FALSE(table.contains(3));
}

TEMPLATE_TEST_CASE("HashTable<int>: grande volume", "[hash][stress]",
                   LinkedHashTable<int>, OpenAddressHashTable<int>) {
  TestType table(kLargeCapacity, intHash);
  constexpr int N = 10000;

  for (int i = 0; i < N; ++i) {
    table.add(i);
  }

  SECTION("todos os valores inseridos sao encontrados") {
    for (int i = 0; i < N; ++i) {
      REQUIRE(table.contains(i));
    }
    REQUIRE_FALSE(table.contains(N));
    REQUIRE_FALSE(table.contains(-1));
  }

  SECTION("remover os pares mantem apenas os impares") {
    for (int i = 0; i < N; i += 2) {
      table.remove(i);
    }
    for (int i = 0; i < N; ++i) {
      if (i % 2 == 0) {
        REQUIRE_FALSE(table.contains(i));
      } else {
        REQUIRE(table.contains(i));
      }
    }
  }

  SECTION("remover tudo deixa a tabela vazia e reutilizavel") {
    for (int i = 0; i < N; ++i) {
      table.remove(i);
    }
    for (int i = 0; i < N; ++i) {
      REQUIRE_FALSE(table.contains(i));
    }
    table.add(123);
    REQUIRE(table.contains(123));
  }
}

TEMPLATE_TEST_CASE("HashTable<int>: ciclos repetidos de add/remove",
                   "[hash][tombstone]", LinkedHashTable<int>,
                   OpenAddressHashTable<int>) {
  TestType table(kSmallCapacity, intHash);

  // Valores fixos que permanecem na tabela durante todo o teste.
  for (int i = 0; i < 20; ++i) {
    table.add(i * 1024);
  }

  // Em enderecamento aberto, muitas lapides acumuladas nao podem esgotar a
  // tabela nem causar loop infinito na busca.
  for (int round = 0; round < 1000; ++round) {
    table.add(777);
    REQUIRE(table.contains(777));
    table.remove(777);
    REQUIRE_FALSE(table.contains(777));
  }

  for (int i = 0; i < 20; ++i) {
    REQUIRE(table.contains(i * 1024));
  }
}

// ---------------------------------------------------------------------------
// Cópia e movimentação (regra dos cinco)
// ---------------------------------------------------------------------------

TEMPLATE_TEST_CASE("HashTable<int>: copia e movimentacao", "[hash][copy]",
                   LinkedHashTable<int>, OpenAddressHashTable<int>) {
  TestType table(kSmallCapacity, intHash);
  table.add(1);
  table.add(2);

  SECTION("a copia e independente do original") {
    TestType copy(table);
    table.remove(1);
    copy.add(3);

    REQUIRE_FALSE(table.contains(1));
    REQUIRE(copy.contains(1));
    REQUIRE(copy.contains(3));
    REQUIRE_FALSE(table.contains(3));
  }

  SECTION("atribuicao por copia") {
    TestType other(kSmallCapacity, intHash);
    other.add(99);
    other = table;

    REQUIRE(other.contains(1));
    REQUIRE(other.contains(2));
    REQUIRE_FALSE(other.contains(99));
    table.remove(2);
    REQUIRE(other.contains(2));
  }

  SECTION("auto-atribuicao e segura") {
    auto &alias = table;
    table = alias;
    REQUIRE(table.contains(1));
    REQUIRE(table.contains(2));
  }

  SECTION("construtor de movimentacao") {
    TestType moved(std::move(table));
    REQUIRE(moved.contains(1));
    REQUIRE(moved.contains(2));
  }

  SECTION("atribuicao por movimentacao") {
    TestType other(kSmallCapacity, intHash);
    other = std::move(table);
    REQUIRE(other.contains(1));
    REQUIRE(other.contains(2));
  }
}

// ---------------------------------------------------------------------------
// Comportamentos específicos
// ---------------------------------------------------------------------------

TEST_CASE("OpenAddressHashTable: capacidade fixa", "[hash][open][capacity]") {
  OpenAddressHashTable<int> table(3, intHash);

  REQUIRE_FALSE(table.isFull());
  table.add(1);
  table.add(2);
  table.add(3);
  REQUIRE(table.isFull());

  SECTION("valor novo em tabela cheia lanca excecao") {
    REQUIRE_THROWS_AS(table.add(4), std::runtime_error);
    REQUIRE_FALSE(table.contains(4));
  }

  SECTION("valor ja presente em tabela cheia nao lanca") {
    REQUIRE_NOTHROW(table.add(2));
    REQUIRE(table.isFull());
  }

  SECTION("remover libera espaco (reaproveita a lapide)") {
    table.remove(2);
    REQUIRE_FALSE(table.isFull());
    REQUIRE_NOTHROW(table.add(4));
    REQUIRE(table.contains(4));
    REQUIRE(table.contains(1));
    REQUIRE(table.contains(3));
    REQUIRE_FALSE(table.contains(2));
  }

  SECTION("buscar valor ausente em tabela cheia termina") {
    REQUIRE_FALSE(table.contains(100));
  }
}

TEST_CASE("LinkedHashTable: withHashOf devolve a lista do indice",
          "[hash][linked]") {
  LinkedHashTable<int> table(4, intHash);

  table.add(1);
  table.add(5); // 5 % 4 == 1: mesma lista
  table.add(2);

  auto &list = table.withHashOf(1);
  REQUIRE(list.size() == 2);
  REQUIRE(list.contains(1));
  REQUIRE(list.contains(5));
  REQUIRE_FALSE(list.contains(2));
}

// ---------------------------------------------------------------------------
// Tipo não numérico
// ---------------------------------------------------------------------------

TEMPLATE_TEST_CASE("HashTable<std::string>: operacoes basicas",
                   "[hash][string]", LinkedHashTable<std::string>,
                   OpenAddressHashTable<std::string>) {
  TestType table(kSmallCapacity, stringHash);

  table.add("ola");
  table.add("mundo");
  table.add("");

  REQUIRE(table.contains("ola"));
  REQUIRE(table.contains("mundo"));
  REQUIRE(table.contains(""));
  REQUIRE_FALSE(table.contains("Ola")); // diferencia maiusculas/minusculas
  REQUIRE_FALSE(table.contains("ol"));

  table.remove("ola");
  REQUIRE_FALSE(table.contains("ola"));
  REQUIRE(table.contains("mundo"));
  REQUIRE(table.contains(""));
}

// ---------------------------------------------------------------------------
// Uso polimórfico via interface
// ---------------------------------------------------------------------------

TEST_CASE("HashTableInterface: uso polimorfico", "[hash][interface]") {
  std::vector<std::unique_ptr<HashTableInterface<int>>> tables;
  tables.push_back(
      std::make_unique<LinkedHashTable<int>>(kSmallCapacity, intHash));
  tables.push_back(
      std::make_unique<OpenAddressHashTable<int>>(kSmallCapacity, intHash));

  for (auto &table : tables) {
    REQUIRE_FALSE(table->contains(1));
    table->add(1);
    table->add(2);
    REQUIRE(table->contains(1));
    REQUIRE(table->contains(2));
    table->remove(1);
    REQUIRE_FALSE(table->contains(1));
    REQUIRE(table->contains(2));
  }
}
