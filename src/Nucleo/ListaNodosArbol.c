//
// Created by LAMM_ on 29/05/2023.
//
#include "ListaNodosArbol.h"
#include <stdlib.h>
#include <string.h>

NodoLista_NA *crearNodoListaNA(struct NodoArbol *nodo) {
    NodoLista_NA *nodo_lista = (NodoLista_NA *) malloc(sizeof(NodoLista_NA));
    if (nodo_lista == NULL) {
        return error("No se pudo crear el nodo de la lista", NULL);
    }
    if (nodo == NULL) {
        return error("No se puede crear un nodo de lista con un nodo nulo", NULL);
    }
    nodo_lista->nodo = nodo;
    nodo_lista->siguiente = NULL;
    return nodo_lista;
}

Lista_NA *crearListaNA() {
    Lista_NA *lista = (Lista_NA *) malloc(sizeof(Lista_NA));
    if (lista == NULL) {
        return error("No se pudo crear la lista", NULL);
    }
    lista->tam = 0;
    lista->inicio = NULL;
    lista->actual = NULL;
    return lista;
}

void irAlInicioNA(Lista_NA *lista) {
    if (lista == NULL) {
        return;
    }
    lista->actual = lista->inicio;
}

void irAlSiguienteNA(Lista_NA *lista) {
    if (lista == NULL) {
        return;
    }
    if (lista->actual == NULL) {
        return;
    }
    lista->actual = (NodoLista_NA *) lista->actual->siguiente;
}

void irAlFinalNA(Lista_NA *lista) {
    if (lista == NULL) {
        return;
    }
    irAlInicioNA(lista);
    while (lista->actual->siguiente != NULL) {
        irAlSiguienteNA(lista);
    }
}

bool insertarNodoListaNA(Lista_NA *lista, struct NodoArbol *nodo) {
    NodoLista_NA *nodo_lista;
    if (lista == NULL || nodo == NULL) {
        return false;
    }
    nodo_lista = crearNodoListaNA(nodo);
    if (nodo_lista == NULL) {
        return false;
    }
    if (lista->inicio == NULL) {
        lista->inicio = nodo_lista;
        lista->actual = nodo_lista;
    } else {
        irAlFinalNA(lista);
        lista->actual->siguiente = nodo_lista;
    }
    lista->tam++;
    return true;
}

NodoLista_NA *retirarNodoListaNA(Lista_NA *lista, char *clave) {
    if (lista == NULL || clave == NULL) {
        return NULL;
    }
    Lista_NA lista_aux;
    lista_aux.inicio = lista->inicio;
    lista_aux.actual = lista->inicio;
    NodoLista_NA *nodo_retirado = NULL;
    irAlInicioNA(lista);
    while (lista->actual != NULL) {
        if (strcmp(lista->actual->nodo->rotulo, clave) == 0) {
            while (lista_aux.actual->siguiente != lista->actual) {
                irAlSiguienteNA(&lista_aux);
            }
            nodo_retirado = lista->actual;
            lista_aux.actual->siguiente = lista->actual->siguiente;
            lista->tam--;
        }
        irAlSiguienteNA(lista);
    }
    return nodo_retirado;
}