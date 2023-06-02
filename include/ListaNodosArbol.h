//
// Created by LAMM_ on 27/05/2023.
//

#ifndef PRACTICA12_LISTANODOSARBOL_HPP
#define PRACTICA12_LISTANODOSARBOL_HPP

#include <stdbool.h>
#include "Arboles.h"
#include <stdlib.h>
#include <stddef.h>

typedef struct NodoListaNodosArbol {
    struct NodoArbol *nodo;
    struct NodoListaNodosArbol *siguiente;
} NodoLista_NA;

typedef struct ListaNodosArbol {
    size_t tam;
    NodoLista_NA *inicio;
    NodoLista_NA *actual;
} Lista_NA;


//Nodos de lista
//Crea una entrada para la lista, devuelve NULL si no se pudo crear
NodoLista_NA *crearNodoListaNA(struct NodoArbol *nodo);

//Lista
//Crea una lista vacia, devuelve NULL si no se pudo crear
Lista_NA *crearListaNA();

//Vuelve a la cabecera de la lista
void irAlInicioNA(Lista_NA *lista);

//Avanza a la siguiente entrada de la lista
void irAlSiguienteNA(Lista_NA *lista);

//Avanza a la ultima entrada de la lista
void irAlFinalNA(Lista_NA *lista);

//@TODO: Implementar
//Verifica si el nodo existe en la lista (nodo->rotulo == clave), devuelve true si existe, false si no
bool existeNodoEnListaNA(Lista_NA *lista, char *clave);

//@TODO: Implementar
//Elimina un nodo de la lista
NodoLista_NA *retirarNodoListaNA(Lista_NA *lista, char *clave);

//@TODO: Implementar
//Inserta un nodo en la lista, devuelve true si se pudo insertar, false si no
bool insertarNodoListaNA(Lista_NA *lista, struct NodoArbol *nodo);

#endif //PRACTICA12_LISTANODOSARBOL_HPP
