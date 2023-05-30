//
// Created by LAMM_ on 29/05/2023.
//
#include "Utilidades.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void *error(char *mensaje, void *a_liberar) {
    printf("%s", mensaje);
    if (a_liberar != NULL) {
        free(a_liberar);
    }
    return NULL;
}

bool textosIguales(char *cadena1, char *cadena2) {
    if (strlen(cadena1) != strlen(cadena2)) {
        return false;
    }
    for (int i = 0; i < strlen(cadena1); i++) {
        if (cadena1[i] != cadena2[i]) {
            return false;
        }
    }
    return true;
}