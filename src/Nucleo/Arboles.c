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
    nodo_objetivo = buscarNodoConClave(arbol->raiz, objetivo);
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
    nodo->estado = (nodo->tipo == MATERIA) ? NO_CURSADO : NO_COMPLETADO;
    insertarNodoListaNA(nodo_objetivo->hijos, nodo);
    return true;
}

NodoArbol *buscarNodoConClave(NodoArbol *nodo, char *clave) {
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
        nodo_objetivo = buscarNodoConClave(nodo->hijos->actual->nodo, clave);
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

bool cambiarEstadosDesdeLista(struct ListaNodosArbol *lista, Estado nuevo_estado) {
    if (lista == NULL) {
        return false;
    }
    irAlInicioNA(lista);
    while (lista->actual != NULL) {
        lista->actual->nodo->estado = nuevo_estado;
        irAlSiguienteNA(lista);
        free(retirarNodoListaNA(lista, lista->actual->nodo->rotulo));
    }
    return true;
}

struct ListaNodosArbol *obtenerMateriasDisponibles(Arbol *arbol, char *semestre) {
    NodoArbol *nodo_semestre = buscarNodoConClave(arbol->raiz, semestre);
    struct ListaNodosArbol *lista_materias_disponibles = crearListaNA();
    if (nodo_semestre == NULL) {
        free(lista_materias_disponibles);
        return NULL;
    }
    if (nodo_semestre->hijos == NULL) {
        free(lista_materias_disponibles);
        return NULL;
    }
    irAlInicioNA(nodo_semestre->hijos);
    while (nodo_semestre->hijos->actual != NULL) {
        if (nodo_semestre->hijos->actual->nodo->estado == NO_CURSADO) {
            insertarNodoListaNA(lista_materias_disponibles, nodo_semestre->hijos->actual->nodo);
        }
        irAlSiguienteNA(nodo_semestre->hijos);
    }
    return lista_materias_disponibles;
}

bool seHaCursadoSemestreCompleto(Arbol *arbol, char *semestre) {
    NodoArbol *nodo_semestre = buscarNodoConClave(arbol->raiz, semestre);
    if (nodo_semestre == NULL) {
        return false;
    }
    if (nodo_semestre->hijos == NULL) {
        return false;
    }
    irAlInicioNA(nodo_semestre->hijos);
    while (nodo_semestre->hijos->actual != NULL) {
        if (nodo_semestre->hijos->actual->nodo->estado != CURSADO) {
            return false;
        }
        irAlSiguienteNA(nodo_semestre->hijos);
    }
    return true;
}

bool especialidadTerminada(NodoArbol *nodo) {
    bool cumple = true;
    if (nodo == NULL) {
        return true;
    }
    if (nodo->tipo == ESPECIALIDAD) {
        if (nodo->hijos == NULL) {
            return false;
        }
        irAlInicioNA(nodo->hijos);
        while (nodo->hijos->actual != NULL) {
            cumple = cumple && especialidadTerminada(nodo->hijos->actual->nodo);
            irAlSiguienteNA(nodo->hijos);
        }
    }
    cumple = cumple && nodo->tipo == MATERIA ? nodo->estado == CURSADO : true;
    return cumple;
}