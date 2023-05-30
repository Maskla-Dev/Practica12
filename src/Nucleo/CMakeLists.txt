add_library(Nucleo Constructor.c Arboles.c ListaNodosArbol.c Utilidades.c)
target_include_directories(Nucleo PUBLIC ${CMAKE_SOURCE_DIR}/include)