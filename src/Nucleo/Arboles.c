//
// Created by LAMM_ on 29/05/2023.
//
#include "Arboles.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "Utilidades.h"

Arbol *crearArbol(char *nombre_raiz) {
    Arbol *arbol = (Arbol *) malloc(sizeof(Arbol));
    if (arbol == NULL) {
        printf("No se pudo crear el arbol\n");
        return NULL;
    }
    arbol->raiz = crearNodoArbol(nombre_raiz, RAIZ);
    arbol->altura = 1;
    if (arbol->raiz == NULL) {
        printf("No se pudo crear la raiz\n");
        return NULL;
    }
    return arbol;
}

NodoArbol *crearNodoArbol(char *nombre, TipoNodo tipo) {
    NodoArbol *nodo = (NodoArbol *) malloc(sizeof(NodoArbol));
    if (nodo == NULL) {
        return error("No se pudo crear el nodo\n", NULL);
    }
    if (nombre == NULL) {
        return error("Nombre del nodo no puede estar vacío\n", nodo);
    }
    nodo->rotulo = (char *) malloc(strlen(nombre) + 1);
    if (nodo->rotulo == NULL) {
        return error("No se pudo crear el rotulo\n", nodo);
    }
    strcpy(nodo->rotulo, nombre);
    nodo->tipo = tipo;
    nodo->profundidad = 1;
    if (tipo == RAIZ)
        nodo->estado = NO_IMPORTA;
    nodo->hijos = NULL;
    return nodo;
}

bool insertarEnArbol(Arbol *arbol, char *objetivo, NodoArbol *nodo) {
    NodoArbol *nodo_objetivo;
    if (arbol == NULL || nodo == NULL) {
        return false;
    }
    nodo_objetivo = buscarNodo(arbol->raiz, objetivo);
    if (nodo_objetivo == NULL) {
        return false;
    }
    if (nodo_objetivo->hijos == NULL) {
        nodo_objetivo->hijos = crearListaNA();
        if (nodo_objetivo->hijos == NULL) {
            return false;
        }
    }
    nodo->profundidad = nodo_objetivo->profundidad + 1;
    if (nodo->profundidad > arbol->altura) {
        arbol->altura = nodo->profundidad;
    }
    nodo->estado = (nodo->tipo == MATERIA) ? NO_COMPLETADO : NO_CURSADO;
    insertarNodoListaNA(nodo_objetivo->hijos, nodo);
    return true;
}

NodoArbol *buscarNodo(NodoArbol *nodo, char *clave) {
    NodoArbol *nodo_objetivo;
    if (nodo == NULL) {
        return NULL;
    }
    if (textosIguales(nodo->rotulo, clave) == true) {
        return nodo;
    }
    if (nodo->hijos == NULL) {
        return NULL;
    }
    irAlInicioNA(nodo->hijos);
    while (nodo->hijos->actual != NULL) {
        nodo_objetivo = buscarNodo(nodo->hijos->actual->nodo, clave);
        if (nodo_objetivo != NULL) {
            return nodo_objetivo;
        }
        irAlSiguienteNA(nodo->hijos);
    }
    return NULL;
}

void imprimirArbol(NodoArbol *nodo_arbol) {
    if (nodo_arbol == NULL) {
        printf("No se pudo imprimir el arbol, no hay contenido\n");
        return;
    }
    for (int i = 0; i < (nodo_arbol->profundidad - 1) * 3; i++) {
        printf("  ");
    }
    printf("%s\n", nodo_arbol->rotulo);
    if (nodo_arbol->hijos == NULL) {
        return;
    }
    irAlInicioNA(nodo_arbol->hijos);
    while (nodo_arbol->hijos->actual != NULL) {
        imprimirArbol(nodo_arbol->hijos->actual->nodo);
        irAlSiguienteNA(nodo_arbol->hijos);
    }
}