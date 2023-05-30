//
// Created by LAMM_ on 27/05/2023.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Constructor.h"

int main(int argc, char *argv[]) {
    int test_type = 0;
    char *texto;
    Arbol *arbol;
    if (argc < 2) {
        printf("No se han introducido argumentos\n");
        return EXIT_FAILURE;
    }
    test_type = atoi(argv[1]);
    switch (test_type) {
        case 1:
            return leerArchivo(argv[2]) != NULL ? EXIT_SUCCESS : EXIT_FAILURE;
        case 2:
            texto = leerArchivo(argv[2]);
            return strcmp(obtenerNombreRaiz(texto), "Especialidades") == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
        case 3:
            arbol = construirArbol(argv[2]);
            return arbol != NULL ? EXIT_SUCCESS : EXIT_FAILURE;
        case 4:
            arbol = construirArbol(argv[2]);
            imprimirArbol(arbol->raiz);
            return arbol == NULL ? EXIT_FAILURE : EXIT_SUCCESS;
        default:
            printf("No se ha introducido un tipo de prueba válido\n");
            return EXIT_FAILURE;
    }
}