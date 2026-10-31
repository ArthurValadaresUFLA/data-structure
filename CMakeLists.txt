# Versão 3.28: acima do mínimo de 3.23 exigido pelos CMakePresets "version": 4
# gerados pelo Conan e por PROJECT_IS_TOP_LEVEL (usada logo abaixo, na opção
# DATA_STRUCTURE_BUILD_EXAMPLES). A partir da 3.24 a política CMP0135 já é NEW.
cmake_minimum_required(VERSION 3.28)

project(
  data-structure
  VERSION 0.1.0
  DESCRIPTION
    "Estruturas de dados genéricas implementadas como TADs (GAC108 - DCC/UFLA)"
  HOMEPAGE_URL "https://github.com/ArthurValadaresUFLA/data-structure"
  LANGUAGES CXX)

set(LIB_NAME ${PROJECT_NAME})

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

# ---------------------------------------------------------------------------
# Biblioteca
# ---------------------------------------------------------------------------

# Todas as estruturas de dados são templates e os arquivos .cpp de src/ contêm
# exclusivamente definições de template, incluídas ao final do cabeçalho
# correspondente (nunca compiladas isoladamente). Compilá-los isoladamente
# geraria objetos vazios, portanto não há nada a compilar aqui e o alvo é
# INTERFACE (header-only).
add_library(${LIB_NAME} INTERFACE)
add_library(${LIB_NAME}::${LIB_NAME} ALIAS ${LIB_NAME})

target_compile_features(${LIB_NAME} INTERFACE cxx_std_17)

# include/ e src/ têm um único filho cada, data-structure/, para que o pacote
# instalado exponha <prefix>/include/data-structure/... e
# <prefix>/src/data-structure/... -- evita colisão de nomes genéricos como
# "hash/Hash.h" com os de outra biblioteca instalada no mesmo prefixo. Os
# cabeçalhos alcançam as definições em src/ por caminho relativo
# ("../../../src/data-structure/...").
target_include_directories(
  ${LIB_NAME}
  INTERFACE $<BUILD_INTERFACE:${INCLUDE_DIR}> $<BUILD_INTERFACE:${SOURCE_DIR}>
            $<INSTALL_INTERFACE:include> $<INSTALL_INTERFACE:src>)

# ---------------------------------------------------------------------------
# Visibilidade na IDE
# ---------------------------------------------------------------------------

# Um alvo INTERFACE não possui fontes, então cabeçalhos e implementações não
# apareceriam na árvore do projeto. Este alvo auxiliar não é compilado e existe
# apenas para que a IDE (CLion) liste e indexe os arquivos.
file(GLOB_RECURSE LIB_HEADERS CONFIGURE_DEPENDS ${INCLUDE_DIR}/*.h)
file(GLOB_RECURSE LIB_TEMPLATE_SOURCES CONFIGURE_DEPENDS ${SOURCE_DIR}/*.cpp)

add_custom_target(
  ${LIB_NAME}_sources
  SOURCES ${LIB_HEADERS} ${LIB_TEMPLATE_SOURCES}
  COMMENT "Auxílio à indexação por IDE's")

# ---------------------------------------------------------------------------
# Exemplos
# ---------------------------------------------------------------------------

# Os exercícios de examples/dredd compilam como consumidores reais da
# biblioteca (ver examples/CMakeLists.txt). Habilitados por padrão só quando
# este é o projeto principal: quem consome via add_subdirectory() não precisa
# deles.
option(
  DATA_STRUCTURE_BUILD_EXAMPLES
  "Compila os exercícios de examples/dredd como exemplos de consumo da biblioteca"
  ${PROJECT_IS_TOP_LEVEL})

if(DATA_STRUCTURE_BUILD_EXAMPLES)
  message(STATUS "${LIB_NAME}: configurando os exemplos (examples/dredd)")
  add_subdirectory(examples)
endif()

# ---------------------------------------------------------------------------
# Instalação
# ---------------------------------------------------------------------------

include(GNUInstallDirs)

# src/ é instalado como irmão de include/ porque os cabeçalhos instalados
# continuam referenciando "../../../src/data-structure/...". São as definições
# de template, alcançadas a partir dos cabeçalhos.
install(DIRECTORY ${INCLUDE_DIR}/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(DIRECTORY ${SOURCE_DIR}/ DESTINATION src)

# Nenhum arquivo de configuração CMake é instalado de propósito: o pacote é
# consumido via Conan, e o CMakeDeps gera o data-structure-config.cmake a partir
# do package_info() da receita.

# A suíte de testes unitários vive em test_package/tests e é compilada e
# executada a partir do conanfile.py de test_package, não daqui.

# ---------------------------------------------------------------------------
# Documentação
# ---------------------------------------------------------------------------

option(DATA_STRUCTURE_BUILD_DOCS "Gera a documentação Doxygen"
       ${PROJECT_IS_TOP_LEVEL})

if(DATA_STRUCTURE_BUILD_DOCS)
  find_package(Doxygen)

  if(NOT DOXYGEN_FOUND)
    message(WARNING "${LIB_NAME}: Doxygen não encontrado, docs desabilitada")
  else()
    include(FetchContent)

    FetchContent_Declare(
      doxygen-awesome-css
      URL https://github.com/jothepro/doxygen-awesome-css/archive/refs/tags/v2.3.4.zip)
    FetchContent_MakeAvailable(doxygen-awesome-css)
    FetchContent_GetProperties(doxygen-awesome-css SOURCE_DIR AWESOME_CSS_DIR)

    set(DOXYFILE_IN ${CMAKE_CURRENT_SOURCE_DIR}/doc/Doxyfile.in)
    set(DOXYFILE_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)
    configure_file(${DOXYFILE_IN} ${DOXYFILE_OUT} @ONLY)

    # Sem este alvo o Doxyfile era gerado mas o Doxygen nunca era executado.
    add_custom_target(
      docs
      COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYFILE_OUT}
      WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
      COMMENT "Gerando a documentação com Doxygen"
      VERBATIM)
  endif()
endif()
