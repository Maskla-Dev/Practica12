//
// Created by LAMM_ on 29/05/2023.
//

#ifndef PRACTICA12_UTILIDADES_H
#define PRACTICA12_UTILIDADES_H

#include <stdbool.h>

//Imprime mensaje de error y libera memoria, devuelve siempre NULL
void *error(char *mensaje, void *a_liberar);

//Compara dos cadenas de texto, devuelve true si son iguales, false si no
bool textosIguales(char *cadena1, char *cadena2);

#endif //PRACTICA12_UTILIDADES_H
