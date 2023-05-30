#include <stdio.h>
#include <stdlib.h>
#include "Constructor.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("No se han introducido argumentos\n");
        return EXIT_FAILURE;
    }
    Arbol *arbol = construirArbol(argv[1]);
    if (arbol == NULL) {
        printf("No se pudo construir el arbol\n");
        return EXIT_FAILURE;
    }
    imprimirArbol(arbol->raiz);
    return EXIT_SUCCESS;
}
