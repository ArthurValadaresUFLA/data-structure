#include <iostream>

#include "data-structure/node/SinglyLinkedNode.h"

// Instancia um template da biblioteca para confirmar que o cabeçalho instalado
// alcança a definição correspondente em <package>/src e que o resultado linka.
int main() {
  const SinglyLinkedNode<int> node(42);

  std::cout << "data-structure ok: " << node.getData() << '\n';

  return 0;
}
