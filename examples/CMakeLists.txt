file(GLOB_RECURSE DREDD_SOURCES CONFIGURE_DEPENDS
     ${CMAKE_CURRENT_SOURCE_DIR}/dredd/*.cpp)

foreach(DREDD_SOURCE ${DREDD_SOURCES})
  file(RELATIVE_PATH DREDD_REL_PATH ${CMAKE_CURRENT_SOURCE_DIR}/dredd
       ${DREDD_SOURCE})
  string(REGEX REPLACE "\.cpp$" "" DREDD_REL_PATH ${DREDD_REL_PATH})
  string(REPLACE "/" "_" DREDD_TARGET "dredd_${DREDD_REL_PATH}")

  # Sanitiza o nome do target: substitui qualquer caractere que não seja letra,
  # número ou '_' por '_' (espaços, acentos, pontuação, etc.)
  string(REGEX REPLACE "[^A-Za-z0-9_]" "_" DREDD_TARGET ${DREDD_TARGET})

  # Evita underscores duplicados/consecutivos resultantes da substituição
  string(REGEX REPLACE "_+" "_" DREDD_TARGET ${DREDD_TARGET})

  add_executable(${DREDD_TARGET} ${DREDD_SOURCE})
  target_link_libraries(${DREDD_TARGET} PRIVATE data-structure::data-structure)
endforeach()
